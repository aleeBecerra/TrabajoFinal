#pragma once
#include "User.h"

class Employee : public User
{

protected:
	string employeeType;

public:
	Employee(string username, string email, string password, string employeeType) : User(username, email, password, "Employee"),
		employeeType(employeeType) {}
	~Employee(){}

	string getCustomerType() {
		return this->employeeType;
	}

};


