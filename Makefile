Phony : Ang_distri.pdf Ang_distri.gif

Ang_distri.pdf : plot.gp datos_plot.dat
	echo "load 'plot.gp'" | gnuplot

Ang_distri.gif : plot.gp datos_plot.dat
	echo "load 'Anima.gp'" | gnuplot

datos_plot.dat: datos.dat
	awk -F "," 'BEGIN{bef = 0; now = 0} { if(NF != 1){now = $$1; if(bef != now){print "\n", $$1, $$2, $$3 } else{print $$1,$$2,$$3}; bef = $$1}}' datos.dat > datos_plot.dat

datos.dat : Amplitudes.cpp
	g++ -lSpacetime Amplitudes.cpp -o HelA
	./HelA
	rm HelA

clean :
	rm  *.pdf *.gif *.dat *~ *\# a.out
