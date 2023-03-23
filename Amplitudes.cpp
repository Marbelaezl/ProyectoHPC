#include"Spacetime/Spinor.h"
#include"Spacetime/Rotation.h"
#include"Spacetime/ThreeVector.h"
#include<cmath>
#include<complex>
#include<Eigen/Dense>
#include <fstream>

/* class particula{
	const unsigned int J;
	const int M;
	particula(unsigned int j, int m): J(j),M(m){};
	auto spinor();
}; */




//El spin se controla desde aquí porque los spinores requieren ser iniciados con constantes de tipo unsigned int. Si se inicia luego, el constructor de spinores devuelve "Error: 2J+1 is not a constant expression"

//Función que calcula la amplitud compleja del decaimiento
double prob(int,int,int, double, double);
double prob0(int,int, double, double);
double prob1(int,int, double, double);
double prob2(int,int, double, double);
double prob3(int,int, double, double);


int main(){
//Se declaran e inician en su valor mínimo las variables que se van a usar. J es spin, M es helicidad inicial, la1 es helicidad de la partícula 1, la 2 es helicidad de la partícula 2.
int J=0,M=0,la1=0,la2=0,lambda=0;
//IMPORTANTE: lambda NO ES UN PARÁMETRO LIBRE. ES LA HELICIDAD DE EL ESTADO FINAL, IGUAL A la1-la2

//Inicialización de prueba
J=3;M=2;la1=2;la2=-1; lambda=la1-la2;

constexpr int tst=1;
Spinor<2*tst+1> cosa;



//Se crea el archivo de salida con los títulos en los ejes. El formato de datos que uso es una lista de todos los puntos (theta,phi,P) y los grafico con ax.plot_trisurface() en el archivo de python
std::ofstream Datos("datos.dat");
Datos<<"Theta, Phi, P" <<std::endl;

//IMPORTANTE: EL ALGORITMO ES O(n²) CON RESPECTO A PUNTOS. NO ES EL NÚMERO TOTAL; ES EL NÚMERO DE PUNTOS POR EJE
int puntos=100;
//Se inicializan theta y phi por si acaso
double theta,phi;
for (int i=0;i<puntos; i++){
	for (int j=0;j<puntos;j++){
	theta= 2*i*M_PI/puntos;
	phi= 2*j*M_PI/puntos;
	Datos<<theta<<","<<phi<<","<<prob(J,M,lambda,theta,phi)<<std::endl; 
	
	}
}
Datos.close();

return 0;
}

//Zona de definición de funciones:


double prob(int J, int M,int m, double theta, double phi){
//La única forma que encontré de iniciar los spinores sin que se rompiera fue así, porque ninguna otra manera dejaba iniciar diferentes estados de spin. Si alguien lo puede traducir a una template (y que siga dejando el parámetro J como variable), sería bueno y útil pero no importante ni urgente. Se dejan solo las posibilidades para J 0, 1 , 2 y 3 porque son las observadas en la naturaleza.
switch(J){
case 3:
return prob3(M,m,theta,phi);break;
case 2:
return prob2(M,m,theta,phi);break;
case 1:
return prob1(M,m,theta,phi);break;
case 0:
return prob0(M,m,theta,phi);break;
default:
std::cout<<"Error: Solo se han implementado partículas con spin 0, 1/2, 1 y 3/2. Lamentablemente, no se aceptan gravitones";
return 0.0;}

}

double prob0(int M,int m, double theta, double phi){
//Calcula la amplitud compleja a lo largo de cierto theta y phi para el estado inicial (J,M) y el estado final (J,m). La salida por defecto es 0
static const unsigned int J=0;
//POSIBLE ERROR: Las distribuciones angulares que probé son independientes de phi, pero no sé si esto sea el comportamiento esperado. Si se cambia el eje de rotación aparece una dependencia, por lo que realmente no tengo punto de referencia para saber si esto es esperado
//Primero: M no puede exceder J porque el spin a lo largo de z sería mayor que el total. Se implementa la condición como barrera para el usuario.
if (abs(M)>J){std::cout<<"Error en la función Amplitud: la helicidad inicial("<<M<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Lo mismo pero para m
if (abs(m)>J){std::cout<<"Error en la función Amplitud: la helicidad final("<<m<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Se definen los spinores de estado inicial y final, que son 0 en todos los componentes excepto el M para el inicial y m para el final, en donde es 1
//El spinor de un estado puro es 1 en el componente de spin correspondiente y 0 en los demás. Ejemplos:
// Para una partícula de spin 1/2, la configuración + es (1,0,0), la 0 es (0,1,0) y la - es (0,0,1)
Spinor <(2*J+1)> Xi,Xf;
// Esta implementación garantiza que va en la posición adecuada: 0 para M=J, 1 para M = J-1, ..., 2J para M=-J
Xi[J-M]=1;
Xf[J-m]=1;
//Se define la rotación cuya matriz se va a hallar. Como la rotación es de theta radianes, la magnitud del vector debe ser theta. El eje es el que aparece en el libro.
Rotation rot(ThreeVector (-sin(phi)*theta,cos(phi)*theta,0));
std::complex<double> res=sqrt((2*J+1.0)/(4* M_PI))*(rot*Xf).adjoint()*Xi;
return std::norm(res);
}
double prob1(int M,int m, double theta, double phi){
//Calcula la amplitud compleja a lo largo de cierto theta y phi para el estado inicial (J,M) y el estado final (J,m). La salida por defecto es 0
static const unsigned int J=1;
//POSIBLE ERROR: Las distribuciones angulares que probé son independientes de phi, pero no sé si esto sea el comportamiento esperado. Si se cambia el eje de rotación aparece una dependencia, por lo que realmente no tengo punto de referencia para saber si esto es esperado
//Primero: M no puede exceder J porque el spin a lo largo de z sería mayor que el total. Se implementa la condición como barrera para el usuario.
if (abs(M)>J){std::cout<<"Error en la función Amplitud: la helicidad inicial("<<M<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Lo mismo pero para m
if (abs(m)>J){std::cout<<"Error en la función Amplitud: la helicidad final("<<m<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Se definen los spinores de estado inicial y final, que son 0 en todos los componentes excepto el M para el inicial y m para el final, en donde es 1
//El spinor de un estado puro es 1 en el componente de spin correspondiente y 0 en los demás. Ejemplos:
// Para una partícula de spin 1/2, la configuración + es (1,0,0), la 0 es (0,1,0) y la - es (0,0,1)
Spinor <(2*J+1)> Xi,Xf;
// Esta implementación garantiza que va en la posición adecuada: 0 para M=J, 1 para M = J-1, ..., 2J para M=-J
Xi[J-M]=1;
Xf[J-m]=1;
//Se define la rotación cuya matriz se va a hallar. Como la rotación es de theta radianes, la magnitud del vector debe ser theta. El eje es el que aparece en el libro.
Rotation rot(ThreeVector (-sin(phi)*theta,cos(phi)*theta,0));
std::complex<double> res=sqrt((2*J+1.0)/(4* M_PI))*(rot*Xf).adjoint()*Xi;
return std::norm(res);
}
double prob2(int M,int m, double theta, double phi){
//Calcula la amplitud compleja a lo largo de cierto theta y phi para el estado inicial (J,M) y el estado final (J,m). La salida por defecto es 0
static const unsigned int J=2;
//POSIBLE ERROR: Las distribuciones angulares que probé son independientes de phi, pero no sé si esto sea el comportamiento esperado. Si se cambia el eje de rotación aparece una dependencia, por lo que realmente no tengo punto de referencia para saber si esto es esperado
//Primero: M no puede exceder J porque el spin a lo largo de z sería mayor que el total. Se implementa la condición como barrera para el usuario.
if (abs(M)>J){std::cout<<"Error en la función Amplitud: la helicidad inicial("<<M<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Lo mismo pero para m
if (abs(m)>J){std::cout<<"Error en la función Amplitud: la helicidad final("<<m<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Se definen los spinores de estado inicial y final, que son 0 en todos los componentes excepto el M para el inicial y m para el final, en donde es 1
//El spinor de un estado puro es 1 en el componente de spin correspondiente y 0 en los demás. Ejemplos:
// Para una partícula de spin 1/2, la configuración + es (1,0,0), la 0 es (0,1,0) y la - es (0,0,1)
Spinor <(2*J+1)> Xi,Xf;
// Esta implementación garantiza que va en la posición adecuada: 0 para M=J, 1 para M = J-1, ..., 2J para M=-J
Xi[J-M]=1;
Xf[J-m]=1;
//Se define la rotación cuya matriz se va a hallar. Como la rotación es de theta radianes, la magnitud del vector debe ser theta. El eje es el que aparece en el libro.
Rotation rot(ThreeVector (-sin(phi)*theta,cos(phi)*theta,0));
std::complex<double> res=sqrt((2*J+1.0)/(4* M_PI))*(rot*Xf).adjoint()*Xi;
return std::norm(res);
}
double prob3(int M,int m, double theta, double phi){
//Calcula la amplitud compleja a lo largo de cierto theta y phi para el estado inicial (J,M) y el estado final (J,m). La salida por defecto es 0
static const unsigned int J=3;
//POSIBLE ERROR: Las distribuciones angulares que probé son independientes de phi, pero no sé si esto sea el comportamiento esperado. Si se cambia el eje de rotación aparece una dependencia, por lo que realmente no tengo punto de referencia para saber si esto es esperado
//Primero: M no puede exceder J porque el spin a lo largo de z sería mayor que el total. Se implementa la condición como barrera para el usuario.
if (abs(M)>J){std::cout<<"Error en la función Amplitud: la helicidad inicial("<<M<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Lo mismo pero para m
if (abs(m)>J){std::cout<<"Error en la función Amplitud: la helicidad final("<<m<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Se definen los spinores de estado inicial y final, que son 0 en todos los componentes excepto el M para el inicial y m para el final, en donde es 1
//El spinor de un estado puro es 1 en el componente de spin correspondiente y 0 en los demás. Ejemplos:
// Para una partícula de spin 1/2, la configuración + es (1,0,0), la 0 es (0,1,0) y la - es (0,0,1)
Spinor <(2*J+1)> Xi,Xf;
// Esta implementación garantiza que va en la posición adecuada: 0 para M=J, 1 para M = J-1, ..., 2J para M=-J
Xi[J-M]=1;
Xf[J-m]=1;
//Se define la rotación cuya matriz se va a hallar. Como la rotación es de theta radianes, la magnitud del vector debe ser theta. El eje es el que aparece en el libro.
Rotation rot(ThreeVector (-sin(phi)*theta,cos(phi)*theta,0));
std::complex<double> res=sqrt((2*J+1.0)/(4* M_PI))*(rot*Xf).adjoint()*Xi;
return std::norm(res);
}
