reset session

set terminal pdf
set output 'Ang_ditri.pdf'
set pm3d depthorder
set mapping spherical


splot 'datos_plot.dat' u 2:1:3 w pm3d t 'HelAmplitudes'
