
#include "Receptor.h"
#include "LinkedList.h"

LinkedList lista_receptor = LinkedList();

struct ListNode *front_receptor = nullptr;

Receptor::Receptor() = default ;

Receptor::Receptor(const string &nombre, const string &apellido, const string &direccion, const string &email,
                   const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel,
                   const GrupoSanguineo &grupo) : Persona(nombre, apellido, direccion, email, clave, telefono, dni, dia,
                                                          mes, anio, nivel, grupo) {}

void Receptor::cargar_receptor(Persona p) {
    lista_receptor.push(&front_receptor, p);
    lista_receptor.insertionSort(&front_receptor);
}


void Receptor::listar_receptores(){
    lista_receptor.printList(front_receptor);
}

bool Receptor::buscar_receptor(string email, string clave, Persona& p){
    return lista_receptor.buscar(front_receptor, email, clave, p);
}

bool Receptor::buscar_dni(int dni, Persona& p){
    return lista_receptor.buscar_dni(front_receptor, dni, p);
}

void Receptor::buscar_compatible(string antigeno, char rh, Queue<Persona>&p){
    lista_receptor.compatible(front_receptor, antigeno, rh,p);
}

void Receptor::eliminar_receptores(){
    lista_receptor.eliminar_lista(front_receptor);
}
void Receptor::eliminar_receptor(int dni){
    lista_receptor.eliminar_usuario(front_receptor, dni);
}

void Receptor::guardar_receptores(){
    lista_receptor.backup(front_receptor,"receptores_backup");
}