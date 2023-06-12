#!/usr/bin/env python3

import argparse
import requests
import subprocess
import sys
from glob import glob
from os import mkdir, rename
from os.path import join, isdir, isfile, dirname, splitext, basename, abspath

# Types
LIVE = "live"
SAMPLE = "sample"
RUN_TYPES = [LIVE, SAMPLE]

# Model variants
ALL = "all"
ALL_SCC = "scchart"
SCC_CLASSIC = "scchart-classic"
SCC_DYN = "scchart-dynamic"
SCC_SAMPLES = [SCC_CLASSIC, SCC_DYN]
ALL_LF = "lf"
LF_PLAIN = "lf-classic"
LF_MODES = "lf-modes"
LF_MODES_NESTED = "lf-modes-nested"
LF_EMBED = "lf-scchart"
LF_SAMPLES = [LF_PLAIN, LF_MODES, LF_MODES_NESTED, LF_EMBED]
RUN_CHOICES = [ALL, ALL_SCC, ALL_LF] + SCC_SAMPLES + LF_SAMPLES

# Files
ROOT = dirname(abspath(__file__))
SAMPLE_SOURCES = {
    SCC_CLASSIC: join(ROOT, "sccharts/classic/FurutaPendulumSample.sctx"),
    SCC_DYN: join(ROOT, "sccharts/dynamic-ticks/FurutaPendulumSample.sctx"),
    LF_PLAIN: join(ROOT, "lf/classic/FurutaPendulumSample.lf"),
    LF_MODES: join(ROOT, "lf/modes/FurutaPendulumSample.lf"),
    LF_MODES_NESTED: join(ROOT, "lf/modes-nested/FurutaPendulumSample.lf"),
    LF_EMBED: join(ROOT, "lf/scchart-embedded/FurutaPendulumSample.lf"),
}
LIVE_SOURCES = {
    SCC_DYN: join(ROOT, "sccharts/dynamic-ticks/FurutaPendulumLive.sctx"),
    LF_MODES: join(ROOT, "lf/modes/FurutaPendulumLive.lf"),
}

# Compiler locations
COMPILER_URL = "https://github.com/a-sr/furuta-pendulum/releases/tag/1.0.0"
SCC_URL = "https://github.com/a-sr/furuta-pendulum/releases/download/1.0.0/scc.jar"
SCC_JAR = join(ROOT, "compiler/scc.jar")
LFC_URL = "https://github.com/a-sr/furuta-pendulum/releases/download/1.0.0/lfc.jar"
LFC_JAR = join(ROOT, "compiler/lfc.jar")

# Source files for SCCharts compilation
IMPL_DIR = join(ROOT, "impl")
BEHAVIOR_C = join(IMPL_DIR, "behavior.c")
SIMULATION_C = join(IMPL_DIR, "simulation.c")
VISUALIZATION_C = join(IMPL_DIR, "visualization.c")
MAIN_DIR = join(ROOT, "sccharts/main")
SAMPLE_MAIN = join(MAIN_DIR, "sample-main.c")
LIVE_MAIN = join(MAIN_DIR, "live-main.c")
TIME_UTIL = join(MAIN_DIR, "time-util.c")
FACIL_DIR = join(ROOT, "facil.io")
FACIL_LIB = join(FACIL_DIR, "libdump")
FACIL_SRC = join(FACIL_DIR, "lib")

# Gnuplot plotting
SAMPLE_DATA_NAME = "pendulum-sample.csv"
PLOT_PATH = join(ROOT, "gnuplot")
PENDULUM_PLOT = join(PLOT_PATH, "pendulum.gnuplot")

VISUALIZATION = join(ROOT, "visualization/visualization.html")


def main():
    global args

    if args.type == SAMPLE or not args.type:
        models = []

        # Default models
        if not args.model:
            args.model = ALL

        # Collect models
        if args.model == ALL:
            models = SCC_SAMPLES + LF_SAMPLES
        elif args.model == ALL_SCC:
            models = SCC_SAMPLES
        elif args.model == ALL_LF:
            models = LF_SAMPLES
        elif args.model in SCC_SAMPLES or args.model in LF_SAMPLES:
            models = [args.model]
        else:
            print(f"Unknown model {args.model}.")
            exit(-1)

        # Run models
        for model in models:
            if model not in SCC_SAMPLES and model not in LF_SAMPLES:
                print(f"Unknown model name: {model}")
                exit(-2)
            elif model not in SAMPLE_SOURCES:
                print(f"Model {model} does not support sampling.")
                exit(-3)
            
            if model in SCC_SAMPLES:
                run_ssc(model, True)               
            else:
                run_lf(model, True)
    elif args.type == LIVE:
        # Check support
        if not args.model or args.model == ALL or args.model == ALL_SCC or args.model == ALL_LF:
            print(f"Specify a single model to run live.")
            exit(-4)
        elif args.model in LIVE_SOURCES:
            # Run model
            if args.model in SCC_SAMPLES:
                run_ssc(args.model, False)
            else:
                run_lf(args.model, False)
        else:
            print(f"Model {args.model} does not support live simulation.")
            exit(-5)

    else:
        print(f"Unknown run type {args.type}.")
        exit(-6)


def run_lf(model, sample):
    source = SAMPLE_SOURCES[model] if sample else LIVE_SOURCES[model]
    wd = dirname(source)

    print(f"\n= Model {model} =")
    print("= Compiling LF Program =")
    check_compiler(LFC_JAR)
    if not sample:
        check_facil()
    cmd = [
        "java", "-jar", LFC_JAR,
        source
    ]
    run_cmd(cmd, wd)

    print("\n= Running LF Program =")
    if not sample:
        print("Please open the visualization front-end is a browser on the same computer and click connect after the server started.")
        print(f"Visualization page: {VISUALIZATION}")
    name = splitext(basename(source))[0]
    bin_dir = join(wd, "bin")
    run_cmd([join(bin_dir, name)], wd)

    if sample:
        print("\n= Creating Plots =")
        plot_dir = join(wd, "plot")
        if not isdir(plot_dir):
            mkdir(plot_dir)
        rename(join(wd, SAMPLE_DATA_NAME), join(plot_dir, SAMPLE_DATA_NAME))
        plot(plot_dir)
        print()


def run_ssc(model, sample):
    source = SAMPLE_SOURCES[model] if sample else LIVE_SOURCES[model]
    wd = dirname(source)

    print(f"\n= Model {model} =")
    print("= Compiling SCChart =")
    check_compiler(SCC_JAR)
    gen_dir = join(wd, "src-gen")
    cmd = [
        "java", "-jar", SCC_JAR,
        "-v",
        "-o", gen_dir,
        "-s", "de.cau.cs.kieler.sccharts.netlist",
        source
    ]
    run_cmd(cmd, wd)

    print("\n= Compiling Generated Code =")
    extra = [BEHAVIOR_C, SIMULATION_C]
    if sample:
        extra += [
            SAMPLE_MAIN,
            "-I", MAIN_DIR,
            TIME_UTIL,
        ]
    else:
        check_facil()
        extra += [
            VISUALIZATION_C,
            LIVE_MAIN,
            "-I", MAIN_DIR,
            TIME_UTIL,
            "-I", join(FACIL_LIB, "include"),
            *glob(join(FACIL_LIB, "src/*.c")),
            "-pthread"
        ]
    name = splitext(basename(source))[0]
    bin_dir = join(wd, "bin")
    exe = join(bin_dir, name)
    cmd = [
        "gcc", "-Wall",
        "-O3", "-DNDEBUG", "-std=gnu11",  # as in LF RELEASE mode
        "-o", exe,
        "-I"+IMPL_DIR, "-I"+gen_dir,
        join(gen_dir, name + ".c"),
        *extra,
        "-lm"
    ]
    if not isdir(bin_dir):
        mkdir(bin_dir)
    run_cmd(cmd, wd)

    print("\n= Running Program =")
    if not sample:
        print("Please open the visualization front-end is a browser on the same computer and click connect after the server started.")
        print(f"Visualization page: {VISUALIZATION}")
    cmd = [exe]
    run_cmd(cmd, wd)
    print("Execution finished.")

    if sample:
        print("\n= Creating Plots =")
        plot_dir = join(wd, "plot")
        if not isdir(plot_dir):
            mkdir(plot_dir)
        rename(join(wd, SAMPLE_DATA_NAME), join(plot_dir, SAMPLE_DATA_NAME))
        plot(plot_dir)
        print()


def run_cmd(cmd, wd):
    print(" ".join(cmd))
    r = subprocess.run(cmd, cwd=wd, text=True, stdout=sys.stdout, stderr=sys.stderr)
    if r.returncode != 0:
        print("ERROR: Execution failed. Exit code: ", r.returncode)
        exit(-30)


def check_facil():
    if not isdir(FACIL_LIB):
        if not isdir(FACIL_SRC):
            print("facil.io submodule not checked out!")
            answer = input('Checkout facil.io submodule now? (Yes/No): ')
            if answer.lower() == "yes" or answer.lower() == "y":
                run_cmd(["git", "submodule", "init"], ROOT)
                run_cmd(["git", "submodule", "update"], ROOT)
            else:
                print("Please update the facil.io submodule by running 'git submodule init && git submodule update'.")
                exit(0)

        print("Missing facil.io library files!")
        answer = input('Prepare facil.io sources now? (Yes/No): ')
        if answer.lower() == "yes" or answer.lower() == "y":
            run_cmd(["make", "libdump"], FACIL_DIR)
        else:
            print("Please prepare facil.io sources by running 'make libdump'.")
            exit(0)


def check_compiler(jar):
    if not isfile(jar):
        jar_dir = dirname(jar)
        if not isdir(jar_dir):
            mkdir(jar_dir)

        print("Missing compiler!")
        print("The compilation process requires a compatible compiler for LF and SCCharts.")
        answer = input('Automatically download the required jars? (Yes/No): ')
        if answer.lower() == "yes" or answer.lower() == "y":
            if not isfile(SCC_JAR):
                print("== Downloading SCCharts Compiler ==")
                r = requests.get(SCC_URL)
                with open(SCC_JAR, "wb") as f:
                    f.write(r.content)
            if not isfile(SCC_JAR):
                print("== Downloading LF Compiler ==")
                r = requests.get(LFC_URL)
                with open(SCC_JAR, "wb") as f:
                    f.write(r.content)
        else:
            print(
                f"Please download the compiler jars from {COMPILER_URL} and place them in {jar_dir}.")
            exit(0)


def plot(dir):
    cmd = ["gnuplot", PENDULUM_PLOT]
    run_cmd(cmd, dir)


if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser(
        description="Builds and runs different variants of the Furuta Pendulum.")
    arg_parser.add_argument("type", nargs="?", choices=RUN_TYPES)
    arg_parser.add_argument("model", nargs="?", choices=RUN_CHOICES)

    global args
    args = arg_parser.parse_args()

    try:
        main()
    except KeyboardInterrupt:
        print("\nAbort")
        exit(0)
