#include "Paciente.h"

#include <iostream>
#include <string>
using namespace std;

Paciente::Paciente(int id, string nom, int urg, string fecha_i){
    idPaciente = id;
    nombre = nom;
    urgencia = urg;
    estado = "En espera";
    fecha = fecha_i;
}

//getters y setters
int Paciente::getId() {return idPaciente;}
string Paciente::getNombre() {return nombre;}
int Paciente::getUrgencia() {return urgencia;}
string Paciente::getEstado() {return estado;}
string Paciente::getFecha() {return fecha;}

void Paciente::setEstado(string e) {estado = e;}
void Paciente::setFecha (string f) {fecha = f;}
void Paciente::setId(int i) {idPaciente = i;}


//Mostrar
void Paciente::mostrar() {
    cout << "ID: " << idPaciente
         << " | Nombre: " << nombre
         << " | Urgencia: " << urgencia
         << " | Fecha ingresado: " << fecha
         << " | Estado: " << estado << endl;
}
