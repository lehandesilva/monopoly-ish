#pragma once
#ifndef FREEPARKING_H
#define FREEPARKING_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class FreeParking : public CSquare {
public:
	FreeParking(string name, int type);
	~FreeParking();
};

#endif