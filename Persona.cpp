
#include "Persona.h"
#include "Donante.h"
#include "Receptor.h"
#include "Validacion.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <limits>

using namespace std;

Persona::Persona(){};

Persona::Persona(const string &nombre, const string &apellido, const string &direccion, const string &email,
                 const string &clave, int telefono, int dni, int dia, int mes, int anio, bool nivel, const GrupoSanguineo &grupo)
        : nombre(nombre), apellido(apellido), direccion(direccion), email(email), clave(clave), telefono(telefono),
          dni(dni), dia(dia), mes(mes), anio(anio), nivel(nivel), grupo(grupo) {

    calcular_edad(dia,mes,anio,false);
}

void Persona::carga_inicial() {
    GrupoSanguineo grupo_sanguineo = GrupoSanguineo();

    // Donantes
    grupo_sanguineo.antigeno="AB";
    grupo_sanguineo.rh='+';
    Donante donante = Donante ("John","Smith", "Esporta 3028", "johnny@gmail.com", "jonny1234",45421199,36002048,12,12,1990,0,grupo_sanguineo);
    donante.cargar_donante(donante);

    grupo_sanguineo.antigeno="B";
    grupo_sanguineo.rh='-';
    donante = Donante ("Ana","Tabano", "Mendoza 1430", "annie@gmail.com", "martita15",1538492850,32593850,5,3,1980,0,grupo_sanguineo);
    donante.cargar_donante(donante);

    grupo_sanguineo.antigeno="0";
    grupo_sanguineo.rh='+';
    donante = Donante ("Mariano","Navarro", "Segurola 129", "mariano@gmail.com", "1234",1575663911,38995574,17,9,1995,0,grupo_sanguineo);
    donante.cargar_donante(donante);

    // Receptores
    grupo_sanguineo.antigeno="A";
    grupo_sanguineo.rh='+';
    Receptor receptor = Receptor ("Pablo","Sans", "La Pampa 1152", "pab294@gmail.com", "fefee43",1568392058,35049381,0,9,1986,0,grupo_sanguineo);
    receptor.cargar_receptor(receptor);

    grupo_sanguineo.antigeno="B";
    grupo_sanguineo.rh='+';
    receptor = Receptor ("Marcela","Malo", "Zapiola 1432", "marcelao@gmail.com", "1234",47739287,30294859,19,11,1965,0,grupo_sanguineo);
    receptor.cargar_receptor(receptor);

    grupo_sanguineo.antigeno="0";
    grupo_sanguineo.rh='-';
    receptor = Receptor ("Iara","Nizza", "Cortina 3948", "iara@gmail.com", "1234",1538495873,37049548,14,3,1992,1,grupo_sanguineo);
    receptor.cargar_receptor(receptor);

}

void Persona::listar_usuarios(){
    cout << "\n----- L I S T A D O   D E   U S U A R I O S" << endl;
    cout << "\n----------------------- R E C E P T O R E S" << endl;

    Receptor receptor = Receptor();
    receptor.listar_receptores();
    cout << "\n--------------------------- D O N A N T E S" << endl;
    Donante donante = Donante();
    donante.listar_donantes();
}

void Persona::backup(){
    Donante donante = Donante();
    donante.guardar_donantes();
    Receptor receptor = Receptor();
    receptor.guardar_receptores();
}

void Persona::listar_donantes(){
    cout << "\n--------- U S U A R I O S   D O N A N T E S" << endl;
    Donante donante = Donante();
    donante.listar_donantes();
}

void Persona::listar_receptores(){
    cout << "\n----- U S U A R I O S   R E C E P T O R E S" << endl;
    Receptor receptor = Receptor();
    receptor.listar_receptores();
}

void Persona::elimiar_lista(){
    Donante donante = Donante();
    donante.eliminar_donantes();
    Receptor receptor = Receptor();
    receptor.eliminar_receptores();
};

bool Persona::buscar_dni(int dni, Persona &p) {
    Donante donante = Donante();
    if(!donante.buscar_dni(dni,p)) {
        Receptor receptor = Receptor();
        if(!receptor.buscar_dni(dni,p)) return 0;
    }
    return 1;
}

bool Persona::get_grupo(int dni, Persona p){
    Donante donante = Donante();
    if(donante.buscar_dni(dni,p)) {
        return 1;
    }
    return 0;
}

void listar(Persona rta){
    cout << "Apellido: " << rta.getApellido() << endl;
    cout << "Nombre: " << rta.getNombre() << endl;
    cout << "Email: " << rta.getEmail() << endl;
    cout << "Telefono: " << rta.getTelefono() << endl;
    cout << "DNI: " << rta.getDni() << endl;
    cout << "Edad: " << rta.getEdad() << endl;
    cout << "GRUPO SANGUINEO: " << rta.getGrupo().antigeno << rta.getGrupo().rh << endl;
    cout << "" << endl;
}

// MATCH
void Persona::coincidir(Persona p, bool estado){
    Queue<string> q;
    Queue<Persona> rta;
    cout << "\n-------- USUARIOS ";
    if(estado) cout << "RECEPTORES ";
    else cout << "DONANTES ";
    cout << "COMPATIBLES CON TU GRUPO SANGUIENO (" << p.getGrupo().antigeno << p.getGrupo().rh << ")\n"<< endl;
    if(estado) { //donante busca receptor
        p.getGrupo().puede_donar(q);
        //recorro receptores para hallar compatibilidad
        cout << "Compatible con: ";
        while(!q.isEmpty()){
            cout << q.peek() <<" ";
            string rh_string=q.peek().substr(q.peek().length()-1, q.peek().length());
            string antigeno=q.peek().substr(0,q.peek().length()-1);
            char rh=rh_string[0];
            Receptor receptor = Receptor();
            receptor.buscar_compatible(antigeno,rh,rta);
            q.dequeue();
        }
        cout << "\n" << endl;
        if(rta.isEmpty()){
            cout << "\nNo hay usuarios compatibles." << endl;
        }
        else{
            while(!rta.isEmpty()){
                listar(rta.peek());
                rta.dequeue();
            }
        }
    }
    else { //receptor busca donante
        p.getGrupo().puede_recibir(q);
        //recorro donantes para hallar compatibilidad
        cout << "Compatible con: ";
        while(!q.isEmpty()){
            cout << q.peek() <<" ";
            string rh_string=q.peek().substr(q.peek().length()-1, q.peek().length());
            string antigeno=q.peek().substr(0,q.peek().length()-1);
            char rh=rh_string[0];
            Donante donante = Donante();
            donante.buscar_compatible(antigeno,rh,rta);
            q.dequeue();
        }
        cout << "\n" << endl;
        if(rta.isEmpty()){
            cout << "\nNo hay usuarios compatibles." << endl;
        }
        else {
            while (!rta.isEmpty()) {
                listar(rta.peek());
                rta.dequeue();
            }
        }
    }
};

// LOGIN

bool Persona::logear(string e, string c, Persona &p, bool &estado) { //estado (1:donante, 0:receptor)
    bool rta;
    Donante donante = Donante();
    rta = donante.buscar_donante(e,c,p);
    estado=1;
    if(rta) return 1;
    Receptor receptor = Receptor();
    rta= receptor.buscar_receptor(e,c,p);
    estado=0;
    if(rta) return 1;
    return 0;
};

Persona Persona::login(bool &estado){
    Persona p = Persona();
    string email, clave;
    bool ban=0;
    cout << "\nL O G I N" << endl;
    do {
        cout << "\nEmail: ";
        cin >> email;
        cout << "Clave: ";
        cin >> clave;

        if (logear(email, clave, p, estado)) {
            ban=1;
            return p;
        } else {
            cout << "Error, email o clave incorrectos";
        }
    }while(!ban);
};

// REGISTRO

Persona Persona::registro(bool &estado, bool es_admin){

    Validacion v = Validacion();
    string nombre;
    string apellido;
    string calle;
    string email;
    string clave;
    string altura;
    int telefono;
    int dni;
    GrupoSanguineo grupo;

    cout << "\nR E G I S T R O\n" << endl;
    cout << "DATOS PERSONALES:" << endl;

    do{
        cout << "Nombre:";
        cin >> nombre;
    }while(!v.es_texto(nombre));

    do{
        cout << "Apellido:";
        cin >> apellido;
    }while(!v.es_texto(apellido));

    do{
        cout << "Direccion (calle):";
        cin >> calle;
    }while(!v.es_texto(calle));

    do{
        cout << "Direccion (altura):";
        cin >> altura;
    }while(!v.es_altura(altura));

    string tel;
    do{
        cout << "Telefono:";
        cin >> tel;
    }while(!v.es_telefono(tel));
    telefono=std::stoi( tel );

    string dni_s;
    do{
        cout << "N° DNI:";
        cin >> dni_s;
    }while(!v.es_dni(dni_s));
    dni=std::stoi( dni_s );

    string fecha;
    do{
        cout << "Fecha de nacimiento (dd/mm/yyyy) (+18):" ;
        cin >> fecha;
    }while(!v.es_fecha(fecha));
    vector<int> date;
    v.tokenize(fecha,'/',date);

    do{
        cout << "Email: " ;
        cin >> email;
    }while(!v.es_email(email));

    do{
        cout << "Clave: " ;
        cin >> clave;
    }while(!v.es_clave(clave));

    cout << "\nGRUPO SANGUINEO:" << endl;
    GrupoSanguineo grupo_sanguineo;
    do {
        cout << "Antigeno (0/A/B/AB): ";
        cin >> grupo_sanguineo.antigeno;
    }while( grupo_sanguineo.antigeno!="A"&&
            grupo_sanguineo.antigeno!="B"&&
            grupo_sanguineo.antigeno!="AB"&&
            grupo_sanguineo.antigeno!="0"
            );
    do {
        cout << "Factor RH (+/-): ";
        cin >> grupo_sanguineo.rh;
    }while( grupo_sanguineo.rh!='+'&& grupo_sanguineo.rh!='-');

    int opcion;
    do {
        cout << "\n--------------------" << endl;
        cout << "1. Soy Donante     |" << endl;
        cout << "2. Soy Receptor    |" << endl;
        cout << "--------------------" << endl;
        while (std::cout << "Elegir opcion: " && !(std::cin >> opcion)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcion invalida. \n";
        }
    }while( opcion!=1&&opcion!=2);

    cout << "Usuario creado con exito" << endl;
    cout << "------------------------------------------------------------------------------------------------" << endl;

    if(opcion==1){
        Donante donante = Donante (nombre,apellido, calle + " " +altura, email, clave,telefono,dni,date[0],date[1],date[2],0,grupo_sanguineo);
        donante.cargar_donante(donante);
        if(!es_admin) estado=1;
        return donante;
    }
    else{
        Receptor receptor = Receptor (nombre,apellido, calle + " " +altura, email, clave,telefono,dni,date[0],date[1],date[2],0,grupo_sanguineo);
        receptor.cargar_receptor(receptor);
        if(!es_admin) estado=0;
        return receptor;
    }
};

// ELIMINAR CUENTA

void Persona::eliminar_usuario(int dni, bool &estado) {
    if(estado){
        Donante donante = Donante();
        donante.eliminar_donante(dni);
    }
    else{
        Receptor receptor = Receptor();
        receptor.eliminar_receptor(dni);
    }
}

// EDITAR DATOS USUARIO

void Persona::editar_datos(Persona &p, bool modo_admin, bool& estado){

    Validacion v = Validacion();
    Persona es_admin = p;

    //si es admin y quiere editar usuario
    Persona usuario_editar = Persona();
    bool repetir;
    int dni_aux;
    if(modo_admin){
        p.listar_usuarios();
        do{
            int dni;
            repetir=false;
            cout << "-------------------------------------" << endl;
            while (std::cout << "DNI de usuario a editar: " && !(std::cin >> dni)) {
                std::cin.clear(); //clear bad input flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Opcion invalida. \n";
            }

            if(!buscar_dni(dni,usuario_editar)){
                std::cout << "DNI no diponible\n";
                repetir = true;
            }

        }while(repetir);
        p=usuario_editar;
        dni_aux=usuario_editar.getDni();
    }

    int opcion;
    do {

        //encriptacion de clave
        string encriptada="*";
        for(int i=1;i<p.getClave().length();i++){
            encriptada+="*";
        }

        if(modo_admin) cout << "\nU S U A R I O   D A T O S (Editar)\n" << endl;
        else cout << "\nM I S   D A T O S (Editar)\n" << endl;
        cout << "1. Apellido: " << p.getApellido() << endl;
        cout << "2. Nombre: " << p.getNombre() << endl;
        cout << "3. Email: " << p.getEmail() << endl;
        cout << "4. Clave: " << encriptada << endl;
        cout << "5. Direccion: " << p.getDireccion() << endl;
        cout << "6. Telefono: " << p.getTelefono() << endl;
        cout << "7. DNI: " << p.getDni() << endl;
        cout << "8. Edad: " << p.getEdad() << endl;
        cout << "9. Grupo sanguineo: " << p.getGrupo().antigeno << p.getGrupo().rh << endl;
        if (!modo_admin&&estado||modo_admin&&p.get_grupo(dni_aux,usuario_editar)) cout << "10. Es Donante " << endl;
        else cout << "10. Es Receptor " << endl;
        if (modo_admin) cout << "11. ";   //si es admin puede editar el nivel
        if (p.isNivel()) cout << "Nivel: Administrador" << endl;
        else cout << "Nivel: Usuario" << endl;
        cout << "0. Salir" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Dato a editar: ";
        cin >> opcion;

        switch(opcion) {
            case 1:{
                string apellido;
                do {
                    cout << "Apellido:";
                    cin >> apellido;
                } while (!v.es_texto(apellido));
                p.setApellido(apellido);
                cout << "Apellido editado con exito"<< endl;
            }
                break;
            case 2:{
                string nombre;
                do {
                    cout << "Nombre:";
                    cin >> nombre;
                } while (!v.es_texto(nombre));
                p.setNombre(nombre);
                cout << "Nombre editado con exito"<< endl;
            }
                break;
            case 3:{
                string email;
                do {
                    cout << "Email:";
                    cin >> email;
                } while (!v.es_email(email));
                p.setEmail(email);
                cout << "Email editado con exito"<< endl;
            }
                break;
            case 4:{
                string clave_actual;
                string clave_nueva;
                cout << "Clave Actual:";
                cin >> clave_actual;
                if(!p.getClave().compare(clave_actual)){
                    do {
                        cout << "Clave Nueva:";
                        cin >> clave_nueva;
                    } while (!v.es_clave(clave_nueva));
                    p.setClave(clave_nueva);
                    cout << "Clave editada con exito"<< endl;

                }
                else{
                    cout << "Error. La clave no coincide"<< endl;
                }
            }
                break;
            case 5:{
                string calle;
                string altura;
                do{
                    cout << "Direccion (calle):";
                    cin >> calle;
                }while(!v.es_texto(calle));

                do{
                    cout << "Direccion (altura):";
                    cin >> altura;
                }while(!v.es_altura(altura));
                p.setDireccion(calle+" "+altura);
                cout << "Direccion editada con exito"<< endl;
            }
                break;
            case 6:{
                string tel;
                do{
                    cout << "Telefono:";
                    cin >> tel;
                }while(!v.es_telefono(tel));
                int telefono=std::stoi( tel );
                p.setTelefono(telefono);
                cout << "Telefono editado con exito"<< endl;
            }
                break;
            case 7:{
                string dni_s;
                do{
                    cout << "N° DNI:";
                    cin >> dni_s;
                }while(!v.es_dni(dni_s));
                int dni=std::stoi( dni_s );
                p.setDni(dni);
                cout << "DNI editado con exito"<< endl;
            }
                break;
            case 8:{
                string fecha;
                do{
                    cout << "Fecha de nacimiento (dd/mm/yyyy) (+18):" ;
                    cin >> fecha;
                }while(!v.es_fecha(fecha));
                vector<int> date;
                v.tokenize(fecha,'/',date);
                p.setDia(date[0]);
                p.setMes(date[1]);
                p.setAnio(date[2]);
                p.setEdad(p.calcular_edad(date[0],date[1],date[2],true));
                cout << "Fecha editada con exito"<< endl;
            }
                break;
            case 9:{
                cout << "\nGRUPO SANGUINEO:" << endl;
                GrupoSanguineo grupo_sanguineo;
                do {
                    cout << "Antigeno (0/A/B/AB): ";
                    cin >> grupo_sanguineo.antigeno;
                }while( grupo_sanguineo.antigeno!="A"&&
                        grupo_sanguineo.antigeno!="B"&&
                        grupo_sanguineo.antigeno!="AB"&&
                        grupo_sanguineo.antigeno!="0"
                        );
                do {
                    cout << "Factor RH (+/-): ";
                    cin >> grupo_sanguineo.rh;
                }while( grupo_sanguineo.rh!='+'&& grupo_sanguineo.rh!='-');
                p.setGrupo(grupo_sanguineo);
            }
                break;
            case 10:{
                Persona p_nueva=p;
                if(modo_admin){
                    bool estado_aux=p.get_grupo(dni_aux,p_nueva);
                    p.eliminar_usuario(dni_aux, estado_aux);
                }
                else{
                    p.eliminar_usuario(p.getDni(),estado);
                }
                if(estado||modo_admin){
                    Receptor receptor = Receptor();
                    receptor.cargar_receptor(p_nueva);
                    cout << "Ahora es Receptor" << endl;
                    if(!modo_admin) estado=0;
                }
                else{
                    Donante donante = Donante();
                    donante.cargar_donante(p_nueva);
                    cout << "Ahora es Donante"<< endl;
                    if(!modo_admin)  estado=1;
                }
            }
                break;
            case 11:
                if(modo_admin){
                    if(p.isNivel()) p.setNivel(0);
                    else p.setNivel(1);
                }
                else{
                    cout << "Opcion no disponible"<< endl;
                }
                break;
        }
    }while(opcion>=1&&opcion<=12);
    p=es_admin;
};

// CALCULAR EDAD

int Persona::calcular_edad(int dia, int mes, int anio, bool cuando) {

    // fecha actual
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    int current_date = aTime->tm_mday;
    int current_month = aTime->tm_mon + 1;
    int current_year = aTime->tm_year + 1900;

    if (dia > current_date) {
        current_month = current_month - 1;
    }

    if (mes > current_month) {
        current_year = current_year - 1;
    }

    int calculated_year = current_year - anio;
    if(!cuando) this->edad = calculated_year; //usuario recien creado
    else return calculated_year;// edicion de edad
}

//G E T T E R S   &   S E T T E R S

const string &Persona::getNombre() const {
    return nombre;
}

void Persona::setNombre(const string &nombre) {
    Persona::nombre = nombre;
}

const string &Persona::getApellido() const {
    return apellido;
}

void Persona::setApellido(const string &apellido) {
    Persona::apellido = apellido;
}

const string &Persona::getDireccion() const {
    return direccion;
}

void Persona::setDireccion(const string &direccion) {
    Persona::direccion = direccion;
}

const string &Persona::getEmail() const {
    return email;
}

void Persona::setEmail(const string &email) {
    Persona::email = email;
}

const string &Persona::getClave() const {
    return clave;
}

void Persona::setClave(const string &clave) {
    Persona::clave = clave;
}

int Persona::getTelefono() const {
    return telefono;
}

void Persona::setTelefono(int telefono) {
    Persona::telefono = telefono;
}

int Persona::getDni() const {
    return dni;
}

void Persona::setDni(int dni) {
    Persona::dni = dni;
}

void Persona::setDia(int dia) {
    Persona::dia = dia;
}

void Persona::setMes(int mes) {
    Persona::mes = mes;
}

void Persona::setAnio(int anio) {
    Persona::anio = anio;
}

const GrupoSanguineo &Persona::getGrupo() const {
    return grupo;
}

void Persona::setGrupo(const GrupoSanguineo &grupo) {
    Persona::grupo = grupo;
}

bool Persona::isNivel() const {
    return nivel;
}

void Persona::setNivel(bool nivel) {
    Persona::nivel = nivel;
}

int Persona::getEdad() const {
    return edad;
}

void Persona::setEdad(int edad) {
    Persona::edad = edad;
}
