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
	Fisica_Induccion^ form = gcnew Fisica_Induccion;
	Application::Run(form);
	return 0;
}