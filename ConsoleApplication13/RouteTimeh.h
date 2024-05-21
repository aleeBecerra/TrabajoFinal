#pragma once

class RouteTime
{
public:
	//retorna el tiempo en minutos
	double calculateTime(double distance) {
		return (distance / 50.0) * 60;
	}
};


