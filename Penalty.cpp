#include <iostream>
#include "Penalty.hpp"
#include "CSquare.hpp"
using namespace std;

Penalty::Penalty(string name, int type) : CSquare(name, type) {
	Name = name;
	Type = type;
}
Penalty::~Penalty() {}