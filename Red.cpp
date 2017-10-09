#include "Red.h"

Red::Red(){
    IpaId = DiccString<int>();
    IdaIp = diccLog<string>();
    Proxim = diccLog<diccLog<pair<string*,int> > >();
    Conexiones = diccLog<diccLog<int> >();
    Interface = diccLog<aed2::Conj<int> >();
    UlId = 0;
}


Red::~Red(){

}


bool Red::operator==(Red& otra){
    bool r;
    r = ((IpaId == otra.IpaId) && (IdaIp == otra.IdaIp) && (Proxim == otra.Proxim) && (Conexiones == otra.Conexiones) && (Interface == otra.Interface) && (UlId == otra.UlId));
    return r;
}


aed2::Conj<Compu> Red::Computadoras(){
    diccLog<aed2::Conj<int> >::iterador it = Interface.crearIt();
    aed2::Conj<Compu> r = aed2::Conj<Compu>();
    while(it.haySiguiente()){
        Compu c(ConvertirIdaIp(it.siguienteClave()),Interfaces(it.siguienteClave()));
        r.Agregar(c);
        it.avanzar();
    }
    return r;
}


bool Red::Conectadas(const Compu& c1, const Compu& c2){
    diccLog<int>::iterador it = Conexiones.obtener(ConvertirIpaId(c1.Ip())).crearIt();
    bool res = false;
    while(it.haySiguiente()){
        if(it.siguienteSignificado() == ConvertirIpaId(c2.Ip())){
            res = true;
        }
        it.avanzar();
    }
    return res;
}


int Red::InterfazUsada(const Compu& c1, const Compu& c2){
    diccLog<int>::iterador it = Conexiones.obtener(ConvertirIpaId(c1.Ip())).crearIt();
    int c22 = ConvertirIpaId(c2.Ip());
    while(it.siguienteSignificado() != c22){
        it.avanzar();
    }
    return it.siguienteClave();
}


void Red::Agregar(const Compu& c){
	UlId++;
    IpaId.definir(c.Ip(),UlId);
    string* Ip =(string*) (&(c.Ip()));
    IdaIp.definir(UlId,*Ip);
    aed2::Conj<int>* con = (aed2::Conj<int>*)(&(c.Interfaces()));
    Interface.definir(UlId, *con);
    diccLog<int> diLog = diccLog<int>();
    Conexiones.definir(UlId,diLog);
    diccLog<pair<string*,int> > diPair = diccLog<pair<string*,int> >();
    Proxim.definir(UlId,diPair);
    //Hasta aca creo todos los diccionerios internos

    //ahora itero pata agregar las interfaces con un 0 que no es un Id valido.
    aed2::Conj<int>::const_Iterador k = c.Interfaces().CrearIt();
    int cero = 0;
    while(k.HaySiguiente()){
        Conexiones.obtener(UlId).definir(k.Siguiente(),cero);
        k.Avanzar();
	}
}


void Red::Conectar(const Compu& c1, const Compu& c2, int i1, int i2){
    int I1 = i1;
    int I2 = i2;
    int IdC1 = ConvertirIpaId(c1.Ip());
    int IdC2 = ConvertirIpaId(c2.Ip());
    Conexiones.obtener(IdC1).definir(I1,IdC2);
    Conexiones.obtener(IdC2).definir(I2,IdC1);
    diccLog<diccLog<int> >::iterador it1 = Conexiones.crearIt();
    while(it1.haySiguiente()){
        diccLog<diccLog<int> >::iterador it2 = Conexiones.crearIt();
        int clave1 = it1.siguienteClave();
        Compu a1(ConvertirIdaIp(clave1),Interfaces(clave1));
        while(it2.haySiguiente()){
            int clave2 = it2.siguienteClave();
            Compu a2(ConvertirIdaIp(clave2),Interfaces(clave2));
            if(HayCamino(a1,a2)){
                int p = Prox(it1.siguienteClave(),it2.siguienteClave());
                pair<string*,int> tupla =pair<string*,int>(&(ConvertirIdaIp(p)),p);
				Proxim.obtener(it1.siguienteClave()).definir(it2.siguienteClave(),tupla);
            }
            it2.avanzar();
        }
        it1.avanzar();
    }
}


bool Red::UsaInterfaz(const Compu& c, int i){
    bool t;
    if(Conexiones.obtener(ConvertirIpaId(c.Ip())).obtener(i) == 0){
        t = false;
    }else{
        t =true;
    }
    return t;
}


aed2::Lista<Compu> Red::CaminoMinimo(const Compu& c1, const Compu& c2){
    int aux = ConvertirIpaId(c1.Ip());
    aed2::Lista<Compu> S;
    int c22 = ConvertirIpaId(c2.Ip());
    while(c22 != aux){
		pair<string*,int> Prox = Proxim.obtener(aux).obtener(c22);
        Compu f(*(Prox.first),Interfaces(Prox.second));
        S.AgregarAtras(f);
        aux = Prox.second;
    }
    return S;
}


bool Red::HayCamino(const Compu& c1, const Compu& c2){
    if(c1 == c2){
        return false;
    }else{
        aed2::Conj<Compu> comparar = aed2::Conj<Compu>();
        comparar.Agregar(c1);
        aed2::Conj<Compu> comparados = aed2::Conj<Compu>();
        bool repito =false;
        while(!(comparar.Pertenece(c2)) && !repito){
            comparados = Union(comparados, comparar);
            aed2::Conj<Compu>::Iterador it = comparar.CrearIt();
            aed2::Conj<Compu> aux = aed2::Conj<Compu>();
            while(it.HaySiguiente()){
                aed2::Conj<Compu> v = Vecinos(it.Siguiente());
                aux = Union(aux,v);
                it.Avanzar();
            }
            aed2::Conj<Compu>::Iterador it2 = aux.CrearIt();
            while(it2.HaySiguiente()){
                if (comparados.Pertenece(it2.Siguiente())){
                    it2.EliminarSiguiente();
                }else{
                    it2.Avanzar();
                }
            }
            if(aux.Cardinal() == 0){
                repito = true;
            }
            comparar = aux;
        }
        return !repito;
    }
}


int Red::ConvertirIpaId(const string &s){
    return *(IpaId.obtener(s));
}

string& Red::ConvertirIdaIp(const int n){
    return IdaIp.obtener(n);
}


aed2::Conj<Compu> Red::Vecinos(const Compu &c){
    int Id = ConvertirIpaId(c.Ip());
    aed2::Conj<Compu> res = aed2::Conj<Compu>();
    aed2::Conj<int> v = Vec(Id);
    aed2::Conj<int>::Iterador it = v.CrearIt();
    while(it.HaySiguiente()){
        Compu c(ConvertirIdaIp(it.Siguiente()),Interfaces(it.Siguiente()));
        res.Agregar(c);
        it.Avanzar();
    }
    return res;
}


pair<string*,int> Red::Proximo(int c1, int c2){
    return Proxim.obtener(c1).obtener(c2);
}


aed2::Conj<int>& Red::Interfaces(const int c){
    return Interface.obtener(c);
}


int Red::UltId(){
    return UlId;
}
