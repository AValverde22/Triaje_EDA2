#ifndef CITA_H
#define CITA_H

#include <string>
using namespace std;

class Cita {
    private:
        int idCita;
        int idPaciente;
        string fecha;
        string hora;

    public:
        Cita();
        Cita(int id_cita, int id_paciente, string fecha_i, string hora_i);

        int getID_Cita();
        void setID_Cita(int id_cita);

        int getID_Paciente();
        void setID_Paciente(int id_paciente);

        string getFechaString();
        void setFechaString(string fecha_i);

        string getHoraString();
        void setHoraString(string hora_i);

        int getFecha();
        void setFechaAPartirDeInt(int fecha_i);

        int getHora();
        void setHoraAPartirDeInt(int hora_i);

        void mostrarCita();
};

#endif
