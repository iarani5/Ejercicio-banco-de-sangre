
#ifndef FINAL_DONANTE_H
#define FINAL_DONANTE_H
#include "Persona.h"

class Donante : public Persona  {
public:
    Donante();

    Donante(const string &nombre, const string &apellido, const string &direccion, const string &email,
            const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel,
            const GrupoSanguineo &grupo);

    void cargar_donante(Persona);

    void listar_donantes();

    void eliminar_donantes();

    void eliminar_donante(int);

    bool buscar_donante(string, string, Persona&);

    bool buscar_dni(int, Persona &);

    void guardar_donantes();

    void buscar_compatible (string, char, Queue<Persona>&);

};


#endif //FINAL_PROGRAIII_DONANTE_H
