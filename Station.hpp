#pragma once
#ifndef STATION_H
#define STATION_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class Station : public CSquare {

private:
	string Owner;
	int Cost = 200;
	int Rent = 10;

public:
	Station(string name, int type, string owner);

	string getOwner();

	void setOwner(string owner);

	int getRent();

	int getCost();
	
	~Station();
};

#endif