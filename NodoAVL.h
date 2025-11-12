#ifndef NODOAVL_H
#define NODOAVL_H

#include "Cita.h"

class NodoAVL {
    private:
        Cita * cita;
        int altura;
        NodoAVL * izquierda;
        NodoAVL * derecha;

    public:
        NodoAVL(Cita * c);

        Cita * getCita();
        void setCita(Cita * c);

        int getAltura();
        void setAltura(int h);

        NodoAVL * getIzquierda();
        void setIzquierda(NodoAVL * izq);

        NodoAVL * getDerecha();
        void setDerecha(NodoAVL * der);
};

#endif
