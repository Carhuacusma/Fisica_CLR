#pragma once
#ifndef SIMULACION_HPP
#define SIMULACION_HPP

#include <string>
#include <vector>
#include "faraday.hpp"

using namespace std;

enum tipoMat {
	Plata = 0, Cobre, Oro, Aluminio, Tungsteno,
	Hierro, Platino, Plomo, Carbon, Vidrio, Azufre,
	CuarzoF
};
double resistividad(tipoMat material);
class objeto {
	//ASUME: Temperatura T0 = 20° C
	// Basado en: https://www.fisic.ch/contenidos/electricidad/ley-de-ohm-y-resistencia/
	vec3 posicion, normal;
	double I; // Corriente
	double R; // Electricidad
	double A; // Area
	tipoMat tipo;
public:
	objeto(vec3 posicion, double A, tipoMat tipo, double dir1 = 0, double dir2 = 1, double dir3 = 0): posicion(posicion), A(A), tipo(tipo) {
		// No es exactamente la resistencia del material estoy 
		// simplificando la ecuación de la resistencia en un cable
		this->R = resistividad(tipo) / this->A;
		this->normal = vec3(dir1, dir2, dir3);
		//Por defecto la Normal sería 'j' (Eje Y positivo)
	}
	objeto(vec3 posicion, double A, double R) : posicion(posicion), R(R) {}
	double getI();
	double getR();
	double getA();
	vec3 getNormal();
	vec3 getPos();
	void setA(double nuevoA);
	void mover(vec3 direccion);
	string getTipo();
};
//Por defecto B: I/R^2 ---> I*R^(-2)
class detector {
	vec3 posicion;
	vec3 dirB;
	polinomio* B;
	polinomio* flujo, * fem;
	void calcFlujo(objeto* obj);
	void calcFem(objeto* obj);
public:
	detector() {
		this->posicion = vec3(0,0,0);
		double* c = new double[1];
		float* e = new float[1];
		this->B = new polinomio(1, c, e, true); // copiar = true (Crea otros punteros dentro, para su destructor)
		delete[] c; delete[] e;	
	}
	detector(vec3 pos): posicion(pos) {
		double* c = new double[1];
		float* e = new float[1];
		this->B = new polinomio(1, c, e, true); // copiar = true (Crea otros punteros dentro, para su destructor)
		delete[] c; delete[] e;	
	}
	void mover(vec3 direccion);
	vec3 getPosicion();
	double getBRes(double x);
	double calcFlujo(bool segunDistancia, objeto* obj, double x = 0);
	double calcFem(bool segunDistancia, objeto* obj, double x = 0);
};

class controlador {
	ushort t;
	detector* detec;
	vector<objeto*>* objEj;
public:
	controlador() : t(0) { detec = new detector; this->objEj = new vector<objeto*>; }
	controlador(vec3* posDetector): t(0) { detec = new detector(posDetector); this->objEj = new vector<objeto*>; }
	controlador(detector* detec) : detec(detec), t(0) { this->objEj = new vector<objeto*>; }
	void nuevoObjeto(vec3 posicion, double A, tipoMat tipo);
	void moverDetec(vec3& dir);
	void moverObj(vec3& dir, short i = 0);
};
#endif // !SIMULACION_HPP