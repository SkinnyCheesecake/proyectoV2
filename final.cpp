
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>

using namespace std;

class Menu {
private:
    string nombre, telefono, domicilio, codigo, fechapago;

public:
    void menuPrincipal();
    void capturarClientes();
    void mostrarClientes();
    void modificarClientes();
    void detalleClientes();
    void eliminarCliente();
    void validarCodigo(string &codigo);
};

void pausa() {
    cout << "\n\nPresiona ENTER para continuar..." << endl;
    cin.ignore();
    system("cls");
}

void error() {
    cout << "No se pudo abrir el archivo. Asegurate de que el archivo 'clientes.txt' existe en el directorio del programa.";
}

void Menu::validarCodigo(string &codigo) {
    while (codigo.empty()) {
        cout << "Codigo no valido, intentelo de nuevo: ";
        getline(cin, codigo);
    }
}

void Menu::menuPrincipal() {
    int opcion;
    do {
        cout << "---- REGISTRO DE CLIENTES PARA UNA ESCUELA DE NATACION ----" << endl;
        cout << "[1] Registrar cliente [2] Mostrar todos los clientes";
        cout << "[3] Consultar cliente [4] Modificar cliente [5] Eliminar cliente [6] Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada.
        system("cls");

        switch (opcion) {
            case 1: capturarClientes(); break;
            case 2: mostrarClientes(); break;
            case 3: detalleClientes(); break;
            case 4: modificarClientes(); break;
            case 5: eliminarCliente(); break;
            case 6: cout << "Saliendo del programa..."; break;
            default: cout << "Opcion no valida, intentelo nuevamente."; break;
        }
    } while (opcion != 6);
}

void Menu::capturarClientes() {
    ofstream archivo("clientes.txt", ios::app);
    if (!archivo.is_open()) {
        error();
        return;
    }

    cout << "---- REGISTRAR CLIENTE ----" << endl;
    cout << "Ingrese el codigo del cliente: ";
    getline(cin, codigo);
    validarCodigo(codigo);

    cout << "Ingrese el nombre del cliente: ";
    getline(cin, nombre);
    cout << "Ingrese el domicilio del cliente: ";
    getline(cin, domicilio);
    cout << "Ingrese el telefono del cliente: ";
    getline(cin, telefono);
    cout << "Ingrese la fecha de pago (DD/MM/AAAA): ";
    getline(cin, fechapago);

    archivo << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;
    archivo.close();
    cout << "Cliente registrado exitosamente.";
    pausa();
}

void Menu::mostrarClientes() {
    ifstream archivo("clientes.txt");
    if (!archivo.is_open()) {
        error();
        return;
    }

    cout << "---- LISTA DE CLIENTES ----" << endl;
    int count = 0;
    while (getline(archivo, codigo) && getline(archivo, nombre) &&
           getline(archivo, domicilio) && getline(archivo, telefono) &&
           getline(archivo, fechapago)) {
        cout << "Codigo: " << codigo << endl << "Nombre: " << nombre << endl << "Domicilio: " << domicilio << endl
             << "Telefono: " << telefono << endl << "Fecha de pago: " << fechapago << endl << "" << endl;
        count++;
    }

    if (count == 0) {
        cout << "No hay clientes registrados.";
    } else {
        cout << "Total de clientes registrados: " << count << "";
    }

    archivo.close();
    pausa();
}

void Menu::detalleClientes() {
    ifstream archivo("clientes.txt");
    if (!archivo.is_open()) {
        error();
        return;
    }

    cout << "---- CONSULTAR CLIENTE ----" << endl;
    cout << "Ingrese el codigo del cliente: ";
    string codigoConsulta;
    cin.ignore();
    getline(cin, codigoConsulta);

    bool encontrado = false;
    while (getline(archivo, codigo) && getline(archivo, nombre) &&
           getline(archivo, domicilio) && getline(archivo, telefono) &&
           getline(archivo, fechapago)) {
        if (codigo == codigoConsulta) {
            cout << "Registro encontrado:" << endl;
            cout << "Codigo: " << codigo << endl << "Nombre: " << nombre << endl << "Domicilio: " << domicilio << endl
             << "Telefono: " << telefono << endl << "Fecha de pago: " << fechapago << "";
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontro ningun cliente con el codigo: " << codigoConsulta << "";
    }

    archivo.close();
    pausa();
}

void Menu::modificarClientes() {
    ifstream archivo("clientes.txt");
    ofstream archivoTemp("temp.txt");
    if (!archivo.is_open() || !archivoTemp.is_open()) {
        error();
        return;
    }

    cout << "---- MODIFICAR CLIENTE ----" << endl;
    cout << "Ingrese el codigo del cliente: ";
    string codigoConsulta;
    cin.ignore();
    getline(cin, codigoConsulta);

    bool encontrado = false;
    while (getline(archivo, codigo) && getline(archivo, nombre) &&
           getline(archivo, domicilio) && getline(archivo, telefono) &&
           getline(archivo, fechapago)) {
        if (codigo == codigoConsulta) {
            cout << "Registro encontrado:";
            cout << "Codigo: " << codigo << endl << "Nombre: " << nombre << endl << "Domicilio: " << domicilio << endl
             << "Telefono: " << telefono << endl << "Fecha de pago: " << fechapago << endl << "";
            cout << "\nIngrese los nuevos datos:" << endl;

            cout << "Nuevo codigo: ";
            getline(cin, codigo);
            validarCodigo(codigo);

            cout << "Nuevo nombre: ";
            getline(cin, nombre);
            cout << "Nuevo domicilio: ";
            getline(cin, domicilio);
            cout << "Nuevo telefono: ";
            getline(cin, telefono);
            cout << "Nueva fecha de pago: ";
            getline(cin, fechapago);

            encontrado = true;
        }
        archivoTemp << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;
    }

    archivo.close();
    archivoTemp.close();

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (encontrado) {
        cout << "Cliente modificado exitosamente.";
    } else {
        cout << "No se encontro ningun cliente con el codigo: " << codigoConsulta << "";
    }

    pausa();
}

void Menu::eliminarCliente() {
    ifstream archivo("clientes.txt");
    ofstream archivoTemp("temp.txt");
    if (!archivo.is_open() || !archivoTemp.is_open()) {
        error();
        return;
    }

    cout << "---- ELIMINAR CLIENTE ----" << endl;
    cout << "Ingrese el codigo del cliente: ";
    string codigoConsulta;
    cin.ignore();
    getline(cin, codigoConsulta);

    bool encontrado = false;
    while (getline(archivo, codigo) && getline(archivo, nombre) &&
           getline(archivo, domicilio) && getline(archivo, telefono) &&
           getline(archivo, fechapago)) {
        if (codigo == codigoConsulta) {
            cout << "Registro eliminado:" << endl;
            cout << "Codigo: " << codigo << endl << "Nombre: " << nombre << endl << "Domicilio: " << domicilio << endl
             << "Telefono: " << telefono << endl << "Fecha de pago: " << fechapago << endl << "" << endl;
            encontrado = true;
        } else {
            archivoTemp << codigo << endl << nombre << endl << domicilio << endl << telefono << endl << fechapago << endl;
        }
    }

    archivo.close();
    archivoTemp.close();

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    if (!encontrado) {
        cout << "No se encontro ningun cliente con el codigo: " << codigoConsulta << "";
    }

    pausa();
}

int main() {
    Menu menu;
    menu.menuPrincipal();
    return 0;
}
