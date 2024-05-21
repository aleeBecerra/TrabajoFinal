#pragma once
#include "Order.h"
#include "Shipping.h"
#include "VehicleType.h"
#include "RouteTimeh.h"

class Ticket
{
private:
	Order* order;
	Shipping shipping;
	VehicleType vehicleType;
	RouteTime routeTime;
	string customerName;
	int id;

public:
	Ticket(Order* order, string customerName, int id) : order(order), customerName(customerName), id(id) {}

	void printTicket() {
		double totalWeight = order->getTotalWeight();
		double distance = order->getDistance();

		double shippingCost = shipping.calculateShippingPrice(totalWeight, distance);
		string vehicle = vehicleType.determineVehicleType(totalWeight);
		double travelTime = routeTime.calculateTime(distance);

		cout << "============================ Detalles de la boleta ==========================" << endl;
		cout << "   Nombre del propietario: " << customerName << endl;
		order->showProducts();
		cout << "   ID de la boleta: " << id << endl;
		cout << "   Vehiculo asignado: " << vehicle << endl;
		cout << "   Precio total: " << shippingCost << endl;
		cout << "   Tiempo estimado de demora (minutos): " << travelTime << endl;
		cout << " -----------------------------------------------------------------------------" << endl;
	}

	
	~Ticket(){}
};


