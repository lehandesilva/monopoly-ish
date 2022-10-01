#include <iostream>
#include "GoToJail.hpp"
#include "CSquare.hpp"
using namespace std;

GoToJail::GoToJail(string name, int type) : CSquare(name, type) {
	Name = name;
	Type = type;
}
GoToJail::~GoToJail() {}