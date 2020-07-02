#pragma once
#include "simulacion.h"
using namespace std;

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
	case Carbon:	return 3.5 * pow(10, -5); break;
	case Vidrio:	return pow(10, 12); break;
	case Azufre:	return pow(10, 15); break;
	case CuarzoF:	return pow(10, 16); break;
	default: return R * 159; break;
	}
}
double objeto::getI() { return this->I; }
double objeto::getR() { return this->R; }
double objeto::getA() { return this->A; }
vec3 objeto::getNormal() { return this->normal; }
vec3 objeto::getPos() { return this->posicion; }
void objeto::setA(double nuevoA) {
		//Asumiendo que la resistividad se mantiene (y que R = p/A)
		this->R = (this->R * this->A) / nuevoA;
		this->A = A;
}
	void objeto::mover(vec3 direccion) {
		this->posicion.selfSuma(&direccion);
	}
string objeto::getTipo() {
	switch (this->tipo) {
		case Plata:		return "Plata"; break;
		case Cobre:		return "Cobre"; break;
		case Oro:		return "Oro"; break;
		case Aluminio:	return "Aluminio"; break;
		case Tungsteno:	return "Tungsteno"; break;
		case Hierro:	return "Hierro"; break;
		case Platino:	return "Platino"; break;
		case Plomo:		return "Plomo"; break;
		case Carbon:	return "Carbón"; break;
		case Vidrio:	return "Vidrio"; break;
		case Azufre:	return "Azufre"; break;
		case CuarzoF:	return "Cuarzo Fundido"; break;
		default: return "No se sabe"; break;
		}
	return "No se sabe";
}

//Detector
//Por defecto B: I/R^2 ---> I*R^(-2)

	void detector::calcFlujo(objeto* obj) {
		//...........................................B          *         A          * cosTheta(Angulo entre B y A)
		this->flujo = new polinomio(multiplicacion(this->B, obj->getA() * cosTheta(&this->dirB, &obj->getNormal())));
	}
	void detector::calcFem(objeto* obj) {
		this->calcFlujo(obj);
		polinomio* dFdT = new polinomio(derivada(flujo));
		dFdT->selfMultiplicar(-1);
		this->fem = new polinomio(dFdT, true);
		delete dFdT;
	}
void detector::mover(vec3 direccion) {
		this->posicion.selfSuma(&direccion);
	}
	vec3 detector::getPosicion() { return this->posicion; }
	double detector::getBRes(double x) { return this->B->resultado(x); }
	double detector::calcFlujo(bool segunDistancia, objeto* obj, double x) {
		this->calcFlujo(obj);
		if (segunDistancia) return flujo->resultado(distancia(&this->posicion, &(obj->getPos())));
		return flujo->resultado(x);
	}
	double detector::calcFem(bool segunDistancia, objeto* obj, double x) {
		this->calcFem(obj);
		if (segunDistancia) return fem->resultado(distancia(&this->posicion, &(obj->getPos())));
		return fem->resultado(x);
	}


	void controlador::nuevoObjeto(vec3 posicion, double A, tipoMat tipo) {
		objeto* objAux = new objeto(posicion, A, tipo);
		this->objEj->push_back(objAux);
	}
	void controlador::moverDetec(vec3& dir) { this->detec->mover(dir); }
	void controlador::moverObj(vec3& dir, short i) {
		objeto* aux = this->objEj->at(i);
		aux->mover(dir);
	}
