#pragma once
#include "User.h"

class Customer : public User
{

protected:
	string customerType;

public:
	Customer(string username, string email, string password, string customerType) : User(username,email,password, "Customer"), 
		customerType(customerType){}
	~Customer(){}

	string getCustomerType() {
		return this->customerType;
	}

	



};



