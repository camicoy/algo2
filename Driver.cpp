#include "Driver.h"
//#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver() {

	red = Red();
	dcnet = 0;
	idPaq = 0;

}

Driver::~Driver() {
    // TODO
    if(dcnet != 0){
        int i = 1;
        while(i < red.UltId()+1){
            Cola< ::Paquete>* co = dcnet -> colaDe(i);
            while(!(co -> vacio())){
                ::Paquete* p = &(co -> obtenerMaxPrior());
                co -> eliminar();
                delete p;
            }
            i++;
        }
        delete dcnet;
    }
}

// TAD RED
Nat Driver::CantidadComputadoras() {
    // TODO

    return red.Computadoras().Cardinal();


}

const Computadora& Driver::IesimaComputadora(const Nat i) {
    // TODO
	int aux=i+1;
	return red.ConvertirIdaIp(aux);
}

Nat Driver::CantidadInterfacesDe(const Computadora& c) {
    // TODO
    int Id = red.ConvertirIpaId(c);
    return red.Interfaces(Id).Cardinal();

}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i){
    // TODO
    int Id = red.ConvertirIpaId(c);
    //Conj<int> interfaces = red.Interfaces(Id);
    Conj<int>::Iterador it = red.Interfaces(Id).CrearIt();
    int aux = 0;
    while(it.HaySiguiente() && aux != i){
		it.Avanzar();
		aux++;
	}
    return it.Siguiente();

}

const Interfaz Driver::IntefazUsada(const Computadora& c1, const Computadora& c2){
    int Idc1 = red.ConvertirIpaId(c1);
    int Idc2 = red.ConvertirIpaId(c2);
    Conj<int> Interc1 = red.Interfaces(Idc1);
    Conj<int> Interc2 = red.Interfaces(Idc2);
    Compu C1(c1,Interc1);
    Compu C2(c2,Interc2);
    int resultado = red.InterfazUsada(C1,C2);
    return resultado;
}

bool Driver::conectadas(const Computadora& c1, const Computadora& c2){
    // TODO
    int Idc1 = red.ConvertirIpaId(c1);
    int Idc2 = red.ConvertirIpaId(c2);
    Conj<int> Interc1 = red.Interfaces(Idc1);
    Conj<int> Interc2 = red.Interfaces(Idc2);
    Compu C1 = Compu(c1,Interc1);
    Compu C2 = Compu(c2,Interc2);
    bool res = red.Conectadas(C1,C2);
    return res;
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    // TODO
    string ip2 = ip;
    Conj<int> in = ci;
    Compu c = Compu(ip2,in);
    red.Agregar(c);
}

void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    // TODO
    int Idc1 = red.ConvertirIpaId(c1);
    int Idc2 = red.ConvertirIpaId(c2);
    Conj<int> Interc1 = red.Interfaces(Idc1);
    Conj<int> Interc2 = red.Interfaces(Idc2);
    Compu C1 = Compu(c1,Interc1);
    Compu C2 = Compu(c2,Interc2);
    red.Conectar(C1,C2,i1,i2);
}


Nat Driver::CantidadNodosRecorridosPor(const Paquete& p){
    // TODO
    Conj<Compu> comps = red.Computadoras();
    Conj<Compu>::Iterador iter = comps.CrearIt();
    bool encontre = false;
    ::Paquete paq = ::Paquete();
    while(iter.HaySiguiente() && !encontre){
		Compu* itSig=(Compu*) (&(iter.Siguiente()));
		conjPaquete::iterador it = dcnet -> enEspera(*itSig).crearIt();
		while(it.haySiguiente() && !encontre){
			if(it.siguiente().id() == p){
				encontre = true;
				paq = it.siguiente();
			}
			it.avanzar();
		}
		iter.Avanzar();
    }
    return dcnet -> caminoRecorrido(paq).Longitud();
}

const Computadora Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i){
    // TODO
    Conj<Compu> comps = red.Computadoras();
    Conj<Compu>::Iterador iter = comps.CrearIt();
    bool encontre = false;
    ::Paquete paq;
    while(iter.HaySiguiente() && !encontre){
		Compu* itSig=(Compu*) (&(iter.Siguiente()));
		conjPaquete::iterador it = dcnet -> enEspera(*itSig).crearIt();
		while(it.haySiguiente() && !encontre){
		  if(it.siguiente().id() == p){
			encontre = true;
			paq = it.siguiente();
		  }
		  it.avanzar();
		}
		iter.Avanzar();
    }
    return (dcnet -> caminoRecorrido(paq)[i]).Ip();
}

Nat Driver::CantidadEnviadosPor(const Computadora& c){
    // TODO
    int Idc = red.ConvertirIpaId(c);
    Conj<int> Interc = red.Interfaces(Idc);
    Compu C = Compu(c,Interc);
    return dcnet -> cantidadEnviados(C);
}

Nat Driver::CantidadEnEsperaEn(const Computadora& c){
    // TODO
    int Idc = red.ConvertirIpaId(c);
    Conj<int> Interc = red.Interfaces(Idc);
    Compu C = Compu(c,Interc);
    return dcnet -> enEspera(C).cardinal();
}


ostream& operator<<(ostream& os, conjPaquete& c){
	os << '{';
    conjPaquete::iterador iter = c.crearIt();
    while(iter.haySiguiente()){
		os << iter.siguiente();
		iter.avanzar();
		if(iter.haySiguiente()){
			os << ',';	
		}
	}
	return os << '}';
}

const Paquete Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i){
    // TODO
    int Idc = red.ConvertirIpaId(c);
    Conj<int> Interc = red.Interfaces(Idc);
    //~ cout << "interfaces de red" << red.Interfaces(Idc) <<endl;
    Compu C = Compu(c,Interc);
    //~ cout<< "booga 1" << dcnet -> enEspera(C) << endl <<endl;
    //~ cout<< "booga 2" << dcnet -> enEspera(C) << endl <<endl;
    conjPaquete::iterador it = dcnet -> enEspera(C).crearIt();
    int aux = 0;
    while(it.haySiguiente() && aux != i){
		it.avanzar();
		aux++;
	}
	return it.siguiente().id();
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    // TODO
    if(dcnet == 0){
		dcnet = new DcNet(&red);
	}// Supongo que no se utiliza dcnet hasta que se agrega por lo menos un paquete
    int IdO = red.ConvertirIpaId(origen);
    int IdD = red.ConvertirIpaId(destino);
    Conj<int> InterO = red.Interfaces(IdO);
    Conj<int> InterD = red.Interfaces(IdD);
    Compu o = Compu(origen,InterO);
    Compu d = Compu(destino,InterD);
    ::Paquete* p = new ::Paquete(idPaq,prioridad,o,d);
    idPaq=idPaq+1;
    dcnet -> crearPaquete(*p);
}

void Driver::AvanzarSegundo() {
    // TODO
    dcnet -> avanzarSegundo();

}

const Computadora& Driver::laQueMasEnvio() {
    // TODO
    return dcnet -> laQueMasEnvio().Ip();
}

const Computadora& Driver::origen(const Paquete& p){
    // TODO
    Conj<Compu>::Iterador iter = red.Computadoras().CrearIt();
    bool encontre = false;
    ::Paquete paq = ::Paquete();
    while(iter.HaySiguiente() && !encontre){
		Compu* itSig=(Compu*) (&(iter.Siguiente()));
		conjPaquete::iterador it = dcnet -> enEspera(*itSig).crearIt();
		while(it.haySiguiente() && !encontre){
			if(it.siguiente().id() == p){
				encontre = true;
				paq = it.siguiente();
			}
			it.avanzar();
		}
		iter.Avanzar();
    }
    return paq.origen();
}

const Computadora& Driver::destino(const Paquete& p){
    // TODO
    Conj<Compu>::Iterador iter = red.Computadoras().CrearIt();
    bool encontre = false;
    ::Paquete paq = ::Paquete();
    while(iter.HaySiguiente() && !encontre){
		Compu* itSig=(Compu*) (&(iter.Siguiente()));
		conjPaquete::iterador it = dcnet -> enEspera(*itSig).crearIt();
		while(it.haySiguiente() && !encontre){
			if(it.siguiente().id() == p){
				encontre = true;
				paq = it.siguiente();
			}
			it.avanzar();
		}
		iter.Avanzar();
    }
    return paq.destino();
}

Nat Driver::prioridad(const Paquete p) {
    // TODO
    Conj<Compu> comps = red.Computadoras();
    Conj<Compu>::Iterador iter = comps.CrearIt();
    bool encontre = false;
    ::Paquete paq = ::Paquete();
    while(iter.HaySiguiente() && !encontre){
		Compu* itSig=(Compu*) (&(iter.Siguiente()));
		conjPaquete::iterador it = dcnet -> enEspera(*itSig).crearIt();
		while(it.haySiguiente() && !encontre){
			if(it.siguiente().id() == p){
				encontre = true;
				paq = it.siguiente();
			}
			it.avanzar();
		}
		iter.Avanzar();
    }
    return paq.prioridad();
}

} // namespace aed2

