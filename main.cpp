/*
      FINAL PROGRAMACION III

    - Autora: Iara Nizza (11657)

    - Fecha: 21/11/2018

    - Proyecto: Programa de Gestión de un Banco de Sangre
      El programa cumple los siguientes requisitos:
      - Registrar un nuevo usuario
      - Inciar sesion
      - Calcular edad de usuario
      - Editar datos personales usuario
      - Eliminar cuenta
      - Listar usuarios Receptores y Donantes
      - Matchear entre los usuarios del sistema que puedan donar o recibir sangre de un factor sanguineo compatible
      - Nivel con permisos (Admin/usuario)
        El administrador a su vez puede acceder a un panel de control para:
        - Listar usuarios
        - Crear usuarios
        - Editar usuarios (Cambiar nivel de permisos)
        - Eliminar usuarios
        - Realizar Backup de datos

    - Estructuras de datos utilizadas:
        -LinkedList
        -Vectores
        -Colas
*/


#include <iostream>
#include "Persona.h"
#include <limits>


using namespace std;

int menu(Persona p, bool estado) {
    int opcion;
    cout << "\n--------------------------------------------- MENU -------------------------------------------" << endl;
    if(p.isNivel()) cout << "ADMINISTRADOR " ;
    if(!p.isNivel()) cout << "USUARIO " ;
    if(estado) cout << "DONANTE: " << p.getNombre() << " " << p.getApellido() << endl;
    if(!estado) cout << "RECEPTOR: " << p.getNombre() << " " << p.getApellido() << endl;
    if(!p.isNivel()&&estado) cout << "\n1. Listar usuarios receptores" << endl;
    if(!p.isNivel()&&!estado) cout << "\n1. Listar usuarios donantes" << endl;
    if(p.isNivel()) cout << "\n1. Listar todos los usuarios " << endl;
    cout << "2. Editar mi informacion" << endl;
    cout << "3. Eliminar mi cuenta" << endl;
    cout << "4. Buscar coincidencias " << endl;
    if(p.isNivel())  cout << "5. Panel de control " << endl;
    cout << "0. Salir" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    while (std::cout << "Elegir opcion: " && !(std::cin >> opcion)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcion invalida. \n";
    }
    return opcion;
}

int menu_panel() {
    int opcion;
    cout << "\n-------------------------------- PANEL DE CONTROL ---------------------------------------------" << endl;
    cout << "1. Listar usuarios receptores" << endl;
    cout << "2. Listar usuarios donantes" << endl;
    cout << "3. Crear usuario" << endl;
    cout << "4. Editar usuario" << endl;
    cout << "5. Eliminar usuario" << endl;
    cout << "6. Realizar Backup" << endl;
    cout << "0. Salir del panel" << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
    while (std::cout << "Elegir opcion: " && !(std::cin >> opcion)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcion invalida. \n";
    }
    return opcion;
}

int inicio(Persona &p, bool & estado){
    int opcion;
    cout << "\n------------------------------------- Banco de Sangre -----------------------------------------" << endl;
    cout << "1. Iniciar sesion  " << endl;
    cout << "2. Registrarme    " << endl;
    cout << "-------------------------------------" << endl;
    while (std::cout << "Elegir opcion: " && !(std::cin >> opcion)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcion invalida. \n";
    }
    return opcion;
};

int cuenta_a_eliminar(){
    int dni;
    cout << "-------------------------------------" << endl;
    while (std::cout << "DNI de usuario a eliminar: " && !(std::cin >> dni)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Opcion invalida. \n";
    }
    return dni;
};

int main() {
    bool estado, sesion_cerrada = false;
    int seleccion, opcion;
    Persona p = Persona();
    p.carga_inicial();
    opcion = inicio(p, estado);
    switch (opcion) {
        case 1:
            p = p.login(estado);
            break;
        case 2:
            p = p.registro(estado,false);
            break;
        default:
            cout << "Opcion no disponible";
            return 0;
    }

    do{
        seleccion=menu(p,estado);
        switch(seleccion){
            case 1: //listar usuarios
                if(p.isNivel()) p.listar_usuarios();
                else if(!estado) p.listar_donantes();
                else if(estado) p.listar_receptores();
                break;
            case 2:  //editar datos personales
                p.editar_datos(p,false,estado);
                break;
            case 3: //eliminar cuenta
                p.eliminar_usuario(p.getDni(),estado);
                cout << "\nUsuario eliminado con exito";
                sesion_cerrada=true;
                break;
            case 4: //matchear por grupo y estado (donante/receptor)
                p.coincidir(p,estado);
                break;
            case 5: // PANEL DE CONTROL. Solo admins
                if(p.isNivel()){
                    int opcion;
                    do{
                        opcion = menu_panel();
                        switch(opcion){
                            case 1:
                                p.listar_receptores();
                                break;
                            case 2:
                                p.listar_donantes();
                                break;
                            case 3:
                                p.registro(estado,true);
                                cout << "\nUsuario creado con exito.";
                                break;
                            case 4:
                                p.editar_datos(p,true,estado);
                                break;
                            case 5: {
                                Persona p_aux = Persona();
                                p.listar_usuarios();
                                int dni=cuenta_a_eliminar();
                                bool estado_usuario = p.get_grupo(dni, p_aux);
                                p.eliminar_usuario(dni, estado_usuario);
                                break;
                            }
                            case 6: { //backup
                                p.backup();
                                cout << "\nBackup realizado con exito.";
                                cout << "\nArchivos almacenados en: /cmake-build-debug/donates_backup";
                                cout << "\n                        /cmake-build-debug/receptores_backup";
                                break;
                            }
                        }
                    }while(opcion>=1&&opcion<=5);
                }
                break;
        }
        if(sesion_cerrada) seleccion=0;
    }while(seleccion!=0);
    p.elimiar_lista();

    return 0;
}




