#ifndef HASH_H
#define HASH_H

#include "Paciente.h"

class Hash {
    private:
        Paciente ** tabla;
        int tam;
        int cantidad;

        int hashFunction(int id);
        void rehash();

    public:
        Hash(int capacidad = 10000);

        void setTabla(Paciente ** tablita);
        void setTam(int SIZE);
        void setCantidad(int Cant);

        void insertar(Paciente* p);
        bool existeID(int id);
        Paciente * buscar(int id);
        void mostrar();

        void cambiarEstadoAAtendido(int idPaciente);
        void cambiarEstadoAConCitaProgramada(int idPaciente);
};

#endif
