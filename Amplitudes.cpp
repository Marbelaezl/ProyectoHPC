#include"Spacetime/Spinor.h"
#include"Spacetime/Rotation.h"
#include"Spacetime/ThreeVector.h"
#include<cmath>
#include<complex>
#include<Eigen/Dense>
#include <fstream>


//El spin se controla desde aquí porque los spinores requieren ser iniciados con constantes de tipo unsigned int
const unsigned int J=2;

//Función que calcula la amplitud compleja del decaimiento
double prob(int,int, float, float);


int main(){
//Se declaran e inician en su valor mínimo las variables que se van a usar. J es spin, M es helicidad inicial, la1 es helicidad de la partícula 1, la 2 es helicidad de la partícula 2.
int J=1, M=0,la1=0,la2=0,lambda=0;
//IMPORTANTE: lambda NO ES UN PARÁMETRO LIBRE. ES LA HELICIDAD DE EL ESTADO FINAL, IGUAL A la1-la2


//Rotation rotacion (ThreeVector(-sin(phi)*theta,cos(phi)*theta,0));
double theta=1, phi=2;
//El spinor de un estado puro es 1 en el componente de spin correspondiente y 0 en los demás. Ejemplos:
// Para una partícula de spin 1/2, la configuración + es (1,0,0), la 0 es (0,1,0) y la - es (0,0,1)

std::ofstream Datos("datos.dat");

for (int i=0;i<10000; i++){
Datos<<i*M_PI/10000<<" "<<prob(1,2,2*i*M_PI/10000,0)<<std::endl;}


Datos.close();


return 0;
}

//Zona de definición de funciones:


double prob(int M,int m, float theta, float phi){
//Calcula la amplitud compleja a lo largo de cierto theta y phi para el estado inicial (J,M) y el estado final (J,m). La salida por defecto es 0

//Primero: M no puede exceder J porque el spin a lo largo de z sería mayor que el total. Se implementa la condición como barrera para el usuario.
if (abs(M)>J){std::cout<<"Error en la función Amplitud: la helicidad inicial("<<M<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}
//Lo mismo pero para m
if (abs(m)>J){std::cout<<"Error en la función Amplitud: la helicidad final("<<m<<") Debe ser menor o igual al spin("<<J<<")"<<std::endl; return 0;}

//Se definen los spinores de estado inicial y final, que son 0 en todos los componentes excepto el M para el inicial y m para el final, en donde es 1
Spinor <(2*J+1)> Xi,Xf;
// Esta implementación garantiza que va en la posición adecuada: 0 para M=J, 1 para M = J-1, ..., 2J para M=-J
Xi[J-M]=1;
Xf[J-m]=1;

//Se define la rotación cuya matriz se va a hallar. Como la rotación es de theta radianes, la magnitud del vector debe ser theta. El eje es el que aparece en el libro.
Rotation rot(ThreeVector (-sin(phi)*theta,cos(phi)*theta,0));

//No tengo idea de si esto funciona, pero es la implementación que le dio el autor a Xf^T (R*) Xi. Algebraicamente tiene sentido porque Xf es real y el adjunto de rot*xf será Xf* R* = Xf^T R*
std::complex<double> res=sqrt((2*J+1.0)/(4* M_PI))*(rot*Xf).adjoint()*Xi;

//Pruebas: 
/*
std::cout<<"Raíz: "<<std::endl<<sqrt((2*J+1.0)/(4* M_PI))<<std::endl;
std::cout<<"Rot.adj: "<<std::endl<<(rot*Xf).adjoint()<<std::endl;
std::cout<<"Xi: " <<std::endl<<Xi;
sst::cout<<"Resultado: " <<res<<std::endl;
*/
return std::norm(res);

}
