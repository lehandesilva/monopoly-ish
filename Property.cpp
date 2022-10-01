#include <iostream>
#include "Property.hpp"
#include "CSquare.hpp"
using namespace std;

Property::Property(string name, int type, int cost, int rent, int color, string ownerOfProperty, bool mortgaged) : CSquare(name, type) {
	Cost = cost;
	Rent = rent;
	Color = color;									//constructor
	Owner = ownerOfProperty;
	Mortgaged = mortgaged;
}

void Property::setOwner(string owner) {				//to set the owner
	Owner = owner;
}

string Property::getOwner() {						//get the owner
	return Owner;
}

int Property::getCost() {							//get the cost
	return Cost;
}

int Property::getRent() {							//get the rent
	return Rent;
}

int Property::getColor() {							//get the color
	return Color;
}

bool Property::getMortgaged() {						//get the mortgaged
	return Mortgaged;
}

void Property::setMortgage() {						//set mortgage
	Mortgaged = true;
}

void Property::removeMortgage() {					//remove mortgage 
	Mortgaged = false;
}

Property::~Property() {}							//destructor