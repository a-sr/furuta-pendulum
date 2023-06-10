# Furuta Pendulum Controllers in Lingua Franca and SCCharts

This repository features different variants of [Lingua Franca](https://www.lf-lang.org) and [SCCharts](https://github.com/kieler/semantics/wiki) programs that control a [Furuta pendulum](https://en.wikipedia.org/wiki/Furuta_pendulum).
The models illustrate the various design styles and notations, and are used to compare and test different language features.


## The Furuta Pendulum

A Furuta pendulum is a classic control system problem often used to teach feedback control. 
It consists of a vertical shaft driven by motor, a fixed arm extending out at 90 degrees from the top of the shaft, and a pendulum at the end of the arm.
The goal is to rotate the shaft to impart enough energy to the pendulum that it swings up, to then catch the pendulum and balance it so that the pendulum remains above the arm.
Each of these steps requires a different control behavior, which makes a controller a prime candidate for a modal model.

![Furuta pendulum schematic.](/visualization/pendulum-schematic.png)

To illustrate additional timing aspects, the classical setup is extended by an LED light and a speaker.
The LED displays the phase in which the controller operates.
*Off* during swinging up, *blinking* with a 30 msec period while catching, and constantly *on* when stabilizing.
The speaker indicates how close the pendulum is to its upright position.
From the lowest to the highest position it should play an ascending chromatic scale, specifically C<sub>2</sub>-B<sub>2</sub> (approx. 65-123 Hz), by producing a square wave signal.


## Control Behavior

The simulation and motor control logic used in the contained examples replicate [a solution by Eker et al.](https://ptolemy.berkeley.edu/papers/02/IFAC/IFAC.pdf)
It was originally implemented as a [Ptolemy II model](https://ptolemy.berkeley.edu/ptolemyII/ptII10.0/ptII10.0.1/ptolemy/domains/gr/demo/FurutaPendulum/FurutaPendulum/) and [adapted to C and LF](https://github.com/lf-lang/examples-lingua-franca/tree/383e816627e2668330df3dfc08e7f4202461f42c/C/src/modal_models/FurutaPendulum) by Edward A. Lee.
The models in this repository use an adjusted variant of this implementation as the underlying behavior for controlling the pendulum arm.

The simulation uses a simple forward-Euler simulation.
The Ptolemy II model is more accurate because it uses an RK-45 solver.


## Repository Structure

- **[visualization](/visualization)**: Contains a web page with a 3D visualization of the Furuta pendulum that can replay stored execution samples and can connect to live simulation of a controller.
- **[facil.io](/facil.io)**: The [facil.io](https://github.com/boazsegev/facil.io) library used to setup a websocket connection between the live simulation and the visualization front-end.
- **[gnuplot](/gnuplot)**: The [gnuplot](http://www.gnuplot.info/) configuration used to generate static plots for produced samples.
- **[impl](/impl)**: The underlying C implementation for the control behavior, simulation, and visualization server used in the examples.
- **[lf](/lf)**: The Lingua France model variants.
    - **[classic](/lf/classic)**: A variant that uses only classical language elements.
    - **[modes](/lf/modes)**: A variant that uses a [modal reactor](https://www.lf-lang.org/docs/handbook/modal-models?target=c) to model the different pendulum control modes.
    - **[modes-nested](/lf/modes-nested)**: A variant that uses a two nested [modal reactors](https://www.lf-lang.org/docs/handbook/modal-models?target=c) to model the pendulum control modes and the LED state.
    - **[scchart-embedded](/lf/scchart-embedded)**: A variant that embeds an SCCharts with dynamic ticks to handle the behavior of the controller.
- **[sccharts](/sccharts)**: The SCCharts model variants.
    - **[classic](/lf/classic)**: A variant that uses only classical language elements and represents time in the multiform notion.
    - **[dynamic-ticks](/lf/dynamic-ticks)**: A variant that uses [Timed SCCharts](https://github.com/kieler/semantics/wiki/Syntax:-Timed-Automata) features to model timing aspects and dynamic ticks for a more efficient execution.
- **[run.py](/run.py)**: A Python script that helps in compiling and running the different programs.

## Executing the Examples

The Python script can be used to automatically compile and run the various model variants.
It can run all or a specific set of samples producing runtime results that can be replayed and inspected in the visualization, as well as static plots for the collected data.
Run `python run.py sample all` to produce samples for all variants.
The results will be located in a `plot` sub-directory of each model.

Additionally, the script can start a live simulation for some of the model variants, e.g. via `python run.py live lf-modes`.

### Requirements

- Python version 3
- Java version 17+
- GCC
- make
- gunplot

### Compatibility

- The Python script was only tested on a Linux system but is likely to run on MacOS. Yet, there are no provisions for supporting Windows.
- The Python script will expect the required commands to be available on the PATH.
- The models in this repository might not be compatible to the latest versions of the Lingua Franca and SCCharts compiler. They work with the versions attached to the respective [release of this repository](https://github.com/a-sr/furuta-pendulum/releases). The Python script is able to automatically download them and use them to compile the models.

### Preview

A preview of the visualization of a Lingua Franca sample using modal reactors is available [here](https://a-sr.github.io/furuta-pendulum/visualization.html?load=https://a-sr.github.io/furuta-pendulum/pendulum-example.csv).
