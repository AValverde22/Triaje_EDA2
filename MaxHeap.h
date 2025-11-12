#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "Paciente.h"
#include "Hash.h"

class MaxHeap {
    private:
        static const int TAM = 15000;
        int heap[TAM];
        int size;

    public:
        MaxHeap();

        void insertar(int idPaciente, Hash * hashito);
        void imprimir(Hash * hashito);

        int extraerMax(Hash * hashito);
        //void reestructurarMaxHeap(int i);
};

#endif
