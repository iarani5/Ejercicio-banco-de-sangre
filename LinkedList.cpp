
#include "LinkedList.h"
#include "Receptor.h"
#include "Donante.h"
#include "Persona.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>

using namespace std;

void LinkedList::eliminar_lista(ListNode *front) {
    ListNode *next;
    for (ListNode *ptr = front; ptr != nullptr; ptr = next) {
        next = ptr->next;
        delete ptr;
    }
}

bool LinkedList::buscar(struct ListNode *head, string mail, string clave, Persona &p){
    struct ListNode *temp = head;
    while(temp != nullptr) {
        if(!temp->data.getEmail().compare(mail) && !temp->data.getClave().compare(clave)){
            p=temp->data;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void LinkedList::compatible(struct ListNode *head, string antigeno, char rh,Queue<Persona>& q){
    struct ListNode *temp = head;
    while(temp != nullptr) {
        if(!temp->data.getGrupo().antigeno.compare(antigeno) && temp->data.getGrupo().rh==rh){
            q.enqueue(temp->data);
        }
        temp = temp->next;
    }
}

bool LinkedList::buscar_dni(struct ListNode *head, int dni, Persona &p){
    struct ListNode *temp = head;
    while(temp != nullptr) {
        if(temp->data.getDni()==dni){
            p=temp->data;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void LinkedList::eliminar_usuario(ListNode *&front, int index) {
    int i=0;
    for (ListNode *ptr = front; ptr != nullptr; ptr = ptr->next) {
        if(ptr->data.getDni()==index){
            index=i;
        }
        i++;
    }
    if (front == nullptr) {
        return;
    }
    if (index == 0) {
        ListNode *trash = front;
        front = front->next;
        delete trash;
    }
    else {
        ListNode *tmp = front;
        for (int j = 0; j < index - 1; j++) {
            tmp = tmp->next;
            if (tmp == nullptr) {
                return;
            }
        }
        ListNode *trash = tmp->next;
        tmp->next = tmp->next->next;
        delete trash;
    }
}

void LinkedList::insertionSort(struct ListNode **head_ref) {
    struct ListNode *sorted = nullptr;
    struct ListNode *current = *head_ref;
    while (current != nullptr) {
        struct ListNode *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *head_ref = sorted;
}


void LinkedList::sortedInsert(struct ListNode** head_ref, struct ListNode* new_node) {
    struct ListNode* current;
    if (*head_ref == nullptr || (*head_ref)->data.getApellido() >= new_node->data.getApellido() ) {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else {
        current = *head_ref;
        while (current->next!=nullptr && current->next->data.getApellido() < new_node->data.getApellido()){
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void LinkedList::printList(struct ListNode *head){
    struct ListNode *temp = head;
    while(temp != nullptr) {
        cout << "" << endl;
        cout << "Apellido: " << temp->data.getApellido() << endl;
        cout << "Nombre: " <<  temp->data.getNombre() << endl;
        cout << "Email: " << temp->data.getEmail() << endl;
        cout << "Telefono: " << temp->data.getTelefono() << endl;
        cout << "DNI: " << temp->data.getDni() << endl;
        cout << "Edad: " << temp->data.getEdad() << endl;
        if(temp->data.isNivel()) cout << "Nivel: Administrador" << endl;
        else cout << "Nivel: Usuario" << endl;
        cout << "GRUPO SANGUINEO: " << temp->data.getGrupo().antigeno << temp->data.getGrupo().rh << endl;
        temp = temp->next;
    }
}

// BACKUP
void LinkedList::backup(struct ListNode *head, string nombre){
    struct ListNode *temp = head;
    ofstream outputfile;
    outputfile.open(nombre);
    outputfile  << "\n----- L I S T A D O   D E   U S U A R I O S -----\n" << endl;
    while(temp != nullptr) {
        outputfile << "" << endl;
        outputfile << "Apellido: " << temp->data.getApellido() << endl;
        outputfile << "Nombre: " <<  temp->data.getNombre() << endl;
        outputfile << "Email: " << temp->data.getEmail() << endl;
        outputfile << "Telefono: " << temp->data.getTelefono() << endl;
        outputfile << "DNI: " << temp->data.getDni() << endl;
        outputfile << "Edad: " << temp->data.getEdad() << endl;
        if(temp->data.isNivel()) outputfile << "Nivel: Administrador" << endl;
        else outputfile << "Nivel: Usuario" << endl;
        outputfile << "GRUPO SANGUINEO: " << temp->data.getGrupo().antigeno << temp->data.getGrupo().rh << endl;
        temp = temp->next;
    }
}

void LinkedList::push(struct ListNode** head_ref, Persona new_data) {
    struct ListNode* new_node = new ListNode;
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}
