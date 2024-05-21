#pragma once
#include <iostream>
using namespace std;

class VehicleType
{
public:
	string determineVehicleType(double totalWeight) {
		if (totalWeight <= 5) {
			return "moto";
		}
		else if (totalWeight <= 40) {
			return "auto";
		}
		else if (totalWeight <= 100) {
			return "camion";
		}
		else {
			return "Nuestro servicio no cuenta con el equipo necesario para hacer ese trabajo...";
		}
	}
};

