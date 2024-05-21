
#pragma once

class Shipping
{
public:
	double calculateShippingPrice(double totalWeight, double distance) {
		return (totalWeight * 5) + 10 + distance;
	}
};


