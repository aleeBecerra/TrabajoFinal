#pragma once
#include <iostream>
using namespace std;


class User

{
protected:
	string username;
	string email;
	string password;
	string userType;

public:
	User(string name, string email, string password, string userType): username(name), email(email),password(password), userType(userType) {}
	~User(){}

    void setName(string _name) {
        username = _name;
    }
    void setEmail(string _email) {
        email = _email;
    }
    void setPassword(string _password) {
        password = _password;
    }

    void setUserType(string _userType) {
        userType = _userType;
    }

    //getters
    string getName() {
        return username;
    }

    string getEmail() {
        return email;
    }

    string getPassword() {
        return password;
    }
    string getUserType() {
        return userType;
    }


    //MOSTRAR INFORMACION USER
    virtual void showAdditionalInfo() = 0;



};

