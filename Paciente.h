#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
using namespace std;

class Paciente {
    private:
        int idPaciente;
        string nombre;
        int urgencia;
        string estado;
        string fecha;

    public:
        Paciente(int id, string nom, int urg, string fecha_i);

        int getId();
        string getNombre();
        int getUrgencia();
        string getEstado();
        string getFecha();

        void setId(int i);
        void setEstado(string e);
        void setFecha (string f);

        void mostrar();
};

#endif
