#pragma once
#ifndef JAIL_H
#define JAIL_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class Jail : public CSquare {
public:
	Jail(string name, int type);
	~Jail();
};
#endif
