#include <iostream>
#include "Player.hpp"
#include "CSquare.hpp"
using namespace std;


Player::Player(string name, int money, int pos, bool bankRupt) {
		Name = name;
		Money = money;												//constructor for player
		Pos = pos;
		BankRupt = bankRupt;
	}

	string Player::getName() {
		return Name;												//to get name of player
	}

	int Player::getPosition() {
		return Pos;
	}

	void Player::setPosition(int pos) {								//to set position
		this->Pos = pos;
	}

	int Player::getMoney() {
		return Money;
	}

	void Player::setMoney(int money) {								//to set money
		this->Money = money;
	}

	void Player::setPropertyColors(int propertyColor) {				//pushback colors 
		ownedPropertyColors.push_back(propertyColor);
	}

	vector <int> Player::getPropertyColors() {						//get vector of colors
		return ownedPropertyColors;
	}

	void Player::setBankRupt() {
		BankRupt = true;											//set the player bankrupt
	}

	bool Player::getBankRupt() {									//get a bool value returned based on players balance
		return BankRupt;
	}
	Player::~Player() {}