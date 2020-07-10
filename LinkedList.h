//
// Created by sharon on 21/11/18.
//

#ifndef FINAL_LINKEDLIST_H
#define FINAL_LINKEDLIST_H

#include "Persona.h"
#include <iostream>

using namespace std;

struct ListNode {
    Persona data;
    struct ListNode* next;
};

class LinkedList {

public:
    void eliminar_lista(ListNode *);
    bool buscar(struct ListNode *, string, string, Persona &);
    bool buscar_dni(struct ListNode *, int, Persona &);
    void eliminar_usuario(ListNode *&, int);
    void sortedInsert(struct ListNode**, struct ListNode*);
    void insertionSort(struct ListNode **);
    void push(struct ListNode** , Persona );
    void printList(struct ListNode *);
    void backup(struct ListNode *, string);
    void compatible(struct ListNode *, string, char, Queue<Persona>&);

};





#endif //FINAL_LINKEDLIST_H
