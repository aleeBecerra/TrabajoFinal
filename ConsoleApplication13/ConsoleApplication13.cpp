#include <iostream>
#include <conio.h>
#include <map>
#include "string"
#include "List.h"
#include "Person.h"
#include "Company.h"
#include "Driver.h"
#include "Ticket.h"

using namespace dby;
using namespace std;

List<User*>* usersList = new List<User*>;
List<Order*>* ordersList = new List<Order*>;
List<Product*>* productsList = new List<Product*>;
List<Person*>* personsList = new List<Person*>;
List<Company*>* companiesList = new List<Company*>;
List<Driver*>* driversList = new List<Driver*>;
//Listas para cada tipo de vehiculo
List<Driver*>* driversMoto = new List<Driver*>;
List<Driver*>* driversAuto = new List<Driver*>;
List<Driver*>* driversCamion = new List<Driver*>;

//Mapa que asociará los pedidos con conductores
map<Order*, Driver*> orderDriverMap;

//MOSTRAR LISTA DE CONDUCTORES
void showDriversList(List<Driver*>* driversList, Order* order) {
    Ticket* ticket = nullptr;
    cout << "Seleccione un conductor de la siguiente lista:" << endl;
    for (int i = 0; i < driversList->size(); i++) {
        cout << i + 1 << ". " << driversList->at(i)->getName() << endl;
    }
    int selectedDriverIndex;
    cin >> selectedDriverIndex;
    selectedDriverIndex--;  // ajustar a índice basado en 0

    Driver* selectedDriver = driversList->at(selectedDriverIndex);
    orderDriverMap[order] = selectedDriver;

    cout << "Conductor " << selectedDriver->getName() << " asignado al pedido." << endl;

}

//MOSTRAR MENÚ PARA CUSTOMER Y DRIVER
int showMenuForCustomers() {
    cout << "==================== MENU DE CLIENTES ==================" << endl << endl;
    cout << "1. Hacer pedido" << endl;
    cout << "2. Mostrar boletas" << endl;
    cout << "3. Ver estado de mi pedido" << endl;
    cout << "4. Modificar pedido" << endl;
    cout << "5. Cerrar sesión" << endl;
    int option;
    do
    {
        cin >> option;
        if (option < 1 || option>5)
            cout << "Ingrese una opcion valida... ";
    } while (option < 1 || option>5);

    return option;
}

int showMenuForEmployees() {
    cout << "=====================MENU DE EMPLEADOS==================" << endl << endl;
    cout << "1. Mostrar lista pedidos (seleccionar pedido a realizar)" << endl;
    cout << "2. Cerrar sesion" << endl;
    int option;
    do
    {
        cin >> option;
        if (option < 1 || option>2)
            cout << "Ingrese una opcion valida... ";
    } while (option < 1 || option>2);

    return option;
}

//EJECTUTAR MENU PARA CUSTOMER Y DRIVER
void executeMenuForCustomers(int option, int idCustomer) {

    string origin, destination;
    string vehicleType;
    double distance;
    int n;

    string nameProduct;
    float width, height, weight, value;
    int id;
    int integer = 0;

    Ticket* ticket = nullptr;
    Order* order = nullptr;
    Route* route = nullptr;

    switch (option) {
    case 1:
        id = 0;
        system("cls");
        cout << "Pedido " << integer + 1 << ": " << endl; 
        
        cout << "Ingresa el lugar de recojo: ";
        cin >> origin;
        cout << "Ingresa el lugar de entrega: ";
        cin >> destination;
        cout << "Ingresa la distancia entre el punto de origen y el destino en km: ";
        cin >> distance;
       
         route = new Route(origin, destination, distance);

        cout << "Ingresa la cantidad de productos a transportar: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            id = i + 1;
            cout << "Ingresa el nombre del producto " << i + 1 << ": ";
            cin >> nameProduct;
            cout << "Ingresa la altura del producto " << i + 1 << " en centimetros: ";
            cin >> height;
            cout << "Ingresa el ancho del producto " << i + 1 << " en centimetros: ";
            cin >> width;
            cout << "Ingresa el peso del producto " << i + 1 << " en kilogramos: ";
            cin >> weight;
            cout << "Ingresa el valor (S/.) del producto " << i + 1 << " en soles: S/.";
            cin >> value;
            cout << "Producto registrado exitosamente!" << endl;
            cout << "Presiona cualquier tecla para continuar..." << endl;

            productsList->push_back(new Product(nameProduct, width, height, weight, value, i + 1));
            _getch();
            
        }
        order = new Order(productsList, route);
        ordersList->push_back(order);
        ticket = new Ticket(order, usersList->at(idCustomer)->getName(), integer + 1);
        integer++;

        system("cls");
        ticket->printTicket();
        cout << "Presione cualquier tecla para ver los conductores disponibles para su pedido..." << endl;
        _getch();

        vehicleType = VehicleType().determineVehicleType(order->getTotalWeight());
      
        if (vehicleType == "moto" && !driversMoto->empty()) {
            cout << "Lista de conductores de moto:" << endl;
            showDriversList(driversMoto, order);
        }
        else if (vehicleType == "auto" && !driversAuto->empty()) {
            cout << "Lista de conductores de auto:" << endl;
            showDriversList(driversAuto, order);
        }
        else if (vehicleType == "camion" && !driversCamion->empty()) {
            cout << "Lista de conductores de camión:" << endl;
            showDriversList(driversCamion, order);
        }


        if (driversMoto->empty() && driversAuto->empty() && driversCamion->empty()) {
            cout << "Por el momento no hay conductores disponibles." << endl;
        }

        cout << "Presione cualquier tecla para volver al menú..." << endl;
        _getch();

        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer);
        break;
    case 2:
        system("cls");
        cout << "Mostrando boletas..." << endl;

        if (ordersList->empty()) {
            cout << "No hay boletas para mostrar." << endl;
        }
        else {
            for (int i = 0; i < ordersList->size(); ++i) {
                Order* order = ordersList->at(i);
                ticket = new Ticket(order, usersList->at(idCustomer)->getName(), i + 1);
                cout << "Boleta " << i + 1 << ":" << endl;
                ticket->printTicket();
                delete ticket; // Liberar memoria después de usar el objeto Ticket
            }
        }

        cout << "Presione cualquier tecla para volver al menú..." << endl;
        _getch();
        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer);
        break;

    default:
        cout << "Opcion no valida." << endl;
        break;
    }
}

void executeMenuForEmployees(int option) {
    switch (option) {
    case 1:
        // Mostrar lista de pedidos pendientes y permitir al empleado seleccionar un pedido
        if (ordersList->size() == 0) {
            cout << "No hay pedidos pendientes." << endl;
        }
        else {
            cout << "Lista de pedidos pendientes:" << endl;
            for (int i = 0; i < ordersList->size(); ++i) {
                cout << i + 1 << ". Pedido desde " << ordersList->at(i)->getRoute()->getOrigin()
                    << " hasta " << ordersList->at(i)->getRoute()->getDestination() << endl;
            }
            cout << "Seleccione el número de pedido que desea realizar: ";
            int selectedOrderIndex;
            cin >> selectedOrderIndex;
            selectedOrderIndex--; // Ajustar a índice basado en 0

            // Validar la entrada del usuario
            if (selectedOrderIndex < 0 || selectedOrderIndex >= ordersList->size()) {
                cout << "Número de pedido no válido." << endl;
            }
            else {
                // Asignar conductor al pedido seleccionado
                Order* selectedOrder = ordersList->at(selectedOrderIndex);
                string vehicleType = VehicleType().determineVehicleType(selectedOrder->getTotalWeight());

                Driver* selectedDriver = nullptr;
                if (vehicleType == "moto" && !driversMoto->empty()) {
                    selectedDriver = driversMoto->at(0); // Seleccionar el primer conductor de la lista de motos
                }
                else if (vehicleType == "auto" && !driversAuto->empty()) {
                    selectedDriver = driversAuto->at(0); // Seleccionar el primer conductor de la lista de autos
                }
                else if (vehicleType == "camion" && !driversCamion->empty()) {
                    selectedDriver = driversCamion->at(0); // Seleccionar el primer conductor de la lista de camiones
                }
                else {
                    cout << "No hay conductores disponibles para este tipo de vehículo." << endl;
                }

                if (selectedDriver) {
                    orderDriverMap[selectedOrder] = selectedDriver;
                    cout << "Conductor " << selectedDriver->getName() << " asignado al pedido." << endl;
                }
            }
        }
        break;

    case 2:
        cout << "Cerrando sesión..." << endl;
        break;

    }
}



//REGISTRAR USUARIO

void registerUser() {

    string username, email, password;
    string dni;
    string ruc;
    string licenseNumber, vehicleType;


 //USUARIO (USER):
    system("cls");
    cout << "Ingrese:" << endl;
    cout << "1. Customer -> Si desea usar nuestro servicio" << endl;
    cout << "2. Employee -> Si desea trabajar para nosotros" << endl;
    cout << " --- --- --- --- --- --- --- --- --- --- --- ---" << endl;
    int userType;
    do {
        cin >> userType;
        if (userType < 1 || userType>2) cout << "Ingrese opcion valida... ";
    } while (userType < 1 || userType > 2);
    cout << endl;

        //CLIENTE (CUSTOMER):
    if (userType == 1) {



        cout << "Ingrese: " << endl;
        cout << "1. Person -> Si es persona" << endl;
        cout << "2. Company -> Si es compania/empresa" << endl;
        cout << " --- --- --- --- --- --- --- --- --- ---" << endl;

        int customerType;

        do {
            cin >> customerType;
            if (customerType < 1 || customerType>2) cout << "Ingrese opcion valida... ";
        } while (customerType < 1 || customerType > 2);
        switch (customerType) {

                       //PERSONA (PERSON):
        case 1:


            system("cls");
            cout << "REGISTRANDO CLIENTE PERSONA..." << endl;
            cout << "Ingresa tu nombre y apellido: ";
            cin.ignore();
            getline(cin, username);
            cout << "Ingresa tu correo electronico: ";
            cin >> email;
            cout << "Crea tu contrasenia: ";
            cin >> password;
            cout << "Ingrese tu numero de DNI: ";
            cin >> dni;

            usersList->push_back(new Person(username, email, password, dni));
            break;

                       //COMPAÑIA/EMPRESA (COMPANY):
        case 2:


            system("cls");
            cout << "REGISTRANDO CLIENTE EMPRESA..." << endl;
            cout << "Ingresa el nombre de tu empresa: ";
            cin.ignore();
            getline(cin, username);
            cout << "Ingresa tu correo electronico: ";
            cin >> email;
            cout << "Crea tu contrasenia: ";
            cin >> password;
            cout << "Ingrese tu numero de RUC: ";
            cin >> ruc;

            usersList->push_back(new Company(username, email, password, ruc));
            break;

        }

    }
        //EMPLEADO (EMPLOYEE):
    
                        //CONDUCTOR (DRIVER):
    else if (userType == 2) {
        system("cls");
        cout << "REGISTRANDO EMPLEADO CONDUCTOR..." << endl;
        cout << "Ingresa tu nombre y apellido: ";
        cin.ignore();
        getline(cin, username);
        cout << "Ingresa tu correo electronico: ";
        cin >> email;
        cout << "Crea tu contrasenia: ";
        cin >> password;
        cout << "Ingrese tu numero de licencia de conducir: ";
        cin >> licenseNumber;
        cout << "Ingrese el tipo de tu vehiculo: ";
        cin >> vehicleType;
        //VALIDANDO TIPO DE VEHÍCULO
        while (vehicleType != "moto" && vehicleType != "auto" && vehicleType != "camion") {
            cout << "Tipo de vehiculo no valido. Ingrese 'moto', 'auto' o 'camion': ";
            cin >> vehicleType;
        }
        Driver* driver = new Driver(username, email, password, licenseNumber, vehicleType);
        driversList->push_back(driver);
        usersList->push_back(driver);

        if (vehicleType == "moto") {
            driversMoto->push_back(driver);
        }
        else if (vehicleType == "auto") {
            driversAuto->push_back(driver);
        }
        else if (vehicleType == "camion") {
            driversCamion->push_back(driver);
        }
    
    }
    cout << "\nUuario registrado exitosamente..." << endl;
    cout << "Presione cualquier tecla para volver al menu..." << endl;
    _getch();
}

//MOSTRAR ORDENES PENDIENTES PARA DRIVER
void showPendingOrders(Driver* driver) {
    cout << "Pedidos pendientes para el conductor " << driver->getName() << ":" << endl;
    bool hasPendingOrders = false;

    for (const auto& pair : orderDriverMap) {
        if (pair.second == driver) {
            Order* order = pair.first;
            // Aquí mostramos detalles del pedido
            Route* route = order->getRoute();
            cout << "Pedido desde " << route->getOrigin() << " hasta " << route->getDestination() << endl;
            cout << "Distancia: " << route->getDistance() << " km" << endl;
            cout << "Productos: " << endl;
            for (int i = 0; i < order->getProductsList()->size(); i++) {
                Product* product = order->getProductsList()->at(i);
                cout << "  - " << product->getNameProduct() << " (" << product->getWeight() << " kg)" << endl;
            }
            hasPendingOrders = true;
        }
    }

    if (!hasPendingOrders) {
        cout << "No hay pedidos pendientes." << endl;
    }
    cout << "Presione cualquier tecla para volver al menu..." << endl;
    _getch();
}

//INICIAR SESIÓN
void LogIn() {

    string email, password;
    bool correctPassword = false;
    bool accountFound = false;
    int optionForCustomers, optionForEmployees;
    system("cls");
    cout << "Ingresa tu correo electronico: ";
    cin >> email;

    for (int i = 0; i < usersList->size(); i++) {
        if (email == usersList->at(i)->getEmail()) {
            accountFound = true;
            cout << "Cuenta encontrada!\n";
            cout << "Ingresa tu contrasenia: ";
            cin >> password;
            if (password == usersList->at(i)->getPassword()) {
                correctPassword = true;
                system("cls");
                cout << "Bienvenido de vuelta " << usersList->at(i)->getName() << endl << endl;
                if (usersList->at(i)->getUserType() == "Customer") {
                    optionForCustomers = showMenuForCustomers();
                    executeMenuForCustomers(optionForCustomers, i);
                }
                 if (usersList->at(i)->getUserType() == "Employee") {
                    Employee* employee = dynamic_cast<Employee*>(usersList->at(i));
                    Driver* driver = dynamic_cast<Driver*>(employee);
                    optionForEmployees = showMenuForEmployees();
                    executeMenuForEmployees(optionForEmployees);
                    if (driver) {
                        showPendingOrders(driver);
                    }

                 }
                break;
            }
        }

    }

    if (!accountFound) cout << "No hay ninguna cuenta registrada con este correo electronico..." << endl;



}

//MOSTRAR MENÚ PRINCIPAL
int showMenu() {


    cout << "          _    _ _           _     ___" << std::endl;
    cout << "         | |  | | |         | |   |_  |" << std::endl;
    cout << "         | |  | | |__   __ _| |_    | | ___  _   _ _ __ _ __   ___ _   _" << std::endl;
    cout << "         | |\\/| | '_ \\ / _` | __|   | |/ _ \\| | | | '__| '_ \\ / _ \\ | | |" << std::endl;
    cout << "         \\  /\\  / | | | (_| | |_/\\__/ / (_) | |_| | |  | | | |  __/ |_| |" << std::endl;
    cout << "          \\/  \\/|_| |_|\\__,_|\\__|\\____/\\___/ \\__,_|_|  |_| |_|\\___|\\__, |" << std::endl;

    cout << "  |'''''||'''''||'''''||'''''||'''''||'''''||'''''||'''''||'''''||'__/  |'''''|| '''''| " << endl;
    cout << "  '-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-0-0-''-|___/ -0-0-''`-0-0-'" << endl;

    cout << " ------------------------------------------------------------" << endl;
    cout << "|                                                            |" << endl;
    cout << " ------------------------------------------------------------" << endl;
    cout << "|   1   |           Registrar usuario                        |" << endl;
    cout << " ------------------------------------------------------------" << endl;
    cout << "|   2   |           Iniciar sesion                           |" << endl;
    cout << " ------------------------------------------------------------" << endl;
    cout << "|   3   |           Mostrar usuarios                         |" << endl;
    cout << " ------------------------------------------------------------" << endl;
    cout << "|   4   |           Salir                                    |" << endl;
    cout << " ------------------------------------------------------------" << endl;

    int opcion;
    do
    {
        cin >> opcion;
        if (opcion < 1 || opcion>4)
            cout << "Ingrese una opcion valida... ";
    } while (opcion < 1 || opcion>4);

    return opcion;
}

int main()
{
    int option = 1;
    

    while (option != 4) {
        system("cls");
        option = showMenu();

        switch (option) {
        case 1:
            registerUser();
            break;

        case 2:
            LogIn();
            break;

        case 3:
            system("cls");

            if (usersList->size() == 0) { cout << "Aun no se ha registro ningun usuario..." << endl; }
            else {
                for (int i = 0; i < usersList->size(); i++) {
                    cout << "Usuario " << i + 1 << ": " << usersList->at(i)->getUserType() << endl;


                }
            }
            cout << "hhh";
            _getch();
            break;
        }
        
       
    }

    
}

