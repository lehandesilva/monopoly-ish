#include <iostream>
#include "Station.hpp"
#include "CSquare.hpp"
using namespace std;

Station::Station(string name, int type, string owner) : CSquare(name, type) {
	Name = name;
	Type = type;
	Owner = owner;
}

string Station::getOwner() {
	return Owner;
}

void Station::setOwner(string owner) {
	Owner = owner;
}

int Station::getRent() {
	return Rent;
}

int Station::getCost() {
	return Cost;
}

Station::~Station() {}