reset session

set terminal gif animate
set output 'Ang_ditri.gif'
set pm3d depthorder
set mapping spherical

do for [angle = 360:0:-2]{
   set view ,angle,,
   splot 'datos_plot.dat' u 2:1:3 w pm3d t 'HelAmplitudes'
}
