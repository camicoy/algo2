#include "Paquete.h"

ostream& operator<<(ostream& os, Paquete& p){
    os << '{';
    os << p.id();
    os << ',';
    os << p.prioridad();
    os << ',';
    os << p.origenCompleto();
    os << ',';
    os << p.destinoCompleto();
    return os << '}';
}
