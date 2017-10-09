#ifndef Paquete_H
#define Paquete_H

#include <ostream>
#include <string>

using std::ostream;
using std::string;

#include "Modulos-CPP/aed2.h"
#include "Compu.h"




class Paquete
{
    public:

        Paquete(){}
        
        Paquete(Paquete& p):Id(p.id()),priorida(p.prioridad()),orige(p.origenCompleto()),destin(p.destinoCompleto()){}
        
        Paquete(int id, int Prio, Compu& o, Compu& d):Id(id),priorida(Prio),orige(o),destin(d){}

        ~Paquete(){}

		  Paquete(const Paquete& p){
				Id= p.Id;
				priorida = p.priorida;
				orige = p.orige;
				destin = p.destin;
		}

        bool operator==(const Paquete& p)const{
            return (Id == p.Id) && (priorida == p.priorida) && (orige == p.orige) && (destin == p.destin);
        }

        bool operator!=(const Paquete& p)const{
            return Id != p.Id;
        }

        int id(){
            return Id;
        }

        int prioridad(){
            return priorida;
        }

        const Compu& origenCompleto(){
            return orige;
        }

        const Compu& destinoCompleto(){
            return destin;
        }

		const string& origen(){
            return orige.Ip();
        }

        const string& destino(){
            return destin.Ip();
        }
    private:

        int Id;
        int priorida;
        Compu orige;
        Compu destin;
};

ostream& operator<<(ostream& os, Paquete& p);

#endif // AVL_H
