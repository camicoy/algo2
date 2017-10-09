#ifndef RED_H
#define RED_H
#include "Modulos-CPP/aed2.h"
#include "dicc_trie.h"
#include "diccLog.h"
#include "Compu.h"



class Red
{
    public:
        Red();

        ~Red();

        //Despues lo pruebo
        bool operator==(Red &otra);//le saque los const por incopatibilidades.

        //Probado
        aed2::Conj<Compu> Computadoras();

        //Probado
        bool Conectadas(const Compu &c1, const Compu &c2);

        //Probado
        int InterfazUsada(const Compu &c1, const Compu &c2);

        //Probado
        void Agregar(const Compu &c);

        //A veces falla, con las compus c6 y c7
        void Conectar(const Compu &c1, const Compu &c2, int i1, int i2);

        //Probado
        bool UsaInterfaz(const Compu &c, int i);

        //Hay algo que esta fallando, todavía no logro encontrarlo
        aed2::Lista<Compu> CaminoMinimo(const Compu &c1, const Compu &c2);

        //Probado
        bool HayCamino(const Compu &c1, const Compu &c2);

        //Probado
        int ConvertirIpaId(const string &s);

        //Probado
        string& ConvertirIdaIp(const int n);

        //Probado
        aed2::Conj<Compu> Vecinos(const Compu &c);

        //
        pair<string*,int> Proximo(int c1, int c2);

        //Probado
        aed2::Conj<int>& Interfaces(const int c);

        //Probado
        int UltId();

    private:

        DiccString<int> IpaId;

        diccLog<string> IdaIp;

        diccLog<diccLog<pair<string*,int> > > Proxim;

        diccLog<diccLog<int> > Conexiones;

        diccLog<aed2::Conj<int> > Interface;

        int UlId;



        aed2::Conj<int> Vec(int c){
            diccLog<int>::iterador it = Conexiones.obtener(c).crearIt();
            aed2::Conj<int> r = aed2::Conj<int>();
            while(it.haySiguiente()){
                if(it.siguienteSignificado() != 0){
                    r.Agregar(it.siguienteSignificado());
                }
                it.avanzar();
            }
            return r;
        }


        int Prox(int c1, int c2){
            aed2::Conj<int> v = Vec(c1);
            aed2::Conj<int>::Iterador k = v.CrearIt();
            int aux = c1;
            while(k.HaySiguiente()){
                if(Distancia(aux,c2) > Distancia(k.Siguiente(),c2)){
                    aux = k.Siguiente();
                }
                k.Avanzar();
            }
            if(aux == c1){
                return c2;
            }
            return aux;
        }


        int Distancia(int c1, int c2){
            aed2::Conj<int> comparar = aed2::Conj<int>();
            comparar.Agregar(c1);
            int sum = 0;
            aed2::Conj<int> aux = aed2::Conj<int>();
            while(!comparar.Pertenece(c2)){
                aed2::Conj<int>::Iterador it = comparar.CrearIt();
                aux = aed2::Conj<int>();
                while(it.HaySiguiente()){
                    aux = Union(aux,Vec(it.Siguiente()));
                    it.Avanzar();
                }
                sum++;
                comparar = aux;
            }
            return sum;
        }


        aed2::Conj<Compu> Union(aed2::Conj<Compu> &a, aed2::Conj<Compu> b){
           aed2::Conj<Compu> res = aed2::Conj<Compu>();
           res = a;
           aed2::Conj<Compu>::Iterador it = b.CrearIt();
            while(it.HaySiguiente()){
                res.Agregar(it.Siguiente());
                it.Avanzar();
            }
            return res;
        }


        aed2::Conj<int> Union(aed2::Conj<int> &a, aed2::Conj<int> b){
           aed2::Conj<int> res = aed2::Conj<int>();
           res = a;
           aed2::Conj<int>::Iterador it = b.CrearIt();
           while(it.HaySiguiente()){
                res.Agregar(it.Siguiente());
                it.Avanzar();
           }
           return res;
        }
};

#endif // RED_H
