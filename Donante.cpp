
#include "Donante.h"
#include "LinkedList.h"

LinkedList lista_donante = LinkedList();

struct ListNode *front_donante = nullptr;

Donante::Donante() = default ;

Donante::Donante(const string &nombre, const string &apellido, const string &direccion, const string &email,
                 const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel,
                 const GrupoSanguineo &grupo) : Persona(nombre, apellido, direccion, email, clave, telefono, dni, dia,
                                                        mes, anio, nivel, grupo) {}

void Donante::cargar_donante(Persona p) {
    lista_donante.push(&front_donante, p);
    lista_donante.insertionSort(&front_donante);
}

void Donante::listar_donantes(){
    lista_donante.printList(front_donante);
}

bool Donante::buscar_donante(string email, string clave, Persona &p){
    return lista_donante.buscar(front_donante, email, clave, p);
}

bool Donante::buscar_dni(int dni, Persona &p){
    return lista_donante.buscar_dni(front_donante, dni, p);
}

void Donante::eliminar_donantes(){
    lista_donante.eliminar_lista(front_donante);
}

void Donante::eliminar_donante(int dni){
    lista_donante.eliminar_usuario(front_donante,dni);
}

void Donante::buscar_compatible(string antigeno, char rh, Queue<Persona>& qp) {
    lista_donante.compatible(front_donante, antigeno, rh, qp);
}
void Donante::guardar_donantes(){
    lista_donante.backup(front_donante,"donantes_backup");
}