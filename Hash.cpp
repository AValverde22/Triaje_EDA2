#include "Hash.h"

#include <iostream>
using namespace std;

int Hash::hashFunction(int id) {return id % tam;}

void Hash::rehash() {
    int nuevoTam = tam * 2;
    Paciente ** nuevaTabla = new Paciente * [nuevoTam];
    for(int i = 0; i < nuevoTam; i++) nuevaTabla[i] = nullptr;

    for (int i = 0; i < tam; i++){
        if (tabla[i] != nullptr){
            int index = hashFunction(tabla[i] -> getId());
            while(nuevaTabla[index] != nullptr) index = (index + 1) % nuevoTam;
            nuevaTabla[index] = tabla[i];
        }
    }

    tam = nuevoTam;
    tabla = nuevaTabla;
}

Hash::Hash(int capacidad){
    tam = capacidad;
    cantidad = 0;
    tabla = new Paciente * [tam];
    for (int i = 0; i < tam; i++) tabla[i] = nullptr;
}

void Hash::setTabla(Paciente ** tablita) {tabla = tablita;}
void Hash::setTam(int SIZE) {tam = SIZE;}
void Hash::setCantidad(int Cant) {cantidad = Cant;}

void Hash::insertar(Paciente* p){
    if ((float) cantidad / tam > 0.7) rehash();

    if(p -> getId() == -1) p -> setId(++cantidad);
    int index = hashFunction(p -> getId());
    while (tabla[index] != nullptr) index = (index + 1) % tam;

    tabla[index] = p;
}

bool Hash::existeID(int id) {return buscar(id) != nullptr;}

Paciente * Hash::buscar(int id) {
    int index = hashFunction(id);
    int inicio = index;

    while(tabla[index] != nullptr){
        if (tabla[index] -> getId() == id) return tabla[index];
        index = (index + 1) % tam;
        if (index == inicio) break;
    }

    return nullptr;
}

void Hash::cambiarEstadoAAtendido(int idPaciente){
    int index = hashFunction(idPaciente);
    int inicio = index;

    while(tabla[index] != nullptr){
        if (tabla[index] -> getId() == idPaciente) {
                tabla[index] -> setEstado("Atendido.");
                tabla[index] -> mostrar();

                return;
        }
        index = (index + 1) % tam;
        if (index == inicio) break;
    }

    cout << "Paciente no encontrado." << endl;
    return;
}


void Hash::cambiarEstadoAConCitaProgramada(int idPaciente){
    int index = hashFunction(idPaciente);
    int inicio = index;

    while(tabla[index] != nullptr){
        if (tabla[index] -> getId() == idPaciente) {
                tabla[index] -> setEstado("Con cita programada.");
                tabla[index] -> mostrar();

                return;
        }
        index = (index + 1) % tam;
        if (index == inicio) break;
    }

    cout << "Paciente no encontrado." << endl;
    return;
}


void Hash::mostrar() {for (int i = 0; i < tam; i++) {if (tabla[i] != nullptr) tabla[i] -> mostrar();}}
