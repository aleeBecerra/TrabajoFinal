#include <iostream>
#include <conio.h>
#include <map>
#include <algorithm>
#include <vector>
#include "string"
#include "List.h"
#include "Person.h"
#include "Company.h"
#include "Driver.h"
#include "Ticket.h"

using namespace dby;
using namespace std;

List<Order*>* ordersList = new List<Order*>;
List<Ticket*>* ticketsList = new List<Ticket*>;
List<Product*>* productsList = new List<Product*>;

List<User*>* usersList = new List<User*>;
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
void executeMenuForCustomers(int option, int idCustomer, int& integer) {

    string origin, destination;
    string vehicleType;
    double distance;
    int n;
    string nameProduct;
    float width, height, weight, value;

    Ticket* ticket = nullptr;
    Order* order = nullptr;
    Route* route = nullptr;


    switch (option) {
    case 1:
        integer++;
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

            productsList->push_back(new Product(nameProduct, width, height, weight, value, i + 1, integer));
            _getch();

        }
        order = new Order(productsList, route, integer);
        ordersList->push_back(order);

        ticket = new Ticket(order, usersList->at(idCustomer)->getName(), integer);
        ticketsList->push_back(ticket);

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
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;
    case 2:
        system("cls");
        cout << "Mostrando boletas..." << endl;

        if (ordersList->empty()) {
            cout << "No hay boletas para mostrar." << endl;
        }
        else {
            for (int i = 0; i < ordersList->size(); ++i) {
                //Order* order = ordersList->at(i);
                //ticket = new Ticket(order, usersList->at(idCustomer)->getName(), i + 1);
                //cout << "Boleta " << i + 1 << ":" << endl;
                //ticket->printTicket();
                //delete ticket; // Liberar memoria después de usar el objeto Ticket
                cout << "Boleta " << ticketsList->at(i)->getOrderID() << ": " << endl;
                ticketsList->at(i)->printTicket();
                cout << endl;

            }
        }

        cout << "Presione cualquier tecla para volver al menú..." << endl;
        _getch();
        system("cls");
        executeMenuForCustomers(showMenuForCustomers(), idCustomer, integer);
        break;

    case 5:
        cout << "Cerrando sesíon..." << endl;
        return;

    }

}

//ORDENAMIENTO

void showOrdersMenu() {
    cout << "Seleccione el criterio de ordenamiento:" << endl;
    cout << "1. Ordenar por monto" << endl;
    cout << "2. Ordenar por kilometros" << endl;
    cout << "3. Sin ordenamiento" << endl;
}
bool compareByAmount(Order* a, Order* b) {
    return a->getTotalAmount() < b->getTotalAmount();
}

bool compareByDistance(Order* a, Order* b) {
    return a->getRoute()->getDistance() < b->getRoute()->getDistance();
}
void sortOrdersByAmount(List<Order*>* ordersList) {
    vector<Order*> orderVector;
    for (int i = 0; i < ordersList->size(); ++i) {
        orderVector.push_back(ordersList->at(i));
    }
    sort(orderVector.begin(), orderVector.end(), compareByAmount);
    for (int i = 0; i < orderVector.size(); ++i) {
        ordersList->at(i) = orderVector[i];
    }
}
void sortOrdersByDistance(List<Order*>* ordersList) {
    vector<Order*> orderVector;
    for (int i = 0; i < ordersList->size(); ++i) {
        orderVector.push_back(ordersList->at(i));
    }
    sort(orderVector.begin(), orderVector.end(), compareByDistance);
    for (int i = 0; i < orderVector.size(); ++i) {
        ordersList->at(i) = orderVector[i];
    }
}


void executeMenuForEmployees(int option) {
    switch (option) {
    case 1:
        // Mostrar lista de pedidos pendientes y permitir al empleado seleccionar un pedido
        if (ordersList->empty()) {
            cout << "No hay pedidos pendientes." << endl;
        }
        else {
            // Mostrar lista de opciones de ordenamiento
            showOrdersMenu();
            int orderBy;
            cin >> orderBy;

            // Aplicar el ordenamiento según la opción seleccionada
            switch (orderBy) {
            case 1:
                sortOrdersByAmount(ordersList);
                break;
            case 2:
                sortOrdersByDistance(ordersList);
                break;
            case 3:
                
                break;
            default:
                cout << "Opción no válida." << endl;
                return;
            }

            // Mostrar los datos de los pedidos ordenados
            cout << "Lista de pedidos pendientes:" << endl;
            for (int i = 0; i < ordersList->size(); ++i) {
                Order* order = ordersList->at(i);
                cout << i + 1 << ". Pedido desde " << ordersList->at(i)->getRoute()->getOrigin()
                    << " hasta " << ordersList->at(i)->getRoute()->getDestination() << endl;
                cout << "   Monto total: S/." << order->getTotalAmount() << endl;
                cout << "   Distancia: " << order->getDistance() << " km" << endl;
            }

            // Permitir al conductor seleccionar un pedido
            cout << "Seleccione el número de pedido que desea realizar: ";
            int selectedOrderIndex;
            cin >> selectedOrderIndex;
            selectedOrderIndex--; // Ajustar a índice basado en 0

            // Validar la entrada del usuario
            if (selectedOrderIndex < 0 || selectedOrderIndex >= ordersList->size()) {
                cout << "Número de pedido no válido." << endl;
                return;
            }
            else {
                cout << "Orden en curso...";
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
    int optionForCustomers=0, optionForEmployees=0;
    int integer = -1; //ID: TICKET, ORDER, PRODUCT

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
                    executeMenuForCustomers(optionForCustomers, i, integer);
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

