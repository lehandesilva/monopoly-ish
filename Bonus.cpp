#include <iostream>
#include "Bonus.hpp"
#include "CSquare.hpp"
using namespace std;

Bonus::Bonus(string name, int type) : CSquare(name, type) {
	Name = name;
	Type = type;
}
Bonus::~Bonus() {}