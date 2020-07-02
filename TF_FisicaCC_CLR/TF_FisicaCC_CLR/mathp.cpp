#include "mathp.hpp"



double vec3::magnitud() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}
void vec3::selfSuma(vec3* dir) {
		this->x = this->x + dir->x;
		this->y = this->y + dir->z;
	}
void vec3::selfProdVecEsc(double c) {
		//producto const * vector
		this->x = this->x * c;
		this->y = this->y * c;
		this->z = this->z * c;
	}

#pragma region Funciones
//En teoría lo mejor es aplicar esto pero incluye tener funciones más grandes que solo polinomios:
//https://stackoverflow.com/questions/1559695/implementing-the-derivative-in-c-c

//TODO CORREGIR PUNTERO Y &E
exptrig derivada(ushort trig, polinomio* E) {
	polinomio* newE = &derivada(E);
	switch (trig) {
	case psen:
		return exptrig(newE, pcos); // Debe ser newE*exptrig(E,pcos)
	default: break;
	}
}

#pragma region funciones básicas de vectores
vec3 prodVecEsc(vec3* v1, double c) {
	return vec3(double(v1->x * c), double(v1->y * c), double(v1->z * c));
}
vec3 suma(vec3* v1, vec3* v2) {
	return vec3(v1->x + v2->x, v1->y + v2->y, v1->z + v2->z);
}
vec3 resta(vec3* v1, vec3* v2) {
	//OKO REDUNDANCIA PORQUE BASTA suma(v1,v2*-1)
	return vec3(v1->x - v2->x, v1->y - v2->y, v1->z - v2->z);
}
double distancia(vec3* p1, vec3* p2) {
	double sum = 0;
	sum += std::pow(p1->x - p2->x, 2);
	sum += std::pow(p1->y - p2->y, 2);
	sum += std::pow(p1->z - p2->z, 2);
	return std::pow(sum, 0.5);
}
#pragma endregion

#pragma endregion

#pragma region Apuntes Algebra Lineal para Angulos
double dotSimp(vec3* v1, vec3* v2) {
	//not a simp, pero pos no usa cos xd
	//Algebra Lineal
	return (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
}
double cosTheta(vec3* v1, vec3* v2) {
	//Algebra Lineal: (u.v)/(||u||.||v||)
	return (dotSimp(v1, v2)) / (v1->magnitud() * v2->magnitud());
}
#pragma endregion