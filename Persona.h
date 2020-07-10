
#ifndef FINAL_PERSONA_H
#define FINAL_PERSONA_H
#include <iostream>
#include <string>
#include <stack.h>
#include "queue.h"

using namespace std;

struct GrupoSanguineo {
    string antigeno;
    char rh;

    void const puede_donar(Queue<string>& q) const{
        if(!this->antigeno.compare("A")) {
            if(this->rh==45){
                q.enqueue("A+");
                q.enqueue("AB+");
                q.enqueue("A-");
                q.enqueue("AB-");
            }
            else{
                q.enqueue("A+");
                q.enqueue("AB+");
            }
        }
        else if(!this->antigeno.compare("B")) {
            if(this->rh==45){
                q.enqueue("B+");
                q.enqueue("B-");
                q.enqueue("AB+");
                q.enqueue("AB-");
            }
            else{
                q.enqueue("B+");
                q.enqueue("AB+");
            }
        }
        else if(!this->antigeno.compare("AB")) {
            if(this->rh==45){
                q.enqueue("AB+");
                q.enqueue("AB-");
            }
            else{
                q.enqueue("AB+");
            }
        }
        else if(!this->antigeno.compare("0")) {
            if(this->rh == 45){ // dador universal
                q.enqueue("A+");
                q.enqueue("A-");
                q.enqueue("B-");
                q.enqueue("B-");
                q.enqueue("AB+");
                q.enqueue("AB-");
                q.enqueue("0-");
                q.enqueue("0+");
            }
            else{
                q.enqueue("B+");
                q.enqueue("A+");
                q.enqueue("AB+");
                q.enqueue("0+");
            }
        }
    };

    void puede_recibir(Queue<string>& q) const{
        if(!this->antigeno.compare("A")) {
            if(this->rh==45){
                q.enqueue("A-");
                q.enqueue("0-");
            }
            else{
                q.enqueue("A+");
                q.enqueue("A-");
                q.enqueue("0-");
                q.enqueue("0+");
            }
        }
        else if(!this->antigeno.compare("B")) {
            if(this->rh==45){
                q.enqueue("B-");
                q.enqueue("0-");
            }
            else{
                q.enqueue("B+");
                q.enqueue("B-");
                q.enqueue("0+");
                q.enqueue("0-");
            }
        }
        else if(!this->antigeno.compare("AB")) {
            if(this->rh==45){
                q.enqueue("A-");
                q.enqueue("B-");
                q.enqueue("0-");
                q.enqueue("AB-");
            }
            else{ // receptor universal
                q.enqueue("A+");
                q.enqueue("A-");
                q.enqueue("B-");
                q.enqueue("B-");
                q.enqueue("AB+");
                q.enqueue("AB-");
                q.enqueue("0-");
                q.enqueue("0+");
            }
        }
        else if(!this->antigeno.compare("0")) {
            if(this->rh==45){ //comparo con codigo ascii para valor -
                q.enqueue("0-");
            }
            else{
                q.enqueue("0-");
                q.enqueue("0+");
            }
        }
    };
};

class Persona {

    // A T R I B U T O S

    string nombre;
    string apellido;
    string direccion;
    string email;
    string clave;
    int telefono;
    int dni;
    int dia;
    int mes;
    int edad;
    int anio;
    bool nivel; //false:usuario true:admin
    GrupoSanguineo grupo;

    // M E T O D O S

    int calcular_edad(int,int,int,bool);

    bool logear(string, string, Persona&, bool&);

public:

    void coincidir(Persona,bool);

    void backup();

    bool buscar_dni(int, Persona&);

    bool get_grupo(int,Persona);

    void eliminar_usuario(int, bool &);

    void editar_datos(Persona &, bool, bool&);

    void listar_usuarios();

    void listar_donantes();

    void listar_receptores();

    void carga_inicial();

    void elimiar_lista();

    Persona registro(bool &, bool);

    Persona login (bool &);

    // C O N S T R U C T O R E S

    Persona();

    Persona(const string &nombre, const string &apellido, const string &direccion, const string &email,
            const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel, const GrupoSanguineo &grupo);

    // G E T T E R S   &   S E T T E R S

    int getEdad() const;

    void setEdad(int edad);

    bool isNivel() const;

    void setNivel(bool nivel);

    const string &getNombre() const;

    void setNombre(const string &nombre);

    const string &getApellido() const;

    void setApellido(const string &apellido);

    const string &getDireccion() const;

    void setDireccion(const string &direccion);

    const string &getEmail() const;

    void setEmail(const string &email);

    const string &getClave() const;

    void setClave(const string &clave);

    int getTelefono() const;

    void setTelefono(int telefono);

    int getDni() const;

    void setDni(int dni);

    void setDia(int dia);

    void setMes(int mes);

    void setAnio(int anio);

    const GrupoSanguineo &getGrupo() const;

    void setGrupo(const GrupoSanguineo &grupo);

};


#endif //FINAL_PERSONA_H
