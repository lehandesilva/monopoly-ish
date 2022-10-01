#pragma once
#ifndef MONOPOLY_H
#define MONOPOLY_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

int Random();

int seedFileRead();

void mortgageProperty(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int& bankRuptPlayerCount);

void buyProperty(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int playerPosition, int& bankRuptPlayerCount);

bool colorCheck(unique_ptr <Player> player[4], int currentPlayer, int propertyColor);

void payRent(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int playerPosition, int& bankRuptPlayerCount);

void squareFunction(unique_ptr <Player> player[4], unique_ptr <CSquare> square[26], int currentPlayer, int& playerPosition, int& bankRuptPlayerCount);

void readMonopolyFile(unique_ptr <CSquare> square[26]);

#endif