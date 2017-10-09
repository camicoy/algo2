#ifndef DRIVER_H_
#define DRIVER_H_

#include "Tipos.h"
#include "Modulos-CPP/aed2/TiposBasicos.h"

#include "DcNet.h"

namespace aed2 {

class Driver
{
    public:

        Driver();

        ~Driver();
		
        /// Observadores Red //////////////////////////////////////////////////////////
		
        Nat CantidadComputadoras();
        const Computadora& IesimaComputadora(const Nat i);

        Nat CantidadInterfacesDe(const Computadora& c);
        const Interfaz& IesimaInterfazDe(const Computadora& c, const Nat i);

        const Interfaz IntefazUsada(const Computadora& c1, const Computadora& c2);

        bool conectadas(const Computadora& c1, const Computadora& c2);

        /// Armado Red ////////////////////////////////////////////////////////////////

        void AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci);

        void Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2);


       /// Observadores DCNet //////////////////////////////////////////////////////////////

        Nat CantidadNodosRecorridosPor(const Paquete& p);
        const Computadora IesimoNodoRecorridoPor(const Paquete& p, const Nat i);

        Nat CantidadEnviadosPor(const Computadora& c);

        Nat CantidadEnEsperaEn(const Computadora& c);
        const Paquete IesimoEnEsperaEn(const Computadora& c, const Nat i);

        /// Acciones DCNet ////////////////////////////////////////////////////////////

        void CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad);

        void AvanzarSegundo();

        const Computadora& laQueMasEnvio();

        // Auxiliares para ver los paquetes
        const Computadora& origen(const Paquete& p);
        const Computadora& destino(const Paquete& p);
        Nat prioridad(const Paquete p);

    private:
		Red red;
		DcNet* dcnet;
		int idPaq;
    /*********************************************************************
     * TODO: Va a ser necesario instanciar privadamente un Modulo DCNet *
     * con el cuál interactuar. Además, pueden declarar todas las        *
     * funciones auxiliares que les hagan falta.                         *
     *********************************************************************/

}; // class Driver


} // namespace aed2

#endif // DRIVER_H_
