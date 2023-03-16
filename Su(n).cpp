#include<iostream>
#include<Eigen/Dense>
#include<cmath>
#include<complex>

Eigen::MatrixXcf generator(unsigned int, unsigned int);
int main (){
for (int i=1;i<5;i++){
	for (int j=0;j<=i;j++){
	std::cout<<"generador de dimensión "<< i<<" en dirección "<<j<<": "<< std::endl<<generator(i,j)<<std::endl<<std::endl;
	
	}
}


return 0;
}


Eigen::MatrixXcf generator(unsigned int dim, unsigned int dir){
assert(dim>0);
//Genera las matrices Jx, Jy y Jz. el parámetro dir dicta la orientación: 0 para x, 1 para y, 2 para z
Eigen::MatrixXcf res(dim,dim);
bool flag=0;
for (int i=0;i<dim;i++){
	for (int j=0;j<dim;j++){
	switch(dir){
	case 0:
		if (i==(j-1)){
			res(i,j)=sqrt((j*(dim-j)))/2.0;
			}
		else if (i==(j+1)){
			res(i,j)=sqrt((dim-j-1)*(j+1))/2.0;}
		else{res(i,j)=0;}
		break;
		
	case 1:
		if (i==(j-1)){
			res(i,j)=std::complex (0.0,-sqrt((j*(dim-j)))/2.0);
			}
		else if (i==(j+1)){
			res(i,j)=std::complex(0.0,sqrt((dim-j-1)*(j+1))/2.0);}
		else{res(i,j)=0;}
		break;
	case 2:
	if(i==j){
		res(i,j)=((dim-1)/2.0-i);}
	else{res(i,j)=0.0;}
	break;
	default:
	flag=1;
	res(i,j)=0.0;
		}

	}
}
if (flag){std::cout<<"Valor inválido de dir ingresado en generator. USe 0 para x, 1 para y y 2 para z."<<std::endl;}

return res;
}

