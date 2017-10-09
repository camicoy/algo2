#include "DcNet.h"

DcNet::DcNet(Red* r){
    EnEsp=diccLog<sig_EnEsp>();
    EnEspRapido=aed2::Vector<Elem_EnEspRapido>();
	LaRed=r;
	for (int i=0; i<LaRed->UltId()+1; i++){
        Cola<Paquete> col=Cola<Paquete>();
        diccLog<sig_DiccPaq_EnEsp> dic=diccLog<sig_DiccPaq_EnEsp>();
        conjPaquete conj=conjPaquete();
        sig_EnEsp el_sig_EnEsp=sig_EnEsp(col,dic,conj);
		EnEsp.definir(i,el_sig_EnEsp);
        Elem_EnEspRapido el_Elem_EnEspRapido(EnEsp.obtener(i).dicPaq,(EnEsp.obtener(i)).paq,(EnEsp.obtener(i)).conPaq);
        EnEspRapido.AgregarAtras(el_Elem_EnEspRapido);
	}
	Compu* comput = new Compu(LaRed->ConvertirIdaIp(1),LaRed->Interfaces(1));

	LaQueMas= Par_LaQueMas(*comput);
    LaQueMas.setcEnvios(0);
}

	DcNet::~DcNet(){
		/*diccLog<sig_EnEsp>::iterador it = EnEsp.crearIt();
		while(it.haySiguiente()){
			//delete &(it.siguienteSignificado().dicPaq);
			//delete &(it.siguienteSignificado().conPaq);
			//delete &(it.siguienteSignificado().paq);
			it.avanzar();
		}*/
		//~ EnEsp = diccLog<sig_EnEsp>();
		delete 	LaQueMas.comp();
	}

bool DcNet::operator==(DcNet & otro){
	return ((*(LaRed)==*(otro.LaRed)) && (EnEsp==otro.EnEsp) && (EnEspRapido==otro.EnEspRapido) && (LaQueMas==otro.LaQueMas));
}

Red* DcNet::red(){
	return LaRed;
}

aed2::Lista<Compu> DcNet::caminoRecorrido(Paquete& p){
	aed2::Lista<Compu> L;
	int idActual=compuActual(p.id());
    cs cInicial;
    cs cFinal;
    cInicial.Id=LaRed->ConvertirIpaId(p.origen());
    cInicial.IP=(string*)(&(p.origen()));
    cFinal.Id=LaRed->ConvertirIpaId(p.destino());
    cFinal.IP=(string*)(&(p.destino()));
	while(!(cInicial.Id==idActual)){
		Compu comput(*(cInicial.IP),LaRed->Interfaces(cInicial.Id));
		L.AgregarAtras(comput);
		cInicial.IP=(string*)((LaRed->Proximo(cInicial.Id,cFinal.Id).first));
		cInicial.Id=LaRed->Proximo(cInicial.Id,cFinal.Id).second;
	}
	Compu comput(*(cInicial.IP),LaRed->Interfaces(cInicial.Id));
	L.AgregarAtras(comput);
	return L;
}

int DcNet::cantidadEnviados(Compu& c){
	return (EnEsp.obtener(LaRed->ConvertirIpaId(c.Ip()))).cEnvios;
}

conjPaquete& DcNet::enEspera(Compu& c){
	//~ cout << LaRed->ConvertirIpaId(c.Ip()) << " y se llama: "<< c.Ip() <<endl;
	return *((EnEspRapido[LaRed->ConvertirIpaId(c.Ip())]).con);
}

void DcNet::crearPaquete(Paquete& p){
	sig_DiccPaq_EnEsp el_sig_diccPaq_EnEsp(p);
	el_sig_diccPaq_EnEsp.inicio=LaRed->ConvertirIpaId(p.origen());
	el_sig_diccPaq_EnEsp.fin=LaRed->ConvertirIpaId(p.destino());
	EnEspRapido[LaRed->ConvertirIpaId(p.origen())].dic->definir(p.id(),el_sig_diccPaq_EnEsp);
	EnEspRapido[LaRed->ConvertirIpaId(p.origen())].col->encolar(p.prioridad(),p);
	EnEspRapido[LaRed->ConvertirIpaId(p.origen())].con->agregar(p);
}

bool DcNet::paqueteEnTransito(Paquete &p){
	bool r=false;
	for (int i = 0; i < (LaRed->UltId())+1; i++){
		if ((EnEsp.obtener(i).conPaq).pertenece(p))
		r=true;
	}
	return r;
}

Compu& DcNet::laQueMasEnvio(){
    return *(LaQueMas.comp());

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

void DcNet::avanzarSegundo(){
	diccLog<sig_EnEsp>::iterador it = EnEsp.crearIt();
	diccLog<DondeYQuePaquete> dicYaEnviados= diccLog<DondeYQuePaquete>();
	while(it.haySiguiente()){
		if(!(EnEsp.obtener(it.siguienteClave()).paq.vacio())){
			
			Paquete* paqMaxPrior = &(EnEsp.obtener(it.siguienteClave()).paq.obtenerMaxPrior());
			int aDonde=LaRed->Proximo(it.siguienteClave(),LaRed->ConvertirIpaId(paqMaxPrior->destino())).second;
            DondeYQuePaquete dndYenQuePq(aDonde,paqMaxPrior);
            
            dicYaEnviados.definir(paqMaxPrior->id(),dndYenQuePq);
			EnEsp.obtener(it.siguienteClave()).cEnvios++;
			if ((EnEsp.obtener(it.siguienteClave())).cEnvios >LaQueMas.cEnvios()){
				LaQueMas.setcEnvios((EnEsp.obtener(it.siguienteClave())).cEnvios);
				delete(LaQueMas.comp());
				Compu* comput = new Compu(LaRed->ConvertirIdaIp(it.siguienteClave()),LaRed->Interfaces(it.siguienteClave()));
                LaQueMas.setComp(*comput);
			}
			(EnEsp.obtener(it.siguienteClave())).dicPaq.borrar(paqMaxPrior->id());
			(EnEsp.obtener(it.siguienteClave())).conPaq.borrar(*paqMaxPrior);
            (EnEsp.obtener(it.siguienteClave())).paq.eliminar();
			//~ cout << "paq " << *paqMaxPrior << endl;
			//~ cout << "conjunto " << (EnEsp.obtener(it.siguienteClave())).conPaq << endl << endl;
		}
		it.avanzar();
	}
    diccLog<DondeYQuePaquete>::iterador ite=dicYaEnviados.crearIt();

    while(ite.haySiguiente()){
        int donde=(dicYaEnviados.obtener(ite.siguienteClave())).dnd;
        Paquete& paque = *((dicYaEnviados.obtener(ite.siguienteClave())).pq);
        //borro si ya llego
        //~ cout<< "muestro paque "<<paque<<endl;
        if(donde!=LaRed->ConvertirIpaId(paque.destino())){
			//~ cout<< "Entre al if!!!!"<<endl;
            sig_DiccPaq_EnEsp sig(paque);
            sig.inicio=LaRed->ConvertirIpaId(paque.origen());
            sig.fin=LaRed->ConvertirIpaId(paque.destino());
            (EnEsp.obtener(donde)).paq.encolar(paque.prioridad(),paque);
            (EnEsp.obtener(donde)).dicPaq.definir(paque.id(),sig);
            (EnEsp.obtener(donde)).conPaq.agregar(paque);
            //~ cout<< "muestro paque, denuevo "<<paque<<endl;
        }else{
			delete(&paque);
		}
        ite.avanzar();
    }
}

Cola<Paquete>* DcNet::colaDe(int id){
    return EnEspRapido[id].col;
}
