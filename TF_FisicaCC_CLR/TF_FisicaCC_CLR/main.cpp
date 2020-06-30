#include <iostream>
#include "faraday.hpp"
#include "mathp.hpp"
using namespace std;
using namespace System;
/*
Del Frogger de Progra 1, borrado XD (Milagros de Drive)
struct Personaje {
	void definirCaja(char forma[2][2]) {
		for (short i = 0; i < 2; i++)
			for (short j = 0; j < 2; j++) caja[i][j] = forma[i][j];
	}
	void validarMovimiento(Escenario &esc, char dir) {
		short res = 0;
		for (short i = 0; i < 2; i++)
			for (short j = 0; j < 2; j++)
				if (x + j < 0 || x + j >= esc.columnas
					|| y + i < 0 || y + i >= esc.filas && (caja[i][j] != 0))
					res++;
		if (res) {
			switch (dir) {
			case Arriba:y++; break;
			case Izquierda:x++; break;
			case Abajo:y--; break;
			case Derecha:x--; break;
			default:break;
			}
		}
	}
	void borrar(Escenario &esc) {
		for (short i = 0; i < 2; i++)
			for (short j = 0; j < 2; j++)
				esc.imprimirCuadro(x + j, y + i);
	}
};
*/

void borrar(vec3 pos) {
	Console::SetCursorPosition(pos.x, pos.y);
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	cout << " ";
}
void borrar(short x, short y) {
	Console::SetCursorPosition(x, y);
	Console::ForegroundColor = ConsoleColor::White;
	Console::BackgroundColor = ConsoleColor::Black;
	cout << " ";
}

class detector {
	vec3 posicion;
	bool caja[2][4] = {
		{ 1,1,1,0 },
		{ 1,1,1,1},
	};
	polinomio* B;
public:
	void imprimir() {
		for (short i = 0; i < 2; i++)
			for (short j = 0; j < 4; j++)
				if (caja[i][j] != 0) {
					Console::SetCursorPosition(posicion.x + j, posicion.y + i);
					Console::BackgroundColor = ConsoleColor::Gray;
					Console::ForegroundColor = ConsoleColor::Black;
					cout << "=";
				}
		Console::ForegroundColor = ConsoleColor::White;
		Console::BackgroundColor = ConsoleColor::Black;
	}
	void borrarr() {
		for (short i = 0; i < 2; i++)
			for (short j = 0; j < 4; j++)
				if (caja[i][j] != 0) {
					borrar(this->posicion.x + j, this->posicion.y + i);
				}
	}
	void mover(vec3 direccion) {
		this->posicion.selfSuma(&direccion);
	}
};

class controlador {
	ushort t;
	detector* detec;
public:
	controlador(detector* detec): detec(detec), t(0) {

	}
};

int main() {

	system("pause");
	return 0;
}