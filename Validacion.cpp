

#include <iostream>
#include <regex>
#include <vector>
#include "Validacion.h"
#include <boost/algorithm/string.hpp>

using namespace std;

Validacion::Validacion(){}

//split fecha por barra
void Validacion::tokenize(std::string const &str, const char delim, std::vector<int> &out) {
    std::stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(std::stoi(s));
    }
}

/* V A L I D A C I O N E S */

bool Validacion::es_texto(const std::string& s){
    static const std::regex re{"^[a-zA-Z]{3,15}$"};
    if(!std::regex_match(s, re)) cout << "Solo letras! De 3 a 15 caracteres" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_altura(const std::string& s){
    static const std::regex re{"^[\\d]{1,4}$"};
    if(!std::regex_match(s, re)) cout << "Altura invalida" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_telefono(const std::string& s){
    static const std::regex re{"^[\\d]{8,12}$"};
    if(!std::regex_match(s, re)) cout << "Telefono invalido" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_dni(const std::string& s){
    static const std::regex re{"^[\\d]{8}$"};
    if(!std::regex_match(s, re)) cout << "DNI invalido" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_email(const std::string& s){
    static const std::regex re{"^([a-zA-Z\\d\\-\\_\\.]{3,25}@[a-z]{3,15}\\.[a-z]{2,4})?$"};
    if(!std::regex_match(s, re)) cout << "Email  invalido" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_clave(const std::string& s){
    static const std::regex re{"^([a-zA-Z\\d_#,~@%&\\\\\\!\\$\\^\\*\\(\\)\\-\\+\\=\\{\\}\\[\\]\\:\\\\.\\?\\|]{3,15})?$"};
    if(!std::regex_match(s, re)) cout << "Clave  invalida" << endl;
    return std::regex_match(s, re);
}

bool Validacion::es_fecha(const std::string& s){
    static const std::regex re{"^(0?[1-9]|1[0-9]|2[0-9]|3[0-1])(\\/)(0?[1-9]|1[0-2])(\\/)(19[2-9][0-9]|2000)$"};
    if(!std::regex_match(s, re)) cout << "Fecha invalida" << endl;
    return std::regex_match(s, re);
}
