#include <iostream>
#include "Fisica_Induccion.h"
using namespace std;
/*
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
*/
using namespace TFFisicaCCCLR;

int main() {
	//La clase de mi formulario tendr� el nombre acu�ado
	//en el paso anterior
	//Instanciamos un puntero a un nuevo objeto de la clase
	//formulario que creamos
	Fisica_Induccion^ form = gcnew Fisica_Induccion;
	//Solicitamos a la aplicaci�n que ejecute el formulario
	Application::Run(form);
	return 0;
}