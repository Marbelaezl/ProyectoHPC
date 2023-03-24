Distribucion.pdf : 3dplot.py datos.dat
	python3 3dplot.py
datos.dat : Makedatos.out
	./Makedatos.out 
Makedatos.out : Amplitudes.cpp
	g++ -I/usr/include/eigen3 Amplitudes.cpp -lSpacetime -o Makedatos.out
