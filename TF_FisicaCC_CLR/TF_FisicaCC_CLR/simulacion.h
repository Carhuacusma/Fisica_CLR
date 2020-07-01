#pragma once
#include <string>
#include "faraday.hpp"

using namespace std;

enum tipoMat {
	Plata = 0, Cobre, Oro, Aluminio, Tungsteno,
	Hierro, Platino, Plomo, Carbón, Vidrio, Azufre,
	CuarzoF
};
double resistividad(tipoMat material) {
	double R = pow(10, -8);
	switch (material) {
	case Plata:		return R * 1.59; break;
	case Cobre:		return R * 1.7; break;
	case Oro:		return R * 2.44; break;
	case Aluminio:	return R * 2.82; break;
	case Tungsteno:	return R * 5.6; break;
	case Hierro:	return R * 10; break;
	case Platino:	return R * 11; break;
	case Plomo:		return R * 22; break;
	case Carbón:	return 3.5*pow(10, -5); break;
	case Vidrio:	return pow(10, 12); break;
	case Azufre:	return pow(10, 15); break;
	case CuarzoF:	return pow(10, 16); break;
	default: return R * 159; break;
	}
}
class objeto {
	//ASUME: Temperatura T0 = 20° C
	// Basado en: https://www.fisic.ch/contenidos/electricidad/ley-de-ohm-y-resistencia/
	vec3 posicion;
	double I; // Corriente
	double R; // Electricidad
	double A; // Area
	tipoMat tipo;
public:
	objeto(vec3 posicion, double A, tipoMat tipo): posicion(posicion), A(A), tipo(tipo) {
		//I'm gonna guess (?) [No es exactamente la resistencia del material 
		// estoy simplificando la ecuación de la resistencia en un cable]
		this->R = resistividad(tipo) / this->A; 
	}
	objeto(vec3 posicion, double A, double R) : posicion(posicion), R(R) {}
	double getI() { return this->I; }
	double getR() { return this->R; }
	double getA() { return this->A; }
	void setA(double nuevoA) { 
		//Asumiendo que la resistividad se mantiene (y que R = p/A)
		this->R = (this->R * this->A) / nuevoA;
		this->A = A;
	}

};

class detector {
	vec3 posicion;
	polinomio* B;
public:
	void mover(vec3 direccion) {
		//Por defecto B: I/R^2 ---> I*R^(-2)
		this->posicion.selfSuma(&direccion);
		double* c = new double[1];
		float* e = new float[1];
		this->B = new polinomio(1, c, e, true); // copiar = true (Crea otros punteros dentro, para su destructor)
		delete[] c; delete[] e;
	}
	vec3 getPosicion() { return this->posicion; }
	
};

class controlador {
	ushort t;
	detector* detec;
	objeto* objEj;
public:
	controlador(objeto* objEj): objEj(objEj) {
		// B = I / (dist)
	}
	controlador(detector* detec, objeto* objEj) : detec(detec), t(0) {

	}

};