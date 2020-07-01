#pragma once
#include <string>
#include "faraday.hpp"

using namespace std;

class detector {
	vec3 posicion;
	polinomio* B;
public:
	void mover(vec3 direccion) {
		this->posicion.selfSuma(&direccion);
	}
};
enum tipoMat {
	Plata = 0, Cobre, Oro, Aluminio, Tungsteno,
	Hierro, Platino, Plomo, Carbón, Vidrio, Azufre,
	CuarzoF
};
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
		this->R = pow(10, -8);
		switch (tipo) {
		case Plata:		this->R = 1.59 * this->R; break;
		case Cobre:		this->R *= 1.7; break;
		case Oro:		this->R *= 2.44; break;
		case Aluminio:	this->R *= 2.82; break;
		case Tungsteno:	this->R *= 5.6; break;
		case Hierro:	this->R *= 10; break;
		case Platino:	this->R *= 11; break;
		case Plomo:		this->R *= 22; break;
		case Carbón:	this->R = 3.5*pow(10, -5); break;
		case Vidrio:	this->R = pow(10, 12); break;
		case Azufre:	this->R = pow(10, 15); break;
		case CuarzoF:	this->R = 75*pow(10, 16); break;
		default:
			break;
		}
		this->R = R / this->A; //I'm gonna guess (?) [No es exactamente la resistencia del material 
							   // estoy simplificando la ecuación de la resistencia en un cable]
	}
	objeto(vec3 posicion, double A, double R) : posicion(posicion), R(R) {}
};

class controlador {
	ushort t;
	detector* detec;
public:
	controlador(detector* detec) : detec(detec), t(0) {

	}
};