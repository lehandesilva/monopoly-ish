#include <iostream>
#include "FreeParking.hpp"
#include "CSquare.hpp"
using namespace std;

FreeParking::FreeParking(string name, int type) : CSquare(name, type) {
	Name = name;
	Type = type;
}
FreeParking::~FreeParking() {}