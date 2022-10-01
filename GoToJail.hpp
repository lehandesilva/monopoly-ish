#pragma once
#ifndef GOTOJAIL_H
#define GOTOJAIL_H
#include <iostream>
#include <string>
#include "CSquare.hpp"
using namespace std;

class GoToJail : public CSquare {
public:
	GoToJail(string name, int type);
	~GoToJail();
};

#endif