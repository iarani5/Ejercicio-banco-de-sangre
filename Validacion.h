
#ifndef FINAL_VALIDACION_H
#define FINAL_VALIDACION_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Validacion {
public:
    Validacion();

    bool es_texto(const string &);

    bool es_altura(const string &);

    bool es_telefono(const string &);

    bool es_dni(const string &);

    bool es_email(const string &);

    bool es_clave(const string &);

    bool es_fecha(const string &);

    //Split de fecha para calculo de edad
    void tokenize(const string &, const char, vector<int> &);

};
#endif //FINAL_PROGRAIII_VALIDACION_H
