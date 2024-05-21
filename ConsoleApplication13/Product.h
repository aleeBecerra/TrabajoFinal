#pragma once
#include <iostream>
using namespace std;


class Product
{
private:
	string nameProduct;
	float width, height, weight, value;
	int id;

public:
	Product(string nameP, float width, float height, float weight, float value, int id) : nameProduct(nameP), width(width), height(height), weight(weight),
		value(value), id(id){}
	~Product(){}

	//setters
	void setNameProduct(string _nameProduct) { this->nameProduct = _nameProduct; }
	void setID(int _id) { this->id = _id; }
	void setWidth(float _width) { this->width = _width; }
	void setHeight(float _height) { this->height = _height; }
	void setWeight(float _weight) { this->weight = _weight; }
	void setValue(float _value) { this->value = _value; }

	//getters
	string getNameProduct() { return nameProduct; }
	int getId() { return id; }
	float getWidth() { return width; }
	float getHeight() { return height; }
	float getWeight() { return weight; }
	float getValue() { return value; }

	//metodos de servicio
	void showProductInfo() {
		cout << "== Detalle del producto ==" << endl;
		cout << "Nombre del producto: " << nameProduct << endl;
		cout << "ID del producto: " << id << endl;
		cout << "Ancho del producto: " << width << endl;
		cout << "Altura del producto: " << height << endl;
		cout << "Peso del producto: " << weight << endl;
		cout << "Valor del producto: " << value << endl;
	}
};


