<<<<<<< HEAD
#pragma once
#include "mathp.hpp"

namespace faraday {
#pragma region clases
	class ce_campo {
		polinomio* B;
		vec3* dirB;
	public:
		ce_campo(polinomio* b, vec3* dB) : B(b), dirB(dB) { }
		~ce_campo() {
			delete this->B;
			delete this->dirB;
		}

		polinomio* getB() { return this->B; }
		vec3* getDir() { return this->dirB; }
	};
	class ce_conjEspiras {
		unsigned short N; // N espiras
		double A;
		vec3* dirNA; // La dirección de la normal de área
	public:
		ce_conjEspiras(unsigned short n, double a, vec3* dir) : N(n), A(a), dirNA(dir) { }
		ce_conjEspiras(unsigned short n, double a, double dir1 = 0, double dir2 = 1, double dir3 = 0) : N(n), A(a) {
			this->dirNA = new vec3(dir1, dir2, dir3);
			//Por defecto la Normal sería 'j' (Eje Y positivo)
		}
		~ce_conjEspiras() { delete this->dirNA; }

		double getArea() { return this->A; };
		unsigned short getN() { return this->N; }
		vec3* getNormal() { return this->dirNA; }
	};
#pragma endregion
	double fem(double N, double dF, double dt) {
		return -1 * (N * dF) / dt;
	}
	
	//Flujo = A*B*cos(theta)
	polinomio flujo(polinomio* B, double A, float theta, short sist = MP_RAD) {
		double m;
		switch (sist){
		case MP_RAD: m = A * std::cos(theta);
		case MP_DEG: m = A * std::cos(theta*(180.0 / M_PI));
		default:
			break;
		}
		return multiplicacion(B, m);
	}
=======
#pragma once
#include "mathp.hpp"

namespace faraday {
#pragma region clases
	class ce_campo {
		polinomio* B;
		vec3* dirB;
	public:
		ce_campo(polinomio* b, vec3* dB) : B(b), dirB(dB) { }
		~ce_campo() {
			delete this->B;
			delete this->dirB;
		}

		polinomio* getB() { return this->B; }
		vec3* getDir() { return this->dirB; }
	};
	class ce_conjEspiras {
		unsigned short N; // N espiras
		double A;
		vec3* dirNA; // La dirección de la normal de área
	public:
		ce_conjEspiras(unsigned short n, double a, vec3* dir) : N(n), A(a), dirNA(dir) { }
		ce_conjEspiras(unsigned short n, double a, double dir1 = 0, double dir2 = 1, double dir3 = 0) : N(n), A(a) {
			this->dirNA = new vec3(dir1, dir2, dir3);
			//Por defecto la Normal sería 'j' (Eje Y positivo)
		}
		~ce_conjEspiras() { delete this->dirNA; }

		double getArea() { return this->A; };
		unsigned short getN() { return this->N; }
		vec3* getNormal() { return this->dirNA; }
	};
#pragma endregion
	double fem(double N, double dF, double dt) {
		return -1 * (N * dF) / dt;
	}
	
	//Flujo = A*B*cos(theta)
	polinomio flujo(polinomio* B, double A, float theta, short sist = MP_RAD) {
		double m;
		switch (sist){
		case MP_RAD: m = A * std::cos(theta);
		case MP_DEG: m = A * std::cos(theta*(180.0 / M_PI));
		default:
			break;
		}
		return multiplicacion(B, m);
	}
>>>>>>> a8ece0039ce3e972cec4ed746d34e3aa2b84a3eb
}