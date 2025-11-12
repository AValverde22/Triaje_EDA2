#include "AVL.h"

#include <iostream>
#include <stack>
using namespace std;

void AVL::inorder(NodoAVL * nodo) {
    if(nodo != nullptr){
        inorder(nodo -> getIzquierda());
        nodo -> getCita() -> mostrarCita();
        inorder(nodo -> getDerecha());
    }
}

void AVL::preorder(NodoAVL * nodo) {
    if(nodo != nullptr) {
        nodo -> getCita() -> mostrarCita();
        preorder(nodo -> getIzquierda());
        preorder(nodo -> getDerecha());
    }
}

void AVL::actualizarAltura(NodoAVL * nodo) {
    int alt = 1 + max(altura(nodo -> getIzquierda()), altura(nodo -> getDerecha()));
    nodo -> setAltura(alt);
}

NodoAVL * AVL::rotarIzquierda(NodoAVL * actualRaiz) {
    NodoAVL * nuevaRaiz = actualRaiz -> getDerecha();
    NodoAVL * subArbol = nuevaRaiz -> getIzquierda();

    nuevaRaiz -> setIzquierda(actualRaiz);
    actualRaiz -> setDerecha(subArbol);

    actualizarAltura(actualRaiz);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

NodoAVL * AVL::rotarDerecha(NodoAVL * actualRaiz) {
    NodoAVL * nuevaRaiz = actualRaiz -> getIzquierda();
    NodoAVL * subArbol = nuevaRaiz -> getDerecha();

    nuevaRaiz -> setDerecha(actualRaiz);
    actualRaiz -> setIzquierda(subArbol);

    actualizarAltura(actualRaiz);
    actualizarAltura(nuevaRaiz);

    return nuevaRaiz;
}

NodoAVL * AVL::insertar(NodoAVL * nodo, Cita * c) {
    if(nodo == nullptr) {
        // Si no hay nodo, creamos uno nuevo y lo devolvemos como raíz del subárbol
        return new NodoAVL(c);
    }
    else if (c -> getFecha() == nodo -> getCita() -> getFecha() && c -> getHora() == nodo -> getCita() -> getHora()) {
        cout << "No se puede ingresar la cita, fecha y hora ya ocupados." << endl;
        return nodo;
    } else if (c -> getFecha() < nodo -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getCita() -> getFecha() && c -> getHora() < nodo -> getCita() -> getHora())) {
         nodo -> setIzquierda(insertar(nodo -> getIzquierda(), c));
    } else {
        nodo -> setDerecha(insertar(nodo -> getDerecha(), c));
    }

    actualizarAltura(nodo);
    int facBalance = factorBalance(nodo);

    // der - der
    if (facBalance < -1 && nodo -> getDerecha() != nullptr &&
        (c -> getFecha() > nodo -> getDerecha() -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getDerecha() -> getCita() -> getFecha() && c -> getHora() > nodo -> getDerecha() -> getCita() -> getHora()))) {
        nodo = rotarIzquierda(nodo);
    }

    // izq - izq
    if (facBalance > 1 && nodo->getIzquierda() != nullptr &&
        (c -> getFecha() < nodo -> getIzquierda() -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getIzquierda() -> getCita() -> getFecha() && c -> getHora() < nodo -> getIzquierda() -> getCita() -> getHora()))){
        nodo = rotarDerecha(nodo);
    }

    // izq - der
    if (facBalance > 1 && nodo->getIzquierda() != nullptr &&
        (c -> getFecha() > nodo -> getIzquierda() -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getIzquierda() -> getCita() -> getFecha() && c -> getHora() > nodo -> getIzquierda() -> getCita() -> getHora()))) {
        NodoAVL * tmp = rotarIzquierda(nodo -> getIzquierda());
        nodo -> setIzquierda(tmp);
        nodo = rotarDerecha(nodo);
    }

    // der - izq
    if (facBalance < -1 && nodo->getDerecha() != nullptr &&
        (c -> getFecha() < nodo -> getDerecha() -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getDerecha() -> getCita() -> getFecha() && c -> getHora() < nodo -> getDerecha() -> getCita() -> getHora()))) {
        NodoAVL * tmp = rotarDerecha(nodo -> getDerecha());
        nodo -> setDerecha(tmp);
        nodo = rotarIzquierda(nodo);
    }
    return nodo;
}

NodoAVL * AVL::getMin(NodoAVL * nodo) {
    NodoAVL * actual = nodo;
    while (actual -> getIzquierda() != nullptr) actual = actual -> getIzquierda();
    return actual;
}

NodoAVL * AVL::eliminar(NodoAVL * nodo, Cita * c) {
    if (nodo == nullptr) return nodo;

    if (c -> getFecha() < nodo -> getCita() -> getFecha() ||
        (c -> getFecha() == nodo -> getCita() -> getFecha() && c -> getHora() < nodo -> getCita() -> getHora())) {
        nodo -> setIzquierda(eliminar(nodo -> getIzquierda(), c));
    } else if (c -> getFecha() > nodo -> getCita() -> getFecha() ||
            (c -> getFecha() == nodo -> getCita() -> getFecha() && c -> getHora() > nodo -> getCita() -> getHora())) {
            nodo -> setDerecha(eliminar(nodo -> getDerecha(), c));
    } else {
        if (nodo -> getIzquierda() == nullptr || nodo -> getDerecha() == nullptr) {
            NodoAVL * tmp = nodo -> getIzquierda() ? nodo -> getIzquierda() : nodo -> getDerecha();

            if (tmp == nullptr) {
                tmp = nodo;
                nodo = nullptr;
            } else * nodo = * tmp;
        } else {
            NodoAVL * tmp = getMin(nodo -> getDerecha());
            nodo -> setCita(tmp -> getCita());
            nodo -> setDerecha(eliminar(nodo -> getDerecha(), tmp -> getCita()));
        }
    }

    if (nodo == nullptr) return nodo;
    nodo -> setAltura(1 + max(altura(nodo -> getIzquierda()), altura(nodo -> getDerecha())));
    int balance = factorBalance(nodo);

    // II
    if (balance > 1 && factorBalance(nodo -> getIzquierda()) >= 0) return rotarDerecha(nodo);
    // ID
    if (balance > 1 && factorBalance(nodo -> getIzquierda()) < 0) {
        nodo -> setIzquierda(rotarIzquierda(nodo -> getIzquierda()));
        return rotarDerecha(nodo);
    }

    // DD
    if (balance < -1 && factorBalance(nodo -> getDerecha()) <= 0) return rotarIzquierda(nodo);
    // DI
    if (balance < -1 && factorBalance(nodo -> getDerecha()) > 0) {
        nodo -> setDerecha(rotarDerecha(nodo -> getDerecha()));
        return rotarIzquierda(nodo);
    }

    return nodo;
}

Cita * AVL::getMaxCita() {
    NodoAVL * actual = raiz;
    while (actual -> getDerecha() != nullptr) actual = actual -> getDerecha();
    return actual -> getCita();
}

// MÉTODOS PÚBLICOS
AVL::AVL() {raiz = nullptr; contador = 0;}

int AVL::altura(NodoAVL * nodo) {return nodo ? nodo -> getAltura() : 0;}
int AVL::factorBalance(NodoAVL * nodo) {return nodo ? altura(nodo -> getIzquierda()) - altura(nodo -> getDerecha()) : 0;}

void AVL::insertarR(int idPaciente) {
    cout << "-------------------------------" << endl;
    cout << "INGRESO DE CITA" << endl;
    string fecha, hora;
    cout << "Ingrese fecha (dd/mm/aaaa): ";
    cin >> fecha;

    cout << "Ingrese hora (hh:mm): ";
    cin >> hora;

    Cita * c = new Cita(++contador, idPaciente, fecha, hora);
    raiz = insertar(raiz, c);

    NodoAVL * comprobacion = buscar(contador);
    if(comprobacion != nullptr) {
        cout << "Cita agregada." << endl;
        c -> mostrarCita();
    }
}

void AVL::insertarAutomaticamente(int idPaciente){
    Cita * c = new Cita(++contador, idPaciente, "09/11/2025", "18:00");

    if(raiz != nullptr){
        Cita * ultCita = getMaxCita();

        int horaInt = ultCita -> getHora() + 15;
        int fechaInt = ultCita -> getFecha();

        if(horaInt > 1440) {
            horaInt = 15;
            fechaInt++;
        }

        c -> setHoraAPartirDeInt(horaInt);
        c -> setFechaAPartirDeInt(fechaInt);
        cout << "Cita agregada automaticamente." << endl;
    }

    // actualizar raíz con el posible nuevo subárbol
    raiz = insertar(raiz, c);
    c -> mostrarCita();
    cout << endl << endl;

}

void AVL::cancelarAutomaticamente(int cantidad){
    for(int i = 0; i < cantidad; i++){
        if(raiz != nullptr){
            Cita * c = raiz -> getCita();
            raiz = eliminar(raiz, c);

            c -> mostrarCita();
            cout << "Cita eliminada correctamente." << endl;
            insertarAutomaticamente(c -> getID_Paciente());

        } else {cout << "No hay más citas para eliminar." << endl; return;}
    }

}


void AVL::cancelarCita(int id_cita) {
    NodoAVL * nodo = buscar(id_cita);
    if (nodo != nullptr) {raiz = eliminar(raiz, nodo -> getCita()); cout << "Cita cancelada." << endl;}
    else cout << "Cita no encontrada para cancelar." << endl;
}

void AVL::reprogramarCita(int id_cita) {
    NodoAVL * nodo = buscar(id_cita);
    if(nodo != nullptr){
        Cita * c = nodo -> getCita();

        string fechaOriginal, horaOriginal;
        fechaOriginal = c -> getFechaString();
        horaOriginal = c -> getHoraString();

        string fecha, hora;
        cout << "Ingrese nueva fecha (dd/mm/aaaa): ";
        cin >> fecha;

        cout << "Ingrese nueva hora (hh:mm): ";
        cin >> hora;

        c -> setFechaString(fecha);
        c -> setHoraString(hora);
        cancelarCita(id_cita);
        raiz = insertar(raiz, c);

        // ESTO ES PARA COMPROBAR SI FUE INSERTADO O NO, PORQUE COMO SE USA RECURSIVIDAD Y SOLO SE IMPRIMIR "NO SE PUDO INSERTAR LA CITA", PUES
        // CON ESTO SI DEVUELVE NULLPTR ES QUE NO LO INSERTO XD
        NodoAVL * nodoComprobacion = buscar(id_cita);

        // SI NO FUE INSERTADO PORQUE HUBO COINCIDENCIA, ENTONCES LO VUELVE INSERTAR PERO CON SU FECHA Y HORA ORIGINAL.
        if(nodoComprobacion == nullptr){
            c -> setFechaString(fechaOriginal);
            c -> setHoraString(horaOriginal);
            raiz = insertar(raiz, c);
            cout << "No se pudo reprogramar la cita por cruce de horarios." << endl;
        } else cout << "Cita reprogramada con exitosamente." << endl;

        // NOTA: Se mantuvo la idea original de cancelar e intentar insertar la misma Cita (reprogramación in-place).
    } else {
        cout << "La cita no pudo reprogramarse porque no fue encontrada." << endl;
    }
}

NodoAVL * AVL::buscar(int id_cita) {
    stack<NodoAVL *> P1, P2;

    if(raiz != nullptr) {
        P1.push(raiz);

        while(P1.empty() == 0) {
            P2.push(P1.top());
            P1.pop();

            if(P1.empty() == 1){
                while(P2.empty() == 0){
                    if(P2.top() -> getCita() -> getID_Cita() == id_cita) return P2.top();
                    if(P2.top() -> getIzquierda() != nullptr) P1.push(P2.top() -> getIzquierda());
                    if(P2.top() -> getDerecha() != nullptr) P1.push(P2.top() -> getDerecha());
                    P2.pop();
                }
            }
        }
    }
    return nullptr;
}

void AVL::inorderR() {inorder(raiz);}
void AVL::preorderR() {preorder(raiz);}

/*bool buscarR(Cita c) {return buscar(raiz, c);}

bool buscar(Node* nodo, Cita c){
    if (nodo == nullptr)
        return false;
    if (n == nodo->getDato())
        return true;
    if (n < nodo->getDato())
        return buscar(nodo->getIzquierda(), n);
    else
        return buscar(nodo->getDerecha(), n);
}
*/
