#include "NodoAVL.h"

NodoAVL::NodoAVL(Cita * c){
    cita = c;
    altura = 1;
    izquierda = derecha = nullptr;
}

Cita * NodoAVL::getCita() {return cita;}
void NodoAVL::setCita(Cita * c) {cita = c;}

int NodoAVL::getAltura() {return altura;}
void NodoAVL::setAltura(int h) {altura = h;}

NodoAVL * NodoAVL::getIzquierda() {return izquierda;}
void NodoAVL::setIzquierda(NodoAVL * izq) {izquierda = izq;}

NodoAVL * NodoAVL::getDerecha() {return derecha;}
void NodoAVL::setDerecha(NodoAVL * der) {derecha = der;}
