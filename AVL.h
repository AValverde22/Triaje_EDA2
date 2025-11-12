#ifndef AVL_H
#define AVL_H

#include "NodoAVL.h"

class AVL {
    private:
        NodoAVL * raiz;
        int contador;

        void inorder(NodoAVL * nodo);
        void preorder(NodoAVL * nodo);
        void actualizarAltura(NodoAVL * nodo);

        NodoAVL * rotarIzquierda(NodoAVL * actualRaiz);
        NodoAVL * rotarDerecha(NodoAVL * actualRaiz);

        NodoAVL * insertar(NodoAVL * nodo, Cita * c);
        NodoAVL * getMin(NodoAVL * nodo);
        NodoAVL * eliminar(NodoAVL * nodo, Cita * c);
        Cita * getMaxCita();

    public:
        AVL();

        int altura(NodoAVL * nodo);
        int factorBalance(NodoAVL * nodo);

        void insertarR(int idPaciente);
        void insertarAutomaticamente(int idPaciente);

        void cancelarAutomaticamente(int cantidad);
        void cancelarCita(int id_cita);
        void reprogramarCita(int id_cita);
        NodoAVL * buscar(int id_cita);

        void inorderR();
        void preorderR();
};

#endif

