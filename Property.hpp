#pragma once
#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class Property : public CSquare {
private:

	int Cost;
	int Rent;
	int Color;
	string Owner;
	bool Mortgaged;

public:
	Property(string name, int type, int cost, int rent, int color, string ownerOfProperty, bool mortgaged);

	void setOwner(string owner);

	string getOwner();

	int getCost();

	int getRent();

	int getColor();

	bool getMortgaged();

	void setMortgage();

	void removeMortgage();

	~Property();
};
#endif