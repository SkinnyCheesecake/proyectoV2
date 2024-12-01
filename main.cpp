#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class menu{

    private:
        string nombre;
        string telefono;
        string domicilio;
        string codigo;
        string fechapago;
        string fregistro;


    public:
        void capturarClientes();
        void mostrarClientes(string nuevocodigo);
        void modificarClientes();
        void detalleClientes();
        void eliminarCliente(); 
        void loopCodigo(string *secondCode);
};

void pausa();
void error();

void menu::loopCodigo(string *secondCode){
    string negro;

    *secondCode = negro;

    if(negro == ""){
        do{
            cout << "Codigo no valido, intentelo de nuevo" << endl;
            cout << ">> ";
            getline(cin, codigo);
        }while(negro == "");
    }
}

void menu::capturarClientes(){

    ofstream capturar;
    ifstream verificador;
    string nuevo_codigo;

    bool coincidencia = false;
    verificador.open("clientes.txt", ios::in);
    capturar.open("clientes.txt", ios::app);

    if(capturar.is_open() && verificador.is_open()){
        cout << "** CAPTURAR UN CLIENTE **\n\n" << endl;
        fflush(stdin);
        cout << "Ingresa un codigo para el cliente: >>";
        getline(cin, nuevo_codigo);
        
        loopCodigo(&nuevo_codigo);

        do{
            verificador.seekg(0);
            getline(verificador, codigo);
            while(!verificador.eof()){

                getline(verificador, nombre);
                getline(verificador, telefono);
                getline(verificador, domicilio);
                getline(verificador, fechapago);

                if(codigo == nuevo_codigo){
                    coincidencia = true;
                    cout << "\nYa existe un cliente con ese codigo" << endl;
                    cout << "El cliente con ese codigo es " << nombre << "\n" << endl;
                    cout << "Ingresa un codigo valido: ";

                    getline(cin, nuevo_codigo);

                    loopCodigo(&nuevo_codigo);
                    break;
                }
            getline(verificador, codigo);
            }

            if(verificador.eof() && nuevo_codigo != codigo) coincidencia = false;
        }

        while(coincidencia == true);
        system("cls");

        codigo = nuevo_codigo;
            cout << "**REGISTRAR A UN CLIENTE**\nIngresa el codigo del cliente: ";
            cout << "Ingresa el codigo del cliente";
            cout << codigo << "\n" << endl;
            fflush(stdin);
            cout << "Ingresa el nombre del cliente: ";
            getline(cin, nombre);
            cout << endl;
            cout << "Ingresa el domicilio del cliente: ";
            getline(cin, domicilio);
            cout << endl;
            cout << "Ingresa el numero de telefono del cliente: ";
            getline(cin, telefono);
            cout << endl;
            cout << "Ingresa el fecha de inscripcion del cliente (MM/DD/YYYY): ";
            getline(cin, fechapago);
            cout << endl;
            
            capturar << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;

            cout << "El registro se ha completado de forma correcta!" << endl;
        
    }

    else{
        error();
    }

    capturar.close();
    verificador.close();
    pausa();
}

void menu::eliminarCliente(){
    ifstream lectura;
    ofstream auxiliar;

    bool encontrado = false;
    string codigoauxiliar;
    char respuesta[5];
    lectura.open("clientes.txt", ios::in);
    auxiliar.open("auxiliar.txt", ios::out);

    cout << "**Dar de baja a un cliente**" << endl;
    if(lectura.is_open() && auxiliar.is_open()){
        fflush(stdin);
        cout << "Ingresa el codigo del cliente que se dará de baja: ";
        getline(cin, codigoauxiliar);
        getline(lectura, codigo);
        while(!lectura.eof()){
            getline(lectura, nombre);
            getline(lectura, domicilio);
            getline(lectura, telefono);
            getline(lectura, fechapago);
               
            if(codigoauxiliar == codigo){
                encontrado = true;
                cout << "\n\nRegistro encontrado\n" << endl;
                cout << "Codigo: " << codigo << endl;
                cout << "Nombre: " << nombre << endl;
                cout << "Domicilio: " << domicilio << endl;
                cout << "Telefono: " << codigo << endl;
                cout << "Fecha de inscripcion: " << fechapago << endl;
                cout << "Realmente quieres dar de baja a " << nombre << " (s/n)?: ";

                cin.getline(respuesta, 5);

                if(strcmp(respuesta, "s") == 0 || strcmp(respuesta, "S") == 0 || strcmp(respuesta, "si") == 0 || strcmp(respuesta, "SI") == 0){
                    cout << "\nEl cliente se ha dado de baja de forma correcta :(";
                }

                else{
                    cout << "\nCliente conservado" << endl;
                    auxiliar << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;
                }
            }
            else{
                auxiliar << endl << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;
            }
            getline(lectura, codigo);
        }

        if(encontrado == false){
            cout << "\nNo se encontro el codigo: " << codigoauxiliar << endl;
        }
    }
    else{
        error();
    }
    lectura.close();
    auxiliar.close();
    remove("clientes.txt");
    rename("auxiliar.txt", "clientes.txt");
    pausa();
}

void menu::detalleClientes(){
    string codigoauxiliar;
    ifstream mostrar;
    bool encontrado = true;
    mostrar.open("clientes.txt", ios::in);
    if(mostrar.is_open()){
        fflush(stdin);
        cout << "**CONSULTAR DETALLES DE UN CLIENTE**" << endl;
        cout << "Ingresa el codigo del cliente del que deseas consultar detalles: ";
        getline(cin, codigoauxiliar);
        getline(mostrar, codigo);
        while(!mostrar.eof()){
            getline(mostrar, nombre);
            getline(mostrar, domicilio);
            getline(mostrar, telefono);
            getline(mostrar, fechapago);

            if(codigoauxiliar == codigo){
                encontrado = true;
                cout << "\nRegistro encontrado" << endl;
                cout << "Codigo: " << codigo << endl << "Domicilio: " << domicilio << endl << "Telefono: " << telefono << endl << "Fecha de inscripcion: " << fechapago << endl;
                }
            
            getline(mostrar, codigo);
        }

        if(encontrado == false){
            cout << "\nNo se encontró el registro del codigo: " << codigoauxiliar << endl;
        }
    }

    else{
        error();
    }

    mostrar.close();
    pausa();
}

void menu::modificarClientes(){
    ifstream lectura;
    ifstream verificador;
    ofstream auxiliar;
    string codigoauxiliar;
    string nuevocodigo;
    string nombreauxiliar;
    string domicilioauxiliar;
    string telefonoauxiliar;
    string fechauxiliar;
    bool encontrado = false;
    bool coincidencia = false;
    bool copia = false;
    lectura.open("clientes.txt", ios::in);
    verificador.open("clientes.txt", ios::in);
    auxiliar.open("auxiliar.txt", ios::out);
    cout << "**\nModificar los datos de un cliente\n**" << endl;
    if(lectura.is_open() && verificador.is_open() && auxiliar.is_open()){
        fflush(stdin);
        cout << "Ingresa el codigo del cliente que desea modificar";
        getline(cin, codigoauxiliar);

        loopCodigo(&codigoauxiliar);

        nuevocodigo == codigoauxiliar;   

        getline(lectura, codigo);
        while(!lectura.eof()){
            getline(lectura, nombre);
            getline(lectura, domicilio);
            getline(lectura, telefono);
            getline(lectura, fechapago);

            if(codigoauxiliar == codigo){
                encontrado = true;
                mostrarClientes(nuevocodigo);

                cout << "************************";
                cout << "\n" << endl;
                cout << "Ingresa la nueva informacion para el cliente\n";
                fflush(stdin);
                cout << "Ingresa el codigo del cliente: ";
                getline(cin, codigoauxiliar);

                if(codigoauxiliar == nuevocodigo){
                    copia = true;
                }      
                if(copia == false){
                    do{
                        if(codigoauxiliar == nuevocodigo){
                            coincidencia = false;
                            break;
                        }
                        verificador.seekg(0);
                        getline(verificador, codigo);
                        while(!verificador.eof()){
                            getline(verificador, nombre);
                            getline(verificador, domicilio);
                            getline(verificador, telefono);
                            getline(verificador, fechapago);

                            if(codigoauxiliar == codigo){
                                coincidencia = true;
                                cout << "\nYa existe un cliente con ese codigo\n" << endl << "Ingresa un codigo valido" << endl;
                                getline(cin, codigoauxiliar);
                            }
                            while(codigoauxiliar == "");
                        }
                        break;
                    }
                    getline(verificador, codigo);
                }
                if(verificador.eof() && codigoauxiliar != codigo){
                    coincidencia = false;
                }
            }
            while(coincidencia = true);
        } 

        }
    }