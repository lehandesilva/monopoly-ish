#pragma once
#ifndef PENALTY_H
#define PENALTY_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class Penalty : public CSquare {
public:
	Penalty(string name, int type);
	~Penalty();
};

#endif
