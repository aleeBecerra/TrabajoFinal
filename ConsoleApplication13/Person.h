#pragma once
#include "Customer.h"

class Person : public Customer
{


private:
	string dni;

public:
	Person(string username, string email, string password, string dni) : Customer(username, email, password, "Person"), dni(dni) {}

	~Person(){}
    //setters
    void setDni(string _dni) {
        dni = _dni;
    }

    //getters
    string getDni() {
        return dni;
    }

    void showAdditionalInfo() override {
        cout << "DNI: " << dni << endl;
    }


};


