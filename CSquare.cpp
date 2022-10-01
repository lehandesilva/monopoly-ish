#include <iostream>
#include "CSquare.hpp"
using namespace std;

CSquare::CSquare(string name, int type) {
	Name = name;
	Type = type;								
}

string CSquare::getName() {						
	return Name;
}

int CSquare::getType() {						
	return Type;
}

string CSquare:: getOwner() {					
	return "";
}

void CSquare::setOwner(string Owner) {}				

int CSquare::getCost() {
	return 0;
}

int CSquare::getRent() {
	return 0;
}

int CSquare::getColor() {
	return 0;
}

bool CSquare::getMortgaged() {
	return 0;
}

void CSquare::setMortgage() {}

void CSquare::removeMortgage() {}

CSquare::~CSquare() {}