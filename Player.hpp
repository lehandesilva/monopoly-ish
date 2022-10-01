#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include "CSquare.hpp"
using namespace std;

typedef vector <int> ownedPropertyColors;

class Player {
private:
	string Name;
	int Money;
	int Pos;
	ownedPropertyColors ownedPropertyColors;
	bool BankRupt;

public:

	Player(string name, int money, int pos, bool bankRupt);

	string getName();

	int getPosition();

	void setPosition(int pos);

	int getMoney();

	void setMoney(int money);

	void setPropertyColors(int propertyColor);

	vector <int> getPropertyColors();

	void setBankRupt();

	bool getBankRupt();
	~Player();
};

#endif
