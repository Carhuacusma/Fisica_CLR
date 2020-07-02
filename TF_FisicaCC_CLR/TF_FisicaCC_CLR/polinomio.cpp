#include "polinomio.h"
void polinomio::limpiar() {
	ushort j = 0;
	for (ushort i = 0; i < this->nter; i++) { if (this->c[i] == 0) j++; }
	this->limpiar(j);
}
void polinomio::limpiar(ushort nlimpio) {
	//Se conoce el tamaño de los nuevos arreglos
	double* coefLimpio = new double[nlimpio];
	float* expLimpio = new float[nlimpio];
	ushort j = 0;
	for (ushort i = 0; i < this->nter; i++) {
		if (this->c[i] != 0) {
			coefLimpio[j] = this->c[i];
			expLimpio[j] = this->exp[i];
			j++;
		}
	}
	delete[] this->c;
	delete[] this->exp;
	this->c = coefLimpio;
	this->exp = expLimpio;
}
//Public

	float polinomio::getExp(ushort i) { return this->exp[i]; }
	double polinomio::getCoef(ushort i) { return this->c[i]; }
	ushort polinomio::getN() { return this->nter; }
	ushort polinomio::getG() { return this->grado; }
double polinomio::resultado(double x) {
	double res = 0;
	for (ushort i = 0; i < this->nter; i++) {
		ushort e = this->exp[i];	
		double j = this->c[i];
		res += j * std::pow(x, e);
		// F(x) = primer coeficiente * (x ^ primer exponente) + segundo coeficiente * (x^segundo exponente) + ... i
	}
	return res;
}


std::string polinomio::toString(char x) {
		std::string res = " ";
		bool sigpos = false;
		for (ushort i = 0; i < this->nter; i++) {
			//Si no es el primero, añadir el signo + cuando sea positivo (Lectura humana)
			if (sigpos && this->c[i] > 0) res += "+ ";
			//Si es 1 o -1, no imprimirlo
			//BTW: PUEDE SER BORRADO, ES SUPERFLUO XD
			switch (int(this->c[i])) {
			case -1: res += "- "; break;
			case 1: break;
			default:
				res += std::to_string(this->c[i]); break;
			}
			//por otro error raro que había antes, pero lo dejo para que sea entendible
			//el string del exponente que se le va a poner a x
			std::string exp = std::to_string(this->exp[i]);
			//idk why, pero piensa que quiero usar String de namespace System
			// --- poll: Con WindowsForms como que da igual porque es muy Windows so.. normal usar su String xd
			// --------- Repito,¿quieren usar Forms?
			res += x + (std::string)"^(" + exp + (std::string)") ";
			if (!sigpos) sigpos = true; //SOLO La primera vez es falso
		}
		return res;
	}
void polinomio::mostrar(char x) { std::cout << this->toString(x); }

	void polinomio::selfDerivar() {
		ushort j = 0;	// Contador para estos nuevos arreglos
		for (ushort i = 0; i < nter; i++) {
			//...Nuevo coeficiente: c*n
			this->c[i] = this->exp[i] * this->c[i];
			//...Nuevo exponente: n-1
			this->exp[i] = this->exp[i] - 1;
			if (this->c[i] != 0) j++;
		}
		if (j < this->nter) this->limpiar(j); // Si debe tener menos miembros, limpia.
	}
	void polinomio::selfMultiplicar(double coef) {
		for (ushort i = 0; i < this->nter; i++)
			this->c[i] = this->c[i] * coef;
	}
//Out
polinomio multiplicacion(polinomio* P, double coef) {
		double* newC = new double[P->getN()];
		float* newE = new float[P->getN()];
		for (ushort i = 0; i < P->getN(); i++) {
			newC[i] = P->getCoef(i) * coef;
			newE[i] = P->getExp(i);
		}
		return polinomio(P->getN(), newC, newE);
}
polinomio derivada(polinomio* P) {
	//P(X) = a*x^0 + b*x^1 (puede saltarse, por eso vector de exponentes)
	double* newCoef = new double[P->getN()]; // Nuevos Coeficientes
	float* newExp = new float[P->getN()];	// Nuevos Exponentes
	ushort j = 0;	// Contador para estos nuevos arreglos
	for (ushort i = 0; i < P->getN(); i++) {
		//Pasa por cada miembro del polinomio
		//Regla: derivada de c*(x^n) = (c*n)*x^(n-1) || Ejem: 5x^3 -> 5*3*x^2
		//...Nuevo coeficiente: c*n
		double newCoefAux = P->getCoef(i) * P->getExp(i);
		//...Nuevo exponente: n-1
		float newExpAux = P->getExp(i) - 1;
		if (newCoefAux != 0) {
			//Siempre que el nuevo coeficiente sea diferente a 0
			//Evita guardar 0 * x, ya que no es importante
			newCoef[j] = newCoefAux;
			newExp[j] = newExpAux;
			j++;
			//Guarda en la posición j, que siempre es menor a nter original,
			//pero puede sobrar ( por los casos donde coeficiente = 0 )
		}
	}
	if (j == P->getN())
		//Si cuando derivas, la cantidad de miembros es la misma, BIEN
		return polinomio(j, newCoef, newExp);

	//Para evitar tener un último(s) término(s) que apunta a la basura
	//(Considerando eliminarlo por si se puede usar el espacio original en algo más y evitar cuatro arreglos)
	//(Ya que igual j pasa como nter que determina hasta donde llegar)
	//... Lo que sigue es un simple copiar a los nuevos arreglos donde no sobra espacio en la ram
	double* newC = new double[j];
	float* newE = new float[j];
	for (short i = 0; i < j; i++) {
		newC[i] = newCoef[i];
		newE[i] = newExp[i];
	}
	//Borra los arreglos donde sobra espacio
	delete[] newCoef;
	delete[] newExp;
	//Retorna el polinomio con espacio justo
	return polinomio(j, newC, newE);
}