#pragma once
#ifndef CSQUARE_H
#define CSQUARE_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class CSquare {

protected:
	string Name;
	int Type;

public:

	CSquare(string name, int type);

	string getName();

	int getType();

	virtual string getOwner();

	virtual void setOwner(string Owner);

	virtual int getCost();

	virtual int getRent();

	virtual int getColor();

	virtual bool getMortgaged();

	virtual void setMortgage();

	virtual void removeMortgage();

	virtual ~CSquare();

};
#endif