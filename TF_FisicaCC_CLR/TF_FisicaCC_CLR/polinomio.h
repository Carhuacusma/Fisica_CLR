#pragma once
#include <iostream>
#include <string>

typedef unsigned short ushort;
class polinomio{
	ushort nter;				// n terminos
	double* c;				// coeficientes
	float* exp;				// exponentes
	ushort grado;
	void limpiar();
	void limpiar(ushort nlimpio);
public:
	polinomio(ushort nterminos, double* coeficientes, float* exponentes, bool copiar = true) : nter(nterminos) {
		if (copiar) {
			this->c = new double[nterminos];
			this->exp = new float[nterminos];
			for (ushort i = 0; i < nterminos; i++) {
				this->c[i] = coeficientes[i];
				this->exp[i] = exponentes[i];
			}
		}
		else {
			this->c = coeficientes;
			this->exp = exponentes;
		}
	}
	polinomio(polinomio* p, bool copiar = true) {
		this->nter = p->getN();
		if (copiar) {
			this->c = new double[this->nter];
			this->exp = new float[this->nter];
			for (ushort i = 0; i < this->nter; i++) {
				this->c[i] = p->getCoef(i);
				this->exp[i] = p->getExp(i);
			}
		}
		else {
			this->c = p->c;
			this->exp = p->exp;
		}
	}
	polinomio(ushort nterminos) : nter(nterminos) {
		//Lit P(X) = 1 + x + x^2 + x^3
		this->c = new double[nterminos];
		this->exp = new float[nterminos];
		for (ushort i = 0; i < nterminos; i++) {
			this->c[i] = 1;
			this->exp[i] = i;
		}
	}
	~polinomio() {
		delete[] c;
		delete[] exp;
	}

	float getExp(ushort i);
	double getCoef(ushort i);
	ushort getN();
	ushort getG();
	double resultado(double x);

	std::string toString(char x = 'x');
	void mostrar(char x = 'x');

	void selfDerivar();
	void selfMultiplicar(double coef);
};

polinomio multiplicacion(polinomio* P, double coef);
polinomio derivada(polinomio* P);