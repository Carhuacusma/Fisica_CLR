#pragma once
#include "faraday.hpp"

class detector {
	vec3 posicion;
	polinomio* B;
public:
	void mover(vec3 direccion) {
		this->posicion.selfSuma(&direccion);
	}
};

class controlador {
	ushort t;
	detector* detec;
public:
	controlador(detector* detec) : detec(detec), t(0) {

	}
};