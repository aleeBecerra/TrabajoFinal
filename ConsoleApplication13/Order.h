#pragma once
#include "List.h"
#include "Product.h"
#include "Route.h"
#include "Shipping.h"
using namespace dby;
using namespace std;


class Order
{
private:
	List<Product*>* productsList = new List<Product*>;
	Route* route;
	int orderID;


public:
	Order(List<Product*>* productsList, Route* route, int orderID) : productsList(productsList), route(route), orderID(orderID) {}

	double getDistance() {
		return route->getDistance();
	}

	double getTotalAmount() {
		Shipping shipping; 
		return shipping.calculateShippingPrice(getTotalWeight(), getDistance());
	}

	double getTotalWeight() {

		double totalWeight = 0.0;
		for (int i = 0; i < productsList->size(); i++) {
			totalWeight += productsList->at(i)->getWeight();
		}
		return totalWeight;
	}

	void showProducts() {


		cout << "   Producto/s en 'ORDEN " << orderID + 1 << "': " << endl;
		for (int i = 0; i < productsList->size(); i++) {
			if (productsList->at(i)->getOrderID() == orderID) {
				cout << "   " << "[" << productsList->at(i)->getId() << "]" << " " << productsList->at(i)->getNameProduct() << endl;
			}
		}
		cout << endl;

	}

	List<Product*>* getProductsList() {
		return productsList;
	}

	Route* getRoute() {
		return route;
	}

	~Order() {}
};




