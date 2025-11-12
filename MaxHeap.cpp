#include "MaxHeap.h"
#include <iostream>
using namespace std;

MaxHeap::MaxHeap() {size = 0;}

void MaxHeap::insertar(int idPaciente, Hash * hashito) {
    if (size + 1 >= TAM) {cout << "El heap esta lleno." << endl; return;}

    size++;
    heap[size] = idPaciente;
    int i = size;

    /* Ordenado primero urgencia, si coincide, por fecha, en el caso de fecha se compara con menor porque se requiere al que llego antes.
    (p1 -> getUrgencia() > p2 -> getUrgencia() ||
    (p1 -> getUrgencia() == p2 -> getUrgencia() && p1 -> getFecha() < p2 -> getFecha()))
     Estará bien? xD
    */

    Paciente * p1 = hashito -> buscar(heap[i]);
    Paciente * p2 = hashito -> buscar(heap[i / 2]);
    // i > 1 && heap[i] -> getUrgencia() >= heap[i / 2] -> getUrgencia()
    while (i > 1 && p1 -> getUrgencia() >= p2 -> getUrgencia()) {
        swap(heap[i], heap[i / 2]);
        i = i / 2;

        p1 = hashito -> buscar(heap[i]);
        p2 = hashito -> buscar(heap[i / 2]);
    }
}

void MaxHeap::imprimir(Hash * hashito) {
    for (int i = 1; i <= size; i++){
        hashito -> buscar(heap[i]) -> mostrar();
        cout << " ------------------------- " << endl;
    }
    cout << endl;
}

int MaxHeap::extraerMax(Hash * hashito) {
    if (size == 0) {cout << "Heap vacio" << endl; return -1;}

    int maximo = heap[1];
    heap[1] = heap[size];
    size--;
    int i = 1;
    while (2 * i <= size) {
        int hijoMayor = 2 * i;
        Paciente * p1 = hashito -> buscar(heap[2 * i + 1]);
        Paciente * p2 = hashito -> buscar(heap[2 * i]);

        //if (2 * i + 1 <= size && heap[2 * i + 1] -> getUrgencia() > heap[2 * i] -> getUrgencia()) hijoMayor = 2 * i + 1;
        if (2 * i + 1 <= size && p1 -> getUrgencia() > p2 -> getUrgencia()) hijoMayor = 2 * i + 1;
        /*
        if(2 * i + 1 < = size && (p1 -> getUrgencia() > p2 -> getUrgencia() ||
           (p1 -> getUrgencia() == p2 -> getUrgencia() && p1 -> getFecha() < p2 -> getFecha()))
        */



        /*
        (p1 -> getUrgencia() < p2 -> getUrgencia() ||
            (p1 -> getUrgencia() == p2 -> getUrgencia() && p1 -> getFecha() > p2 -> getFecha()))
        */
        // if (heap[i] -> getUrgencia() < heap[hijoMayor] -> getUrgencia()) {
        Paciente * p3 = hashito -> buscar(heap[i]);
        Paciente * p4 = hashito -> buscar(heap[hijoMayor]);
        if (p3 -> getUrgencia() < p4 -> getUrgencia()) {
            swap(heap[i], heap[hijoMayor]);
            i = hijoMayor;
        } else break;
    }

    return maximo;
}

/* Es necesario?
void MaxHeap::reestructurarMaxHeap(int i) {
    int hijoIzq = 2 * i;
    int hijoDer = 2 * i + 1;
    int mayor = i;
    if (hijoIzq <= size && heap[hijoIzq] -> getUrgencia() >= heap[mayor] -> getUrgencia()) mayor = hijoIzq;
    if (hijoDer <= size && heap[hijoDer] -> getUrgencia() > heap[mayor] -> getUrgencia()) mayor = hijoDer;

    if (mayor != i) {
        swap(heap[i], heap[mayor]);
        reestructurarMaxHeap(mayor);
    }
}
*/
