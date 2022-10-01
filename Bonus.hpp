#pragma once
#ifndef BONUS_H
#define BONUS_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class Bonus : public CSquare {
public:
	Bonus(string name, int type);
	~Bonus();
};

#endif