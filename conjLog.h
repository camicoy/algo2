#ifndef conjLog_H
#define conjLog_H
#include "Modulos-CPP/aed2.h"
#include "diccLog.h"
#include "Compu.h"
#include "Paquete.h"


class conjPaquete
{
    private:
		diccLog<Paquete> dicc;
	
		bool iVacio(){
			return dicc.vacio();
		}
		
		bool iPertenece(Paquete& p){
			return dicc.def(p.id());
		}
		
		bool iPertenecePorId(int id){
			return dicc.def(id);
		}
		
		void iAgregar(Paquete& p){
			dicc.definir(p.id(),p);
		}
		
		void iBorrar(Paquete& p){
			//~ cout << "p en borar " << p << endl;
			//~ cout << "p id en borar " << p << endl;
			dicc.borrar(p.id());
		}
		
	public:
	
		class iterador{
				
			public:
				iterador(){}

				iterador(conjPaquete* con){
					crearLista(con);
					iter = it.CrearIt();
				}

				Paquete& siguiente(){
					return isiguiente();
				}

				bool haySiguiente(){
					return  ihaySiguiente();
				}

				void avanzar(){
					iavanzar();

				}
				
			private:
			
				aed2::Lista<Paquete> it;
				typename aed2::Lista<Paquete>::Iterador iter;
				
				
				void crearLista(conjPaquete* c){
					diccLog<Paquete>::iterador i = c -> dicc.crearIt();
					while(i.haySiguiente()){
						it.AgregarAtras(i.siguienteSignificado());
						i.avanzar();
					}
				}
				
				Paquete& isiguiente(){
					return iter.Siguiente();
				}

				bool ihaySiguiente(){
					return iter.HaySiguiente();
				}

				void iavanzar(){
					iter.Avanzar();

				}

//					friend typename conjPaquete::iterador conjPaquete::crearIt();

		};
	
		bool operator == (conjPaquete& p){
		
		return dicc==p.dicc;
		}
		
		int cardinal(){
				return dicc.claves().Cardinal();
		}
		
		conjPaquete(){
			dicc = diccLog<Paquete>();
		}
		
		bool Vacio(){
			return iVacio();
		}
		
		bool pertenece(Paquete& p){
			return iPertenece(p);
		}
		
		bool pertenecePorId(int id){
			return iPertenecePorId(id);
		}
		
		void agregar(Paquete& p){
			iAgregar(p);
		}
		
		void borrar(Paquete& p){
			iBorrar(p);
		}
	
	
		aed2::Conj<int>  claves(){
			return dicc.claves();
		 }
		
		iterador crearIt(){
			return iterador (this);
		}
	
};

#endif // AVL_H
