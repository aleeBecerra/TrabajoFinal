#pragma once
#include "Employee.h"

class Driver : public Employee
{

private:
	string driverLicense, model;
	
public:
	Driver(string username, string email, string password, string driverLicense, string model) 
		: Employee(username, email, password, "Driver"), driverLicense(driverLicense), model(model) {}
	~Driver(){}
    void setName(string _name) {
        username = _name;
    }
    void setDriverLicense(string _driverLicense) {
        driverLicense = _driverLicense;
    }

    void setModel(string _model) {
        model = _model;
    }

    //getters
    string getName() {
        return username;
    }
  
    string getDriverLicense() {
        return driverLicense;
    }
    string getModel() {
        return model;
    }

    void showAdditionalInfo() override {
        cout << "Licencia de conducir: " << driverLicense << endl;
        cout << "Modelo de auto: " << model << endl;
    }



};

