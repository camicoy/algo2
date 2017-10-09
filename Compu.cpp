#include "Compu.h"

ostream& operator<<(ostream& os, const Compu& c){
    os << '{';
    os << c.Ip();
    os << ',';
    os << c.Interfaces();
    return os << '}';
}

