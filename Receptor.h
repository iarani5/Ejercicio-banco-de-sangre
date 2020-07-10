#ifndef FINAL_PROGRAIII_RECEPTOR_H
#define FINAL_PROGRAIII_RECEPTOR_H
#include "Persona.h"


class Receptor : public Persona{

public:

    Receptor();

    Receptor(const string &nombre, const string &apellido, const string &direccion, const string &email,
             const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel,
             const GrupoSanguineo &grupo);

    void cargar_receptor(Persona);

    void listar_receptores();

    void eliminar_receptores();

    void eliminar_receptor(int);

    bool buscar_dni(int, Persona &);

    bool buscar_receptor(string, string, Persona &);

    void guardar_receptores();

    void buscar_compatible (string, char, Queue<Persona>&);

};


#endif //FINAL_PROGRAIII_RECEPTOR_H
