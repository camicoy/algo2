#ifndef Compu_H
#define Compu_H

#include <ostream>
#include <string>

using std::ostream;
using std::string;

#include "Modulos-CPP/aed2.h"

class Compu
{
    public:

        Compu(){};
        Compu(Compu& c):a(c.Ip()),i(c.Interfaces()){}
        Compu(const Compu& c):a(c.Ip()),i(c.Interfaces()){}
        Compu(string n,aed2:: Conj<int> c){
            a = n;
            i = c;
        }

        //~ void operator=(Compu& c){
				//~ a= c.Ip();
				//~ i = c.Interfaces();
		//~ }

        ~Compu(){}

        bool operator==(const Compu& c)const{
            return a == c.a && i == c.i;
        }

        bool operator!=(const Compu& c)const{
            return a != c.a;
        }

        const string& Ip() const{
            return a;

        }

        const aed2::Conj<int>& Interfaces() const{
            return i;
        }

    private:

        string a;
        aed2::Conj<int> i;
};

ostream& operator<<(ostream& os, const Compu& c);


#endif // AVL_H
