#pragma once
#include <iostream>
using namespace std;

class Route
{
private:
	string origin, destination;
	double distance;

public:
	Route(string origin, string destination, double distance) : origin(origin), destination(destination),
		distance(distance){}

	//setters
	void setOrigin(string _origin) {
		origin = _origin;
	}

	void setDestination(string _destination) {
		destination = _destination;
	}

	void setDistance(double _distance) {
		distance = _distance;
	}

	//getters

	string getOrigin() {
		return origin;
	}

	string getDestination() {
		return destination;
	}

	double getDistance() {
		return distance;
	}


	~Route(){}



};


