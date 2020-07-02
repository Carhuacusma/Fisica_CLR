#pragma once

#include <iostream>
#include "faraday.hpp"
//===================== README ==========================
//Este es un ejemplo m�s parecido al ejercicio de la PC2.
//Prop�sito: comprobar la funcionalidad de las librer�as.
//Douzo.

using namespace std;
using namespace faraday;
class ce_control {
	ce_conjEspiras* espiras;
	ce_campo* campo;
	polinomio* flujo, *fem;
	void menuVector(vec3* v) {
		char op;
		cout << "A. Vector Canonico" << endl << "B. Ingresar" << endl; 
		do { cout << "Ingrese: "; cin >> op; op = toupper(op); } while (!(op == 'A' || op == 'B'));
		if (op == 'A') {
			cout << "Bajo el esquema i, j , k" << "Ingrese: "; 
			cin >> op; op = tolower(op);
			short coef;
			cout << "Orientaci�n ( 1 | -1| 0 )"; cin >> coef;
			v = new vec3(op, coef);
		}else {
			double x, y, z;
			cout << "x: "; cin >> x;
			cout << "y: "; cin >> y;
			cout << "z: "; cin >> z;
			v = new vec3(x, y, z);
		}
	}
public:
	ce_control(ce_conjEspiras* Espiras, ce_campo* campoElec) : espiras(Espiras), campo(campoElec), flujo(nullptr), fem(nullptr) { }
	void creaEspiras(unsigned short nEspiras, double area) {
		this->espiras = new ce_conjEspiras(nEspiras, area);
	}
	void creaEspiras(unsigned short nEspiras, double area, vec3* dirN) {
		this->espiras = new ce_conjEspiras(nEspiras, area, dirN);
	}
	void creaCampo(polinomio* B, vec3* dirB) { this->campo = new ce_campo(B, dirB); }
	//TO DO: menu creacion Campo
	void menuCreacionEspira() {
		double nEspiras, area;
		cout << "Sobre las espiras: " << endl;
		do {
			cout << "N: "; cin >> nEspiras;
		} while (nEspiras <= 0);
		cout << "Sobre el area: " << endl;
		char op;
		do {
			cout << "�Es circulo? (S/N): "; cin >> op;
			op = toupper(op);
		} while (!(op != 'Y' || op != 'N'));
		if (op == 'Y') {
			cout << "Ingrese el radio: "; cin >> area;
			area = area * M_PI;
		}else { cout << "Ingrese el area: "; cin >> area; }
		cout << "Sobre la normal del �rea: ";
		vec3* normal = nullptr;
		this->menuVector(normal);
		this->espiras = new ce_conjEspiras(nEspiras, area, normal);
	}
	void menuCreacionCampo() {

	}

	void calcFlujo() { 
		//...........................................B          *         A          * cosTheta(Angulo entre B y A)
		this->flujo = new polinomio(multiplicacion(campo->getB(), espiras->getArea() * cosTheta(campo->getDir(),espiras->getNormal())));
	}
	void calcFem() {
		if (flujo) {
			polinomio* dFdT = new polinomio(derivada(flujo));
			dFdT->selfMultiplicar(this->espiras->getN()*-1);
			this->fem = new polinomio(dFdT, true);
			delete dFdT;
		}
	}
	double calcFlujo(double t) {
		if(flujo) return flujo->resultado(t);
		return 0;
	}
	double calcFem(double t) {
		if (fem) return fem->resultado(t);
		return 0;
	}
	
	void resultados(double t) {
		cout << "A los " << t << "segundos: " << endl;
		cout << "Flujo:" << this->calcFlujo(t) << endl;
		cout << "Fem:" << this->calcFem(t) << endl;
	}

	void secuencia() {
		this->calcFlujo();
		this->calcFem();
		cout << ">> Flujo: "; this->flujo->mostrar('t');
		cout << ">> Fem: "; this->fem->mostrar('t');
		cout << "==========================================" << endl;
		this->resultados(0);
		this->resultados(10);
		this->resultados(15);
	}
};