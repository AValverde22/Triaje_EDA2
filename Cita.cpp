#include "Cita.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

Cita::Cita() {
    idCita = idPaciente = 0;
    fecha = hora = "";
}

Cita::Cita(int id_cita, int id_paciente, string fecha_i, string hora_i) {
    idCita = id_cita;
    idPaciente = id_paciente;
    fecha = fecha_i;
    hora = hora_i;
}

int Cita::getID_Cita() {return idCita;}
void Cita::setID_Cita(int id_cita) {idCita = id_cita;}

int Cita::getID_Paciente() {return idPaciente;}
void Cita::setID_Paciente(int id_paciente) {idPaciente = id_paciente;}

string Cita::getFechaString() {return fecha;}
void Cita::setFechaString(string fecha_i) {fecha = fecha_i;}

string Cita::getHoraString() {return hora;}
void Cita::setHoraString(string hora_i) {hora = hora_i;}

int Cita::getFecha() {
    vector<string> variables;
    stringstream ss(fecha);
    string variable;

    while(getline(ss, variable, '/')) variables.push_back(variable);
    int dia = stoi(variables.at(0));
    int mes = stoi(variables.at(1)) * 30;
    int year = stoi(variables.at(2)) * 365;
    return dia + mes + year;
}

void Cita::setFechaAPartirDeInt(int fecha_i){
    int year = fecha_i / 365;
    int mes = (fecha_i - year * 365) / 30;
    int dia = (fecha_i - year * 365 - mes * 30);

    fecha = to_string(dia) + "/" + to_string(mes) + "/" + to_string(year);
}

int Cita::getHora() {
    vector<string> variables;
    stringstream ss(hora);
    string variable;

    while(getline(ss, variable, ':')) variables.push_back(variable);
    int horas = stoi(variables.at(0)) * 60;
    int minutos = stoi(variables.at(1));
    return horas + minutos;
}

void Cita::setHoraAPartirDeInt(int hora_i){
    int horas = hora_i / 60;
    int minutos = hora_i - horas * 60;

    hora = to_string(horas) + ":" + to_string(minutos);
}


void Cita::mostrarCita(){
    cout << "Cita ID: " << idCita
    << " | Paciente ID: " << idPaciente
    << " | Fecha: " << fecha
    << " | Hora: " << hora << endl;
}
