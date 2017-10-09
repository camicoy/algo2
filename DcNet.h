#ifndef DCNET_H
#define DCNET_H
#include "Modulos-CPP/aed2.h"
#include "diccLog.h"
#include "Red.h"
#include "Compu.h"
#include "Paquete.h"
#include "heap.h"
#include "conjLog.h"
using namespace std;

class DcNet
{
    public:
        DcNet(Red* r);
        bool operator==(DcNet & otro);
        Red* red();
        aed2::Lista<Compu> caminoRecorrido(Paquete& p);
        int cantidadEnviados(Compu& c);
        conjPaquete& enEspera(Compu& c);
        void crearPaquete(Paquete& p);
        void avanzarSegundo();
        bool paqueteEnTransito(Paquete &p);
        Compu& laQueMasEnvio();

        ~DcNet();
        Cola<Paquete>* colaDe(int id);
    private:
    	//struct Aux, estos (los de prefijo "el") son los que se van a llenar en las funciones para usarse los structs
	    	struct sig_DiccPaq_EnEsp
	    	{
				sig_DiccPaq_EnEsp(Paquete& paq):p(paq){}

	    		int inicio;
	    		int fin;
	    		Paquete& p;

	    		bool operator==(sig_DiccPaq_EnEsp k){
					return (inicio==k.inicio && fin==k.fin && p==k.p);
				}
	    	};

            struct cs
        	{
        		int Id;
                string* IP;
        	};

	    	struct sig_EnEsp
	    	{
				sig_EnEsp(Cola<Paquete>& col,diccLog<sig_DiccPaq_EnEsp>& dic,conjPaquete& conj) : cEnvios(0),paq(col),dicPaq(dic),conPaq(conj){}

	    		int cEnvios;
	    		Cola<Paquete> paq;
	    		diccLog<sig_DiccPaq_EnEsp> dicPaq;
	    		conjPaquete conPaq;

				bool operator==(sig_EnEsp p){
					return (paq==p.paq && dicPaq==p.dicPaq && conPaq==p.conPaq && cEnvios==p.cEnvios);
				}
	    	};

	    	struct Elem_EnEspRapido
	    	{
				Elem_EnEspRapido(diccLog<sig_DiccPaq_EnEsp>& dicc, Cola<Paquete>& cola,conjPaquete& conj):dic(&dicc),col(&cola),con(&conj){}

	    		diccLog<sig_DiccPaq_EnEsp>* dic;
	    		Cola<Paquete>* col;
	    		conjPaquete* con;

	    		bool operator==(Elem_EnEspRapido p){
                    return (*dic==*(p.dic) && *col==*(p.col) && *con==*(p.con));
				}
				bool operator!=(Elem_EnEspRapido p){
                    return !(*dic==*(p.dic) && *col==*(p.col) && *con==*(p.con));
				}
	    	};


	    	class Par_LaQueMas
	    	{
				private:

                    int dcEnvios;
                    Compu* dcomp;

	    		public:
                    void setcEnvios(int dato){
                        dcEnvios = dato;
                    }
                    void setComp(Compu& dato){
                        dcomp = &dato;
                    }

                    int cEnvios(){
                        return dcEnvios;
                    }

                    Compu* comp(){
                        return dcomp;
                    }
                    Par_LaQueMas(Compu& computadora):dcomp(&computadora){}

                    Par_LaQueMas():dcomp(0){}

                    void operator=(Par_LaQueMas p){
                        dcomp = p.dcomp;
                        dcEnvios = p.dcEnvios;
                    }


                    bool operator==(Par_LaQueMas p){

                        return (dcEnvios==p.dcEnvios && *(dcomp)==*(p.dcomp));
                    }
	    	};

	    	struct DondeYQuePaquete
	    	{
				DondeYQuePaquete(int c,Paquete* paq):dnd(c),pq(paq){}
	    		int dnd;
	    		Paquete* pq;
	    	};

    	//fin Struct Aux
	    //esta es la estructura de verdad:
    	diccLog<sig_EnEsp> EnEsp;
    	Red* LaRed;
    	aed2::Vector<Elem_EnEspRapido> EnEspRapido;
		Par_LaQueMas LaQueMas;

		int compuActual(int idP){
        	diccLog<sig_EnEsp>::iterador it = EnEsp.crearIt();
        	bool listo=false;
        	int r;
        	while(it.haySiguiente() && !listo){
        		if (((EnEsp.obtener(it.siguienteClave())).conPaq).pertenecePorId(idP)){
        			r=it.siguienteClave();
        			listo=true;
        		}
        		it.avanzar();
        	}
        	return r;
        }

};


#endif // DCNET_H
