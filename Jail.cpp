#include <iostream>
#include "Jail.hpp"
#include "CSquare.hpp"
using namespace std;

Jail::Jail(string name, int type) : CSquare(name, type) {
	Name = name;
	Type = type;
}
Jail::~Jail() {}