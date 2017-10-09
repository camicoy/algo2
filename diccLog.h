#ifndef diccLog_H
#define diccLog_H
#include "Modulos-CPP/aed2.h"

template<class T> class diccLog
{
    private:


			typedef struct nodo{
				nodo() : padree(0),izqu(0),deru(0),significado(0),clave(0), altura(-1){}
				nodo* padree;
				nodo* izqu;
				nodo* deru;
				T* significado;
				int clave;
				int altura;
			}nodo;

			nodo* primerPuntero;

            bool ivacio(){
				bool res = 0;
                if(primerPuntero != 0){
					res = 1;
				}
				return res;
            }

            int alturaAvl(nodo* n){
				if(n != 0){
					return n->altura;
				}else{
					return -1;
				}

            }

            void actualizarAltura(nodo* n){
                if(n != 0){
                    n->altura = std::max(alturaAvl(n->izqu),alturaAvl(n->deru)) +1;
                }
            }

			T* iobtener(const int c){
				return obtener(c, primerPuntero);
			}

            T* obtener(const int c, nodo* n){
                if(n->clave==c){//estoy parado en la clave que busco
                    return n->significado;

                }
                else if(n->clave>c){//busco en la derecha

                    return obtener(c,n->izqu);
                }
                else {//busco en la izquierda
                    return obtener(c,n->deru);
                }

            }

			bool iDef(int c){
				return def(c,primerPuntero);
			}

            bool def(int c, nodo* n) {
                if(n==0){

                    return false;
                }
                else if(n->clave==c){

                    return true;

                }
                else if(n->clave<c){

                    return (def(c,n->deru));

                }
                else {

                    return (def(c,n->izqu));

                }


            }

			 void redefino(const int& c,T& s,nodo* n){
				if(c< n->clave){
					redefino(c,s,n->izqu);
				}
				else if(c > n->clave){
					redefino(c,s,n -> deru);
				}
				
				else if(c== n->clave){
					delete n->significado;
					n->significado = 0;
					n-> significado = new T (s);
				}
			}

            void idefinir(const int& c,T& s){
                if(def(c)){
					redefino(c,s,primerPuntero);
					
				}
					if(primerPuntero == 0){
					nodo* aux = new nodo();
                    aux -> clave = c;
                    aux -> significado = new T (s);
                    aux -> izqu = 0;
                    aux -> deru = 0;
                    aux -> padree = 0;
                    aux -> altura = 0;
                    primerPuntero = aux;
				}else if(primerPuntero->izqu == 0 && primerPuntero->clave > c){
					//agrego el elemento de la izq
					nodo* aux = new nodo();
					aux -> clave = c;
					aux -> significado = new T (s);
					aux -> izqu = 0;
					aux -> deru = 0;
					aux -> padree = primerPuntero;
					primerPuntero->izqu = aux;
					primerPuntero->altura = 1;
					aux -> altura = 0;

				}else if(primerPuntero->deru == 0 && primerPuntero->clave < c){
					nodo* aux = new nodo();
                    aux -> clave = c;
                    aux -> significado = new T (s);
                    aux -> izqu = 0;
                    aux -> deru = 0;
                    aux -> padree = primerPuntero;
                    primerPuntero->deru = aux;
                    primerPuntero->altura = 1;
                    aux -> altura = 0;
				}else if(primerPuntero->clave > c){
					definirconPadre(c,s,primerPuntero->izqu);
					balancear(primerPuntero);
                    actualizarAltura(primerPuntero);
				}else if(primerPuntero->clave < c){
					definirconPadre(c,s,primerPuntero->deru);
                    balancear(primerPuntero);
                    actualizarAltura(primerPuntero);
				}
            }

            void definirconPadre(const int& c,T& s,nodo* n){

                if(n->izqu == 0 && n->clave > c){
					//agrego el elemento de la izq
					nodo* aux = new nodo();
					aux -> clave = c;
					aux -> significado = new T (s);
					aux -> izqu = 0;
					aux -> deru = 0;
					aux -> padree = n;
					n->izqu = aux;
					aux -> altura = 0;
				}else if(n->deru == 0 && n->clave < c){
					nodo* aux = new nodo();
                    aux -> clave = c;
                    aux -> significado = new T (s);
                    aux -> izqu = 0;
                    aux -> deru = 0;
                    aux -> padree = n;
                    n->deru = aux;
                    aux -> altura = 0;
				}else if(n->clave > c){
					definirconPadre(c,s,n->izqu);
				}else if(n->clave < c){
					definirconPadre(c,s,n->deru);
				}

                balancear(n);
                actualizarAltura(n);
            }

			aed2::Conj<int> iclaves(){
				diccLog<T>::iterador it = crearIt();
				aed2::Conj<int> cClaves = aed2::Conj<int>();

				while(it.haySiguiente()){
					cClaves.Agregar(it.siguienteClave());
					it.avanzar();
				}
				return cClaves;
					//~ return auxConjunto(cClaves,primerPuntero);
            }
//~ 
            //~ aed2::Conj<int>& auxConjunto(aed2::Conj<int>& c,const nodo* n){
				//~ c.Agregar(n->clave);
				//~ if(n->izqu!=0){
					//~ auxConjunto(c,n->izqu);
				//~ }
				//~ if(n->deru!=0){
					//~ auxConjunto(c,n->deru);
				//~ }
				//~ return c;
//~ 
			//~ }
            void iborrar(const int c){
				yoBorro(c,primerPuntero);
			}

            void yoBorro(const int c, nodo* n){

                if(c < n->clave){//la clave a borrar esta a la izquierda
                    yoBorro(c,n->izqu);
                }
                else if(c>n->clave){//la clave a borrar esta a la derrecha
                    yoBorro(c,n->deru);
                }
                else{//estoy parado sobre la clave a borrar

                    if((n->izqu ==0) && (n->deru == 0)){//estoy en una hoja
                        if(n->padree==0){

                            nodo* aux=n;

                            delete (aux->significado);
                            aux->significado = 0;
							delete	aux;
							aux = 0;
                            n=0;
                            primerPuntero=0;
                        }
                        else if(!(n->padree->izqu == 0)&&(((n->padree->izqu)->clave)== n->clave)){//estoy del lado izquierdo
                            n->padree->izqu = 0;

                            nodo* aux = n;
                            n = n-> padree;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete (aux);
                            aux = 0;
                        }
                        else if(n->padree->deru !=0 && n->padree->deru == n){
							n->padree->deru = 0;

                            nodo* aux = n;
                            n = n-> padree;


                            delete (aux -> significado);
                            aux->significado = 0;
                            delete (aux);
                            aux = 0;
                        }
                    }
                    else if(n->izqu == 0){//el nodo tiene solo un hijo derecho
                        if(n->padree==0){


                            primerPuntero= n->deru;
                            primerPuntero->padree=0;

                            nodo* aux = n;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
                            aux = 0;

                            n=primerPuntero;

                        }
                        else if(!(n->padree -> izqu == 0)&& ((n->padree-> izqu -> clave)==n->clave)){//estoy del lado izquierdo
                            //el padre del nodo pasa a apuntar al hijo derecho, y viceversa
                            nodo* aux = n;
                            n->padree -> izqu = n->deru;
                            n->deru -> padree = n->padree;

                            n = n->padree;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
							aux = 0;

                        }
                        else if(n->padree->deru != 0){
                            //el padre del nodo pasa a apuntar al hijo izquierdo, y viceversa
                            nodo* aux = n;
                            n->padree -> deru = n->deru;
                            n->deru -> padree = n->padree;

                            n = n->padree;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
                            aux = 0;
                        }
                    }
                    else if(n->deru == 0){
                        if(n->padree==0){

                            nodo* aux = n;

                            primerPuntero= n->izqu;
                            primerPuntero->padree=0;

                            n=primerPuntero;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
							aux = 0;
                        }
                        else if(!(n->padree -> izqu == 0)&&(n->padree -> izqu -> clave == n->clave)){
                            nodo* aux = n;
                            n->padree -> izqu = n->izqu;
                            n->izqu -> padree = n->padree;

                            n = n-> padree;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
                            aux = 0;
                        }
                        else{
                            nodo* aux = n;
                            n->padree -> deru = n->izqu;
                            n->deru -> padree = n->padree;

                            n = n->padree;

                            delete (aux->significado);
                            aux->significado = 0;
                            delete aux;
                            aux = 0;
                        }


                    }
                    else{//estan los dos hijos
						std::pair<int,T*> minimo = eliminarMinimo(n->deru);
                        n->clave = minimo.first;
						delete n->significado;
						n -> significado = 0;
                        n->significado = minimo.second;

                    }
                }

				actualizarAltura(n);
                balancear(n);
                actualizarAltura(n);
            }

            std::pair <int,T*> eliminarMinimo(nodo* n){
                std::pair <int,T*> res;
                while(!((n->izqu) == 0)){
                    n = (n->izqu);
                }

				
                (res).first = n->clave;

				(res).second = new T(*(n->significado));
				borrar(n->clave);


                return res;
            }

            void balancear(nodo* n){

                if(n != 0 && n->altura > 0){

                if(((alturaAvl(n->izqu)) - (alturaAvl(n->deru))) == 2){

                        if((alturaAvl(n->izqu->izqu)) >= (alturaAvl(n->izqu->deru))) {

                            rotacionSimple(n,true);
                        }
                        else {

                            rotacionDoble(n,true);
                        }
                    }
                    else if(((alturaAvl(n->deru))- (alturaAvl(n->izqu))) == 2 ){

                        if((alturaAvl(n->deru->deru)) >= (alturaAvl(n->deru->izqu))){
                            rotacionSimple(n,false);
                        }
                        else{
                            rotacionDoble(n,false);
                        }
                    }
                }

        }


            void rotacionDoble(nodo* n,bool izquierda){
                if(izquierda){
                    rotacionSimple(n->izqu,false);
                    rotacionSimple(n,true);
                }
                else{
                    rotacionSimple(n->deru,true);
                    rotacionSimple(n,false);
                }
            }

            void rotacionSimple(nodo* n,bool izquierda){
                if(izquierda){
                    nodo* p = n;
                    nodo* q = n->izqu;
                    nodo* b = n->izqu -> deru;
                    nodo* z = n->padree;

                    p->izqu= b;
                    p-> padree = q;

                    q->deru = p;
                    q-> padree = z;
					//DUDOSO
					actualizarAltura(p);
					actualizarAltura(q);
					//DUDOSO
					if(z==0){
						primerPuntero=q;
					}
					else{
						if(z->izqu==p){
							z->izqu = q;
						}
						else {
							z->deru = q;
						}
					}
                }
                else{
                    nodo* p = n;
                    nodo* q = n->deru;
                    nodo* b = n->deru -> izqu;
                    nodo* z = n->padree;

                    p->deru= b;
                    p-> padree = q;

                    q->izqu = p;
                    q-> padree = z;
					//DUDOSO
					actualizarAltura(p);
					actualizarAltura(q);
					//DUDOSO
					if(z==0){
						primerPuntero=q;
					}
					else{
						if(z->izqu==p){
							z->izqu = q;
						}
						else {
							z->deru = q;
						}
					}
                }
            }

             bool perteneceNodo(const nodo* a,bool res){
                if (res){
					if( (def(a -> clave) ) && (obtener(a -> clave )== *(a->significado) )){
						if(a->izqu==0&& a->deru==0){

						 }
						else if(a-> izqu==0){
							res = perteneceNodo(a -> deru,res);
						}
						else if(a->deru==0){
							res = perteneceNodo(a -> izqu,res);
						}
						else{
							res = (perteneceNodo(a -> deru,res)&& perteneceNodo(a -> izqu,res));
						}

					}
					else{
						res=false;
					}
				}
				else {
					return false;
				}
				return res;
            }

            bool pertenece(const diccLog* a){
				return perteneceNodo(a -> primerPuntero,true);


			}
    public:

			class iterador{

			private:
				aed2::Lista<std::pair<int,T*> > it;

				typename aed2::Lista< std::pair<int,T*> >::Iterador iter;

				T& isiguienteSignificado(){
					return *(iter.Siguiente().second);
				}

				int isiguienteClave(){
					return iter.Siguiente().first;
				}

				bool ihaySiguiente(){
					return iter.HaySiguiente();
				}

				void iavanzar(){
					iter.Avanzar();

				}
				void crearLista(diccLog* arbol){
					nodo* aux = arbol->primerPuntero;
					crearListaAux(aux);

				}

				void crearListaAux(nodo* n){

					if(n!=0){

						std::pair<int,T*> elemento;
						elemento.first = n->clave;
						elemento.second = n->significado;
						it.AgregarAtras(elemento);

						crearListaAux(n -> izqu);
						crearListaAux(n -> deru);
					}
				}

			//	friend typename diccLog<T>::iterador diccLog<T>::crearIt();
			public:
				iterador(){
					it = aed2::Lista<std::pair<int,T*> >();
					iter = it.CrearIt();
				}

				iterador(diccLog* arbol){
					it = aed2::Lista<std::pair<int,T*> >();
					crearLista(arbol);
					this -> iter = it.CrearIt();
				}

				T& siguienteSignificado(){
					return isiguienteSignificado();
				}

				int siguienteClave(){
					return isiguienteClave();
				}

				bool haySiguiente(){
					return  ihaySiguiente();
				}

				void avanzar(){
					iavanzar();

				}

		};


		bool operator == (diccLog& a){
                diccLog* ar = new diccLog (a);
                if((pertenece(ar))&&(a.pertenece(this))){
                    return true;
                }
                else {
                    return false;
                }
		}


        diccLog(){
            primerPuntero = 0;
        }
		void eliminarTodo(nodo* n){
			if(n != 0){
				if(n->izqu!=0){
				eliminarTodo(n->izqu);
				}

				if(n->deru!=0){
				eliminarTodo(n->deru);
				}

				delete(n->significado);
				n->significado = 0;
				delete(n);
				n = 0;
			}
		}
		
		/*diccLog(diccLog<T>& d){
			diccLog<T>::iterador it =d.crearIt();
			while(it.haySiguiente()){
				definir(it.siguienteClave(),it.siguienteSignificado());
				it.avanzar();
			} 
		}*/

		~diccLog(){
			eliminarTodo(primerPuntero);
		}


        bool vacio(){
            return ivacio();
        }

        bool def(const int c){
            return iDef(c);
        }

        void definir(const int& c, T& s){
            idefinir(c,s);
        }

        T& obtener(const int c){
            return *(iobtener(c));
        }

        void borrar(const int c){
			//~ std::cout << "c en borar de dicc " << c << std::endl;
            iborrar(c);
        }

		 aed2::Conj<int>  claves(){
			return iclaves();
		 }

		iterador crearIt(){
			return iterador (this);
		}

};

#endif // AVL_H
