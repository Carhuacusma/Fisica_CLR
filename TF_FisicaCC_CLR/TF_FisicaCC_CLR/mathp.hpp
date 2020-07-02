#pragma once
#ifndef PMATH_HPP
#define PMATHP_HPP

#include <math.h>
#include <string>
#include <iostream>
#include "polinomio.h"
//CON p[Nombre] para evitar confusiones con std::math.h, tanto en macros como enum
#define MP_RAD 0
#define MP_DEG 1
//A veces math.h no declara M_PI (my case. So this)
//Thanks to: https://stackoverflow.com/questions/14920675/is-there-a-function-in-c-language-to-calculate-degrees-radians
#ifndef M_PI 
#define M_PI 3.1415926535 
#endif

typedef unsigned short ushort;

enum ftrig { psen = 0, pcos };

#pragma region Clases

class vec3 {
public:
	double x, y, z;
	vec3(char o, float signo = 1) {
		o = tolower(o);
		this->x = 0; this->y = 0; this->z = 0;
		switch (o) {
		case 'i':
			this->x = 1*signo; break;
		case 'j':
			this->y = 1*signo; break;
		case 'k':
			this->z = 1*signo; break;
		default: break;
		}
	}
	vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) { }
	vec3(vec3* vector) {
		if (vector == nullptr) {
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}else {
			this->x = vector->x;
			this->y = vector->y;
			this->z = vector->z;
		}
	}
	double magnitud();
	void selfSuma(vec3* dir);
	void selfProdVecEsc(double c);
};

//TO DO
class exptrig {
	ftrig tipo;
	polinomio* contenido;
	//Ejemplo: tipo => sen ^ contenido = {c = [5,2], e = [0,1]}
	//........ then -> exptrig: sen(5 + 2x)
public:
	//por defecto: sen(x)
	exptrig(ftrig tipo = psen): tipo(tipo) { this->contenido = new polinomio(1, new double(1), new float(1), false); }
	exptrig(polinomio* c, ftrig tipo = psen): tipo(tipo) {
		this->contenido = new polinomio(c, true);
	}

	~exptrig() {
		delete contenido;
	}
	double getResultado(double x = 1, float modo = MP_RAD) {
		double resCont = this->contenido->resultado(x);
		switch (this->tipo) {
		case psen:
			if(modo == MP_RAD) return std::sin(resCont);
			else if (modo == MP_DEG) return std::sin(resCont*(180.0 / M_PI));
		case pcos:
			if (modo == MP_RAD) return std::cos(resCont);
			else if (modo == MP_DEG) return std::cos(resCont*(180.0 / M_PI));
		}
	}
};

class expcompleja {
	polinomio* p;
	exptrig* t;
	char op; // '+' , '-' , '/' , '*'
	bool pPrimero;
public:
	expcompleja(polinomio* p, exptrig* t, char op = '*', bool primeroP = true): p(p), t(t), op(op), pPrimero(primeroP) { }
	~expcompleja() {
		delete this->p;
		delete this->t;
	}
	double getResultado(double x, float sistema = MP_RAD) {
		double res = 0;
		switch (this->op){
		case '+':
			return this->p->resultado(x) + this->t->getResultado(x, sistema);
		case '-':
			res = this->p->resultado(x) - this->t->getResultado(x, sistema);
			if (this->pPrimero) return res; else return -1 * res; break;
		case '*':
			return this->p->resultado(x) * this->t->getResultado(x, sistema);
		case '/':
			if (this->pPrimero) return this->p->resultado(x) / this->t->getResultado(x, sistema);
			else return this->t->getResultado(x, sistema) / this->p->resultado(x);
		default: return 0; break;
		}
	}
};

#pragma endregion

#pragma region Funciones

polinomio multiplicacion(polinomio* P, double coef);
//En teoría lo mejor es aplicar esto pero incluye tener funciones más grandes que solo polinomios:
//https://stackoverflow.com/questions/1559695/implementing-the-derivative-in-c-c
polinomio derivada(polinomio* P);
exptrig derivada(ushort trig, polinomio* E);

vec3 prodVecEsc(vec3* v1, double c);
vec3 suma(vec3* v1, vec3* v2);
vec3 resta(vec3* v1, vec3* v2);
double distancia(vec3* p1, vec3* p2);
#pragma endregion
//Algebra Lineal
double dotSimp(vec3* v1, vec3* v2);
double cosTheta(vec3* v1, vec3* v2);

#endif // !PMATH_HPP