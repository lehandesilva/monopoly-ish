//G20924163
//Lehan De Silva
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "CSquare.hpp"
#include "Property.hpp"
#include "Station.hpp"
#include "Player.hpp"
#include "Bonus.hpp"
#include "Penalty.hpp"
#include "Jail.hpp"
#include "GoToJail.hpp"
#include "FreeParking.hpp"
#include "Monopoly.hpp"
using namespace std;
const char POUND = 156;

int Random()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}

int seedFileRead() { //reads the seed text file and returns the value in the text file 
	int seedInt = 0;
	string seedTxt;
	ifstream file("seed.txt");
	while (getline(file, seedTxt)) {
		seedInt = stoi(seedTxt);
	}
	file.close();
	return seedInt;
}
//Called when a player's balance <= 0 
void mortgageProperty(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int& bankRuptPlayerCount) {
	string lowestValuedPropertyName;
	int lowestValuedProperty = 500, value = 0, remainingMoney = 0, propertyNum;
	bool mortgage = true, bankRupt = false;
	if (player[currentPlayer]->getMoney() > 0) //checking if the player has less 0 because there could be an instance that the 										
	{											//mortgage function was called just because the player cant afford that propertry but has above 0
		for (int x = 0; x < 26; x++)
		{
			if (square[x]->getType() == 1 && square[x]->getOwner() == player[currentPlayer]->getName()) {//Iterates thorugh all the property squares 
				value = square[x]->getCost();															//to look for properties owned by the playuer
				if (square[x]->getMortgaged() == false)
				{
					if (x < lowestValuedProperty)//looks for the property with the lowest value
					{
						x = lowestValuedProperty;
						lowestValuedPropertyName = square[x]->getName();//gets name of said property
						propertyNum = x;//sets the element number of square 
						bankRupt = false;//sets bankrupt to false since the player will mortgage the current property
					}
				}
			}
			bankRupt = true;//If a poperty canno be mortgaged, then the player is bankrupt
		}
		if (bankRupt == true)
		{
			player[currentPlayer]->setBankRupt();//sets the player to be bankrupt
			bankRuptPlayerCount++;//increments the number of bankrupt players
		}
		else
		{
			//if not bankrupt, that would mean the player has a mortgagable property and that property is set to be mortgaged
			square[propertyNum]->setMortgage();
			remainingMoney = square[propertyNum]->getCost() + player[currentPlayer]->getMoney();//adds the cost of the property to the player
			player[currentPlayer]->setMoney(remainingMoney);
		}
	}
}


//Fucntion that buys properties
void buyProperty(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int playerPosition, int& bankRuptPlayerCount) {
	int remainingMoney;

	//To check if the player has a positive amount of money
	if (player[currentPlayer]->getMoney() > 0)
	{
		remainingMoney = player[currentPlayer]->getMoney() - square[playerPosition]->getCost(); //the cost of the property is deducted by the player's money
		square[playerPosition]->setOwner(player[currentPlayer]->getName());//the current is set as the owner of the property
		player[currentPlayer]->setMoney(remainingMoney);
		player[currentPlayer]->setPropertyColors(square[playerPosition]->getColor());//the color of the property is pushed to vector that holds all the 
																						//colors of the properties that player owns
		cout << player[currentPlayer]->getName() << " buys " << square[playerPosition]->getName() << " for " << POUND << square[playerPosition]->getCost() << endl;

	}
	else 
	{
		mortgageProperty(player, square, currentPlayer, bankRuptPlayerCount);//if the player cannot buy the property, a mortgage is taken out
	}
}


//To check if the owner owns all properties of the same color
bool colorCheck(unique_ptr <Player> player[4], int currentPlayer, int propertyColor) {
	int ownedPropertiesOfSamecolor = 0;

	//loops through the vector consisting of the colors of all the properties, the player owns
	for (auto x : player[currentPlayer]->getPropertyColors()) {
		if (x == propertyColor)//checks if the property color matches the property color on the square in that iteration
		{
			ownedPropertiesOfSamecolor++;//incremented by one 
		}
	}
	//the number of properties for each color could either be 2 or 3
	if (propertyColor == 0 || propertyColor == 1 || propertyColor == 2 || propertyColor == 4 || propertyColor == 5 || propertyColor == 7 )
	{
		if (ownedPropertiesOfSamecolor == 2) 
		{
			return 1;//if the player owns all the properties of that color, the return value will be 1 and true as its bool
		}
	}
	else if (propertyColor == 3 || propertyColor == 6)
	{
		if (ownedPropertiesOfSamecolor == 3)
		{
			return 1;//if the player owns all the properties of that color, the return value will be 1 and true as its bool
		}
	}
	else 
	{
		return 0;//returns 0 or false if not 
	}
}


//Function to pay rent 
void payRent(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int playerPosition, int& bankRuptPlayerCount) {
	
	int remainingMoney = 0, ownerInt = 0, ownerMoney = 0, rentToPay = 0;

	//gets the name of the owner of the current property
	if (square[playerPosition]->getName() == player[0]->getName()){
		ownerInt = 0;
	}
	else if (square[playerPosition]->getName() == player[1]->getName()) {
		ownerInt = 1;
	}
	else if (square[playerPosition]->getName() == player[2]->getName()) {
		ownerInt = 2;
	}
	else if (square[playerPosition]->getName() == player[3]->getName()) {
		ownerInt = 3;
	}

	//if that property is mortgaged, rent wont be collected 
	if (square[playerPosition]->getMortgaged() == false)
	{
		//checks if all properties are owned by the same player, and if so, rent is doubled
		if (colorCheck(player, currentPlayer, square[playerPosition]->getColor())) {
			rentToPay = square[playerPosition]->getRent() * 2;//rent is set to double of its original 
		}
		else
		{
			rentToPay = square[playerPosition]->getRent();//if not, the normal rent is paid
		}
		remainingMoney = player[currentPlayer]->getMoney() - rentToPay;
		player[currentPlayer]->setMoney(remainingMoney);
		ownerMoney = rentToPay + player[ownerInt]->getMoney();
		player[ownerInt]->setMoney(ownerMoney);
		cout << player[currentPlayer]->getName() << " pays " << POUND << rentToPay << endl;
	}
}

void squareFunction(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int& playerPosition, int& bankRuptPlayerCount) {
	int secondDiceRoll, remainingMoney;
	
	//If the square is off type 1, which means a property 
	if (square[playerPosition]->getType() == 1)
	{
		if (square[playerPosition]->getOwner() == "")//checks if the property has no owner and if not it will buy the property
		{
			buyProperty(player, square, currentPlayer, playerPosition, bankRuptPlayerCount);
		}
		else {//else the player would pay rent if the player doesnt own the property
			if (player[currentPlayer]->getName() != square[playerPosition]->getOwner()) {
				payRent(player, square, currentPlayer, playerPosition, bankRuptPlayerCount);
			}
		}
	}
	//type 3 would be station 
	else if (square[playerPosition]->getType() == 3) 
	{
		if (square[playerPosition]->getOwner() == "")
		{
			buyProperty(player, square, currentPlayer, playerPosition, bankRuptPlayerCount);
		}
		else {
			payRent(player, square, currentPlayer, playerPosition, bankRuptPlayerCount);
		}
	}//type 4 - Bonus
	else if (square[playerPosition]->getType() == 4) 
	{
		secondDiceRoll = Random();
		switch (secondDiceRoll) 
		{
		case 1:
			cout << "Find some money. Gain " << POUND << "20" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 20;
			break;
		case 2:
			cout << "Win a coding competition. Gain " << POUND << "50" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 50;
			break;
		case 3:
			cout << "Receive a rent rebate. Gain " << POUND << "100" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 100;
			break;
		case 4:
			cout << "Win the lottery. Gain " << POUND << "150" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 150;
			break;
		case 5:
			cout << "Receive a bequest. Gain " << POUND << "200" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 200;
			break;
		case 6:
			cout << "It’s your birthday. Gain " << POUND << "300" << endl;
			remainingMoney = player[currentPlayer]->getMoney() + 300;
			break;
		}
		player[currentPlayer]->setMoney(remainingMoney);
	}
	//type 5- penalty
	else if (square[playerPosition]->getType() == 5) 
	{
		secondDiceRoll = Random();
		switch (secondDiceRoll)
		{
		case 1:
			cout << "Buy a coffee in Starbucks. Lose " << POUND << "20" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 20;
			break;
		case 2:
			cout << "Pay your broadband bill. Lose " << POUND << "50" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 50;
			break;
		case 3:
			cout << "Visit the SU shop for food. Lose " << POUND << "100" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 100;
			break;
		case 4:
			cout << "Buy an assignment solution. Lose " << POUND << "150" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 150;
			break;
		case 5:
			cout << "Go for a romantic meal. Lose " << POUND << "200" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 200;
			break;
		case 6:
			cout << "Pay some university fees. Lose " << POUND << "300" << endl;
			remainingMoney = player[currentPlayer]->getMoney() - 300;
			break;
		}
		player[currentPlayer]->setMoney(remainingMoney);
	}
	//type 6 - jail
	else if (square[playerPosition]->getType() == 6) 
	{
		cout << player[currentPlayer]->getName() << " is just visiting " << endl;
	}
	//type 7 - Go To jail
	else if (square[playerPosition]->getType() == 7)
	{
		remainingMoney = player[currentPlayer]->getMoney() - 50;
		player[currentPlayer]->setMoney(remainingMoney);
		playerPosition = 6;
		cout << player[currentPlayer]->getName() << " goes to jail " << endl;
		cout << player[currentPlayer]->getName() << " pays " << POUND << "50" << endl;
	}
	//type 8 - free Parking 
	else if (square[playerPosition]->getType() == 8)
	{
		cout << player[currentPlayer]->getName() << " is resting." << endl;
	}
}
//reads the monopoly file 
void readMonopolyFile(unique_ptr <CSquare> square[26]) {

	vector <string> holder;
	int cost, rent, color, iterationCount = 0, propertyCount = 0, round = 0, squareType;
	string word, myText, squareName, propertyOwner = "";
	bool mortgaged = false;

	ifstream MyReadFile("monopoly.txt");
	while (getline(MyReadFile, myText)) {

		//iterates through each character in a line
		for (auto x : myText) {
															//if a space is detected, it would push the variable that holds the characters to a vector as one element
			if (x == ' ') {
				holder.push_back(word);
				word = "";									//And the variable is set to null
			}
			else {
				word = word + x;							//This would add a character to the variable and would hold a word
			}
		}
		if (!word.empty()) {
			holder.push_back(word);							//if word isnt empty, this would push it to the holder vector and word is set to null 
			word = "";
		}
		if (holder[0] == "1") {
			squareName = holder[1] + " " + holder[2];		//the first element is the type, as the vector consists only of strings, 
			squareType = stoi(holder[0]);					//the variables with numbers are converted to int using stoi() and creates an object witb a unique pointer 
			cost = stoi(holder[3]);
			rent = stoi(holder[4]);
			color = stoi(holder[5]);
			square[iterationCount] = make_unique<Property>(squareName, squareType, cost, rent, color, propertyOwner, mortgaged);
			holder.clear();
			propertyCount++;
		}
		else if (holder[0] == "2") {						//Same thing as above but the type and parameters are different
			squareType = stoi(holder[0]);
			squareName = holder[1];
			square[iterationCount] = make_unique<CSquare>(squareName, squareType);
			holder.clear();
		}
		else if (holder[0] == "3") {
			squareType = stoi(holder[0]);
			squareName = holder[1] + " " + holder[2];
			square[iterationCount] = make_unique<Station>(squareName, squareType, propertyOwner);
			holder.clear();
		}
		else if (holder[0] == "4") {
			squareType = stoi(holder[0]);
			squareName = holder[1];
			square[iterationCount] = make_unique<Bonus>(squareName, squareType);
			holder.clear();
		}
		else if (holder[0] == "5") {
			squareType = stoi(holder[0]);
			squareName = holder[1];
			square[iterationCount] = make_unique<Penalty>(squareName, squareType);
			holder.clear();
		}
		else if (holder[0] == "6") {
			squareType = stoi(holder[0]);
			squareName = holder[1];
			square[iterationCount] = make_unique<Jail>(squareName, squareType);
			holder.clear();
		}
		else if (holder[0] == "7") {
			squareType = stoi(holder[0]);
			squareName = holder[1] + " " + holder[2] + " " + holder[3];
			square[iterationCount] = make_unique<GoToJail>(squareName, squareType);
			holder.clear();
		}
		else if (holder[0] == "8") {
			squareType = stoi(holder[0]);
			squareName = holder[1] + " " + holder[2];
			square[iterationCount] = make_unique<FreeParking>(squareName, squareType);
			holder.clear();
		}
		iterationCount++;									//based in the iteration count, the element number can be used to declare objects
	}
	MyReadFile.close();										//closes file  
}

int main()
{
	{
		int diceRoll = 0, bankRuptPlayerCount = 0, playerMoney, playerPosition, round = 0;
		bool  bankRupt = false, skipTurn = false, passedGo = false;
		unique_ptr <CSquare> square[26]; 
		unique_ptr <Player> player[4];
		player[0] = make_unique<Player>("dog", 1500, 0, bankRupt);
		player[1] = make_unique<Player>("car", 1500, 0, bankRupt);
		player[2] = make_unique<Player>("shoe", 1500, 0, bankRupt);
		player[3] = make_unique<Player>("hat", 1500, 0, bankRupt);

		cout << "Welcome to Monopol-ish" << endl;
		
		readMonopolyFile(square);
		srand(seedFileRead());
		while (round < 20) {
			for (int currentPlayer = 0; currentPlayer < 4; currentPlayer++) {
				//iterates thgrough all four players for one round 
				if (bankRuptPlayerCount == 3)
				{
					//if 3 players are bankrupt, the game ends by breaking out of the loop
					break;
				}
				if (player[currentPlayer]->getBankRupt()) 
				{
					//checks if the current player is bankrupt and if so, the turn is skipped
					skipTurn = true;
				}
				if (skipTurn == false) {
					diceRoll = Random(); //Assigns a value of a dice roll
					cout << player[currentPlayer]->getName() << " rolls " << diceRoll << endl;
					playerPosition = player[currentPlayer]->getPosition() + diceRoll;
					if (playerPosition > 25) {
						//if the player passes the 25th square, the 0th square is called
						playerPosition = playerPosition - 26;
						passedGo = true; //Since the either the player landed on 0 or passed it, the player will collect 200
					}
					if (passedGo == true)
					{
						playerMoney = player[currentPlayer]->getMoney() + 200; //200 is added to the players money
						player[currentPlayer]->setMoney(playerMoney);//sets the moeny value
						cout << player[currentPlayer]->getName() << " passes GO and collects " << POUND << "200" << endl;
						passedGo = false;//passGo is set back to false
					}

					cout << player[currentPlayer]->getName() << " lands on " << square[playerPosition]->getName() << endl;
					squareFunction(player, square, currentPlayer, playerPosition, bankRuptPlayerCount);//calls a fucntion that holds all the outcomes of diffenre square types
					player[currentPlayer]->setPosition(playerPosition);//sets new position
					cout << player[currentPlayer]->getName() << " has " << POUND << player[currentPlayer]->getMoney() << endl;
					cout << endl;
				}
				skipTurn = false;//If the turn was skipped the bool value is set back to false so the next players turn isnt skipped 
			}
			round++;//round is incremented after all 4 players get a chance 
			cout << endl;
		}

		cout << "Game Over" << endl;
		for (int x = 0; x < 4; x++) 
		{
			cout << player[x]->getName() << " has " << POUND << player[x]->getMoney() << endl; //outputs the remainder of all players 
		}

	}
	//function to look for memory leaks
	_CrtDumpMemoryLeaks();
}