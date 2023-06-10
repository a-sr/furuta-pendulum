# Gnuplot commands to generate plots from sample

## General
set terminal pdf size 6, 3.5    # Set the output format to PDF
set datafile separator ','      # CSV
set key autotitle columnhead
set xrange [0:3]

## Pendulum
set title  'Pendulum'           # Set graph title
set output 'pendulum.pdf'       # Set output file.
set xlabel 'Time (seconds)'

plot 'pendulum-sample.csv' using 1:4 with lines linetype 3 linewidth 0.5, \
     '' using 1:3 with lines linetype 4 linewidth 1.5, \
     '' using 1:6 with lines linetype 2 linewidth 2, \
     '' using 1:5 with lines linetype 1 linewidth 2

## Angles
set title  'Pendulum Angles'    # Set graph title
set output 'angles.pdf'         # Set output file.
set xlabel 'Time (seconds)'

plot 'pendulum-sample.csv' using 1:7 with lines linetype 1 linewidth 2, \
     '' using 1:8 with lines linetype 2 linewidth 2, \
     '' using 1:9 with lines linetype 3 linewidth 2, \
     '' using 1:10 with lines linetype 4 linewidth 2