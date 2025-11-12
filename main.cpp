#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <cstdlib> // para random
#include <ctime>

#include "Paciente.h"
#include "Hash.h"
#include "MaxHeap.h"
#include "AVL.h"
#include "NodoAVL.h"

using namespace std;

void regresar(){
    string tecla;
    cout << "Presione cualquier tecla luego enter para regresar.";
    cin >> tecla;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insertarDesdeTXT(Hash * hashito, MaxHeap * heap){
    ifstream archivo("Nombres.txt");

    if(archivo.is_open()){
        string linea, variable;

        while(getline(archivo, linea)){
            vector<string> variables;
            stringstream ss(linea);
            while(getline(ss, variable, ',')) variables.push_back(variable);

            Paciente * p = new Paciente(stoi(variables.at(0)), variables.at(1), stoi(variables.at(2)), variables.at(3));
            hashito -> insertar(p);
            heap -> insertar(stoi(variables.at(0)), hashito);
        }

        archivo.close();
        cout << "Pacientes agregados con exito." << endl;
        regresar();
    } else cout << "Error al abrir el archivo." << endl;
}

void insertarUnoSolo(Hash * hashito, MaxHeap * heap){

    int id, urgencia;
    string nombre, fecha;
    cout << " ----------------------------------------- " << endl;
    cout << "AGREGAR PACIENTE" << endl;
    cout << "Ingrese ID: ";
    cin >> id;

    while(hashito -> existeID(id)){
        cout << "No puede ingresar un ID existente." << endl;
        system("cls");
        cout << " ----------------------------------------- " << endl;
        cout << "AGREGAR PACIENTE" << endl;
        cout << "Ingrese ID: ";
        cin >> id;
    }

    cout << "Ingrese nombre:";
    cin >> nombre;
    cout << "Ingrese nivel de urgencia (1 - 5): ";
    cin >> urgencia;


    while(urgencia < 1 || urgencia > 5){
        cout << "El nivel de urgencia se debe encontrar entre 1 y 5." << endl;
        system("cls");
        cout << "Ingrese nivel de urgencia (1 - 5): ";
        cin >> urgencia;
    }

    cout << "Ingrese fecha (dd/mm/aaaa): ";
    cin >> fecha;

    Paciente * p = new Paciente(id, nombre, urgencia, fecha);
    hashito -> insertar(p);
    heap -> insertar(id, hashito);

    cout << "Paciente agregado con exito." << endl;
    p -> mostrar();
    regresar();
}

bool uno(bool insertado10000, Hash * hashito, MaxHeap * heap){
    cout << insertado10000;
    int opcion;
    if(!insertado10000){
       do{
            system("cls");
            cout << " ----------------------------------------- " << endl;
            cout << "AGREGAR PACIENTE" << endl;
            cout << "   1. Insertar 10000 Pacientes" << endl;
            cout << "   2. Insertar Paciente" << endl;
            cout << "   3. Regresar" << endl;
            cout << ">> Insertar opcion (1 - 3): ";

            cin >> opcion;
            system("cls");

            switch(opcion){
                case 1: insertarDesdeTXT(hashito, heap); return true; // RETURN PARA QUE NO VUELVE A AGREGAR 10000 PACIENTES
                case 2: insertarUnoSolo(hashito, heap); break;  // BREAK PORQUE PUEDE AÚN AGREGAR OTRO PACIENTE
                default: return false;
            }
       } while(opcion != 3);

    }

    do{
        system("cls");
        cout << " ----------------------------------------- " << endl;
        cout << "AGREGAR PACIENTE" << endl;
        cout << "   1. Insertar Paciente" << endl;
        cout << "   2. Regresar" << endl;
        cout << ">> Insertar opcion (1 - 2): ";

        cin >> opcion;
        system("cls");

        switch(opcion){
            case 1: insertarUnoSolo(hashito, heap); break;  // BREAK PORQUE PUEDE AÚN AGREGAR OTRO PACIENTE
            default: return true;
        }
    }while(opcion != 2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dos(Hash * hashito, MaxHeap * heap){
    heap -> imprimir(hashito);
    regresar();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void tres(Hash * hashito, MaxHeap * heap){
    int idPaciente;

    cout << "Ingrese ID del paciente: ";
    cin >> idPaciente;

    Paciente * p = hashito -> buscar(idPaciente);
    if(p != nullptr) p -> mostrar();
    else cout << "No se pudo encontrar al paciente." << endl;

    regresar();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void atenderSiguiente(Hash * hashito, MaxHeap * heap, AVL * avl){
    int idPaciente = heap -> extraerMax(hashito);
    if(idPaciente == -1) {cout << "No hay mas pacientes para antender" << endl; return;}
    cout << "Paciente encontrado." << endl;

    cout << endl << endl;
    hashito -> cambiarEstadoAAtendido(idPaciente);
    avl -> insertarR(idPaciente);
    hashito -> cambiarEstadoAConCitaProgramada(idPaciente);
    cout << endl << endl;
}

void cuatro(Hash * hashito, MaxHeap * heap, AVL * avl) {atenderSiguiente(hashito, heap, avl); regresar();}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void buscarCita(AVL * avl){
    int idCita;
    cout << "Ingrese ID de cita: ";
    cin >> idCita;

    NodoAVL * nodo = avl -> buscar(idCita);
    if(nodo != nullptr) nodo -> getCita() -> mostrarCita();
    else cout << "No se pudo encontrar la cita." << endl;
    regresar();
}

void listarCitas(AVL * avl){
    avl -> inorderR();
    regresar();
}


void cancelarCita(AVL * avl){
    int idCita;
    cout << "Ingrese ID de cita: ";
    cin >> idCita;

    avl -> cancelarCita(idCita);
    regresar();
}

void reprogramarCita(AVL * avl){
    int idCita;
    cout << "Ingrese ID de cita: ";
    cin >> idCita;

    avl -> reprogramarCita(idCita);
    regresar();
}

void cinco(AVL * avl){
    int opcion;
    do {
        system("cls");
        cout << " ----------------------------------------- " << endl;
        cout << "CITAS" << endl;
        cout << "   1. Buscar cita" << endl;
        cout << "   2. Listar citas" << endl;
        cout << "   3. Cancelar cita" << endl;
        cout << "   4. Reprogramar cita" << endl;
        cout << "   5. Regresar" << endl;
        cout << ">> Insertar opcion (1 - 5): ";

        cin >> opcion;
        system("cls");

        switch(opcion){
            case 1: buscarCita(avl); break;
            case 2: listarCitas(avl); break;
            case 3: cancelarCita(avl); break;
            case 4: reprogramarCita(avl); break;
            default: return;
        }
    } while(opcion != 5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void atenderSiguienteAutomaticamente(Hash * hashito, MaxHeap * heap, AVL * avl){
    for(int i = 0; i < 2000; i++){
        int idPaciente = heap -> extraerMax(hashito);
        if(idPaciente == -1) {cout << "No hay mas pacientes para antender" << endl; return;}
        cout << "Paciente encontrado." << endl;

        cout << endl << endl;
        hashito -> cambiarEstadoAAtendido(idPaciente);
        avl -> insertarAutomaticamente(idPaciente);
        hashito -> cambiarEstadoAConCitaProgramada(idPaciente);
        cout << endl << endl;
    }
}

void atencionMasiva(Hash * hashito, MaxHeap * heap, AVL * avl){
    atenderSiguienteAutomaticamente(hashito, heap, avl);
    cout << "Pacientes atendidos." << endl;
    regresar();
}

void insertarCitasDuplicadas(AVL * avl){
    avl -> insertarR(-1);
    avl -> insertarR(-2);
    avl -> insertarR(-3);
    avl -> insertarR(-4);
    regresar();
}
void cancelarCienCitas(AVL * avl) {avl -> cancelarAutomaticamente(100); regresar();}

void consultarCincuentaPacientasAlAzar(Hash * hashito){
    srand(time(NULL));
    int random;
    Paciente * p;
    for(int i = 0; i < 50; i++){
        cout << i + 1 << ": ";
        random = (rand() % 20000) + 1;
        p = hashito -> buscar(random);
        if(p != nullptr) p -> mostrar();
        else cout << "Paciente no encontrado." << endl;
    }
    regresar();
}

void listarTodosLosPacientes(Hash * hashito){hashito -> mostrar(); regresar();}

void seis(Hash * hashito, MaxHeap * heap, AVL * avl){
    int opcion;
    do {
        system("cls");
        cout << " ----------------------------------------- " << endl;
        cout << "ESCENARIOS" << endl;
        cout << "   1. Atencion masiva e insercion de citas de 2000 pacientes" << endl;
        cout << "   2. Insertar citas duplicados" << endl;
        cout << "   3. Cancelar y reprogramar 100 citas" << endl;
        cout << "   4. Consultar 50 pacientes al azar" << endl;
        cout << "   5. Listar todos los pacientes" << endl;
        cout << "   6. Regresar" << endl;
        cout << ">> Insertar opcion (1 - 5): ";

        cin >> opcion;
        system("cls");

        switch(opcion){
            case 1: atencionMasiva(hashito, heap, avl); break;
            case 2: insertarCitasDuplicadas(avl); break;
            case 3: cancelarCienCitas(avl); break;
            case 4: consultarCincuentaPacientasAlAzar(hashito); break;
            case 5: listarTodosLosPacientes(hashito); break;
            default: return;
        }
    } while(opcion != 5);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void pantallaPrincipal(Hash * hashito, MaxHeap * heap, AVL * avl){
    int opcion;
    bool agregado10000 = false;

    do {
        system("cls");
        cout << " ----------------------------------------- " << endl;
        cout << "Bienvenido. ¿Que desea hacer?" << endl;
        cout << "   1. Insertar paciente" << endl;
        cout << "   2. Listar pacientes sin atender" << endl;
        cout << "   3. Buscar paciente" << endl;
        cout << "   4. Atender siguiente" << endl;
        cout << "   5. Citas " << endl;
        cout << "   6. Escenarios" << endl;
        cout << "   7. Salir" << endl;
        cout << ">> Insertar opcion (1 - 7): ";

        cin >> opcion;
        system("cls");

        switch(opcion){
            case 1: agregado10000 = uno(agregado10000, hashito, heap); break;
            case 2: dos(hashito, heap); break;
            case 3: tres(hashito, heap); break;
            case 4: cuatro(hashito, heap, avl); break;
            case 5: cinco(avl); break;
            case 6: seis(hashito, heap, avl); break;
            default: break;
        }

    } while(opcion != 7);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){
    Hash * hashito = new Hash(12000);
    MaxHeap * heap = new MaxHeap();
    AVL * avl = new AVL();

    pantallaPrincipal(hashito, heap, avl);
    heap -> imprimir(hashito);
    return 0;
}

