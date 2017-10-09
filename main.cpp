#include <iostream>
#include "diccLog.h"
#include "conjLog.h"

int main(){

	diccLog<int> a= diccLog<int>();
	int b = 1;
	conjPaquete conj= conjPaquete();
	//conjPaquete::iterador ite = conj.crearIt();
	diccLog<int>::iterador it = a.crearIt();
	
	a.definir(13,b);
	a.definir(53,b);
	a.definir(32,b);
	a.definir(72,b);
	a.definir(12,b);
	a.definir(2,b);
	
	std::cout<< a.claves().Cardinal() << std::endl;

	return 0;

}
