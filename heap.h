#ifndef HEAP_H
#define HEAP_H
#include<assert.h>


template<class T> class Cola{

	private:

	typedef struct nodo{
		nodo() : elemento(0), prioridad(0),padre(0),izq(0),der(0){}
		T* elemento;
		int prioridad;
		nodo* padre;
		nodo* izq;
		nodo* der;
	}nodo;
	nodo* punteroArbol;
	nodo* ultimo;
	
	
	bool iVacio(){
		bool res = 0;
		if(punteroArbol == 0 && ultimo == 0){
			res = 1;
		}
		return res;
	}
	
		nodo* borroPrimerElemento(){
		eliminar();
		return punteroArbol;
	}
	
	aed2::Lista<T>& devuelvoLista(aed2::Lista<T>& list,aed2::Lista<int>& listPrior,nodo* n){
			while(n != 0){
				list.AgregarAdelante(*n->elemento);
				listPrior.AgregarAdelante(n->prioridad);
				n = borroPrimerElemento();
			}
			//Ya la lista esta completa!! Ahora volvemos a llenar el arbol!
			int cantItems = list.Longitud();
			int i = 0;
			while(i<cantItems){
				encolar(listPrior[i],list[i]);
				i++;
			}
			//Ahora el arbol vuelve a tener todos los elementos y podemos devolver la lista de elementos en el orden en el que se desencolaria
			return list;
	}
	
	aed2::Lista<T>& pasarALista(){
		aed2::Lista<T> lista1;
		aed2::Lista<int> lista2;
		return devuelvoLista(lista1,lista2,punteroArbol);
	}
	
	
	bool fijarseSiEsIgual(Cola<T>& col){
		aed2::Lista<T> lista1;
		aed2::Lista<T> lista2;
		lista1 = col.colaALista();
		lista2 = pasarALista();
		if(lista1.Longitud() == lista2.Longitud()){
			return lista1 == lista2;
		}else{
			return false;
		} 
	}
	
	void insertarUltimoElemento(T& elem, int p){
		nodo* n =  new nodo();
		n->elemento = &(elem);
		n->prioridad = p;
		if(ultimo == 0){
			//Es el primer elemento
			ultimo = n;
			punteroArbol = n;
			n->padre = 0;
			n->izq = 0;
			n->der = 0;
		}else{
			nodo* ult = ultimo;
			nodo* raiz = punteroArbol;
			if(ult->padre == 0){ //Osea el ultimo es raiz..
				if(ult->izq == 0){
					ult->izq = n;
					n->padre = ultimo;
					ultimo = n;
				}else{
					ult->der = n;
					n->padre = ultimo;
					ultimo = n;
				}

			}else{
				while((ult->padre) != raiz && ult == ((ult->padre)->der)){
					ult = ult->padre;
				}
				if(((ult->padre)->izq) == ult && (ult->padre) == raiz){//modifique esta deberia entrar y no entra..
					if(((ult->padre)->der) != 0){
						ult = (ult->padre)->der;
						while((ult->izq	)!= 0){
							ult = ult->izq;
						}
						//nodo* nuevoUltimo = new nodo();
						//n->elemento = &elem;
						//n->prioridad = p;
						n->padre = ult; // Aca era ult->padre, por eso no se liberaba toda la memoria..
						n->izq = 0;
						n->der = 0;
						(ult->izq) = n;
						ultimo = n;
					}else{
						//nodo* nuevoUltimo = new nodo();
						//n->elemento = &elem;
						//n->prioridad = p;
						n->padre = ult->padre;
						(ult->padre)->der = n;
						ultimo = n;
					}
				}else{
					if(((ult->padre)->izq) == ult && (ult->padre) != raiz){
						if(((ult->padre)->der) != 0){
							ult = (ult->padre)->der;
							while((ult->izq) != 0){
								ult = ult->izq;
							}
							//nodo* nuevoUltimo = new nodo();
							//n->elemento = &elem;
							//n->prioridad = p;
							n->padre = ult->padre;
							ult->izq = n;
							ultimo = n;
						}else{
							//nodo* n = new nodo();
							//n->elemento = &elem;
							//n->prioridad = p;
							n->padre = ult->padre;
							(ult->padre)->der = n;
							ultimo = n;
						}
					}else{
						if(((ult->padre)->izq) == ult && (ult->padre) != raiz){
							if(((ult->padre)->der) != 0){
								ult = ((ult->padre)->der);
								while((ult->izq) != 0){
									ult = ult->izq;
								}
								//nodo* nuevoUltimo = new nodo();
								//n->elemento = &elem;
								//n->prioridad = p;
								n->padre = ult->padre;
								ult->izq = n;
								ultimo = n;
							}else{
								//nodo* nuevoUltimo = new nodo();
								//n->elemento = &elem;
								//n->prioridad = p;
								n->padre = ult->padre;
								(ult->padre)->der = n;
								ultimo = n;
							}
						}
					}
					if(((ult->padre)->der) == ult && (ult->padre) == raiz){
						//No estoy seguro de este if todavia..
						ult = ult->padre;
						while(ult->izq != 0){
							ult = ult->izq;
						}
						//nodo* nuevoUltimo = new nodo();
						//nuevoUltimo->elemento = &elem;
						//nuevoUltimo->prioridad = p;
						n->padre = ult;  //estaba ult->padre
						ult->izq = n;
						ultimo = n;
					}
				}
			}
		}

	}

	void borrarUltimoElemento(){
		//Sabemos que ultimo, es el nodo que hay que borrar, pero tambien hay que actualizar el valor de ultimo..
		nodo* ult = ultimo;
		//nodo* raiz = punteroArbol;
		if(ult != 0 && ult->padre != 0){
			if( (ult->padre)->der != 0 && (ult->padre)->der == ult){
				ultimo = ((ult->padre)->izq);
				(ult->padre)->der = 0;
				//delete(ult->elemento);
				delete(ult);
				ult = 0;
			}else{
				while(ult->padre != 0 && (ult->padre)->izq == ult){
					ult = ult->padre;
				}
				if(ult->padre != 0){
					ult = (ult->padre)->izq;
				}
				while(ult->der != 0){
					ult = ult->der;
				}
				if(ultimo->padre != 0){
					if(ultimo == (ultimo->padre)->izq){
						(ultimo->padre)->izq = 0;
					}else{
						(ultimo->padre)->der = 0;
					}
				}
				//delete(ultimo->elemento);
				delete(ultimo);
				ultimo = ult;
			}
		}else{
			if(ult != 0){
				ultimo = 0;
				punteroArbol = 0;
			}
		}
	}

	void cambiarPrimerElementoConUltimo(){
		if(ultimo != 0 && ultimo != punteroArbol){
			nodo* n = ultimo;
			T* ultElem = n->elemento;
			int ultPrio = n->prioridad;
			nodo* m = punteroArbol;
			T* prmElem = m->elemento;
			int prmPrio = m->prioridad;
			n->elemento = prmElem;
			n->prioridad = prmPrio;
			m->elemento = ultElem;
			m->prioridad = ultPrio;

			//Sabemos que siempre es una hoja, porque es el ULTIMO elemento..
			borrarUltimoElemento();

		}else{
			if(ultimo != 0){
				//delete(ultimo->elemento);
				delete(ultimo);
				ultimo = 0;
				punteroArbol = 0;
			}
		}
	}

	void ordenarHeapDeAbajo(){
		if(ultimo != 0 && ultimo != punteroArbol){
			nodo* n = ultimo;
			T* hijoElem;
			int hijoPrio;
			nodo* m = 0;
			T* padreElem;
			int padrePrio;
			while((n->padre)!= 0 && (n->prioridad) < ((n->padre)->prioridad)){
				hijoElem = n->elemento;
				hijoPrio = n->prioridad;
				m = n->padre;
				padreElem = m->elemento;
				padrePrio = m->prioridad;
				n->elemento = padreElem;
				n->prioridad = padrePrio;
				m->elemento = hijoElem;
				m->prioridad = hijoPrio;
				n = m; //Aclaro, por las dudas, n = padre, para que ahora vuelva al while y este un escalon mas arriba en el heap
			}
		}
	}
	T& _mayorElemento(){
		//nodo* n = punteroArbol;
		return *(punteroArbol->elemento);
	}

	void ordenarHeapDeArriba(){
		if(ultimo != 0 && ultimo != punteroArbol){
			nodo* n = punteroArbol;
			T* hijoElem;
			int hijoPrio;
			T* padreElem;
			int padrePrio;
			bool sigoBajando = 1;
			while( ((n->izq) != 0 || (n->der) != 0) &&  sigoBajando == 1){
				if((n->izq) != 0 && (n->der) != 0 && ( ((n->prioridad) > ((n->izq)->prioridad)) || ((n->prioridad) > ((n->der)->prioridad)) )){
					if(((n->izq)->prioridad) < ((n->der)->prioridad)){
						//Entonces sube, n->izq, y baja el padre..
						hijoElem = (n->izq)->elemento;
						hijoPrio = (n->izq)->prioridad;
						padreElem = n->elemento;
						padrePrio = n->prioridad;
						n->elemento = hijoElem;
						n->prioridad = hijoPrio;
						(n->izq)->elemento = padreElem;
						(n->izq)->prioridad = padrePrio;
						n = n->izq;
					}else{
						hijoElem = (n->der)->elemento;
						hijoPrio = (n->der)->prioridad;
						padreElem = n->elemento;
						padrePrio = n->prioridad;
						n->elemento = hijoElem;
						n->prioridad = hijoPrio;
						(n->der)->elemento = padreElem;
						(n->der)->prioridad = padrePrio;
						n = n->der;

					}
				}else{
					if(n->izq != 0  && n->der != 0){
						sigoBajando = 0;
					}else{
						if(n->izq != 0 && ((n->izq)->prioridad) < n->prioridad ){
							//Entonces, sube el izq..
							nodo* m = n->izq;
							hijoElem = m->elemento;
							hijoPrio = m->prioridad;
							padreElem = n->elemento;
							padrePrio = n->prioridad;
							n->elemento = hijoElem;
							n->prioridad = hijoPrio;
							m->elemento = padreElem;
							m->prioridad = padrePrio;
							n = n->izq;
						}else if (n->der != 0 && ((n->der)->prioridad) < n->prioridad ) {
							//Entonces sube el der..
							hijoElem = (n->der)->elemento;
							hijoPrio = (n->der)->prioridad;
							padreElem = n->elemento;
							padrePrio = n->prioridad;
							n->elemento = hijoElem;
							n->prioridad = hijoPrio;
							(n->der)->elemento = padreElem;
							(n->der)->prioridad = padrePrio;
							n = n->der;
						}else{
							//No sube ninguno, entonces termina el while
							sigoBajando = 0;
						}

					}


				}
			}

		}
	}

	void eliminarTodo(nodo* n){
		if(n != 0){
			eliminarTodo(n->izq);
			eliminarTodo(n->der);
			//delete(n->elemento);
			delete(n);
			n = 0;
		}
	}

	public:
	
	aed2::Lista<T> colaALista(){
		return pasarALista();
	}
	
	bool operator==(Cola<T>& col){
		return fijarseSiEsIgual(col);
	}
	
	
	 ~Cola()
    {
        eliminarTodo(punteroArbol);
    }

	Cola()
    {
		punteroArbol = 0;
		ultimo = 0;
    }

	bool vacio(){
		return iVacio();
	}

	T& obtenerMaxPrior(){
		return (_mayorElemento());
	}

	void encolar(int p,T& elem){
		insertarUltimoElemento(elem,p);
		ordenarHeapDeAbajo();
	}

	void eliminar(){
		cambiarPrimerElementoConUltimo();
		ordenarHeapDeArriba();
	}

};
#endif
