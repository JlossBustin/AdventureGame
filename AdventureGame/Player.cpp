#include "pch.h"
#include "Player.h"

Player::Player()
{
	name = "";
	currentLocation = 0;
}
Player::Player(string pName)
{
	name = pName;
	currentLocation = 0;
}
void Player::setName(string pName)
{
	name = pName;
}
void Player::setCurrentLocation(int pCurrentLocation)
{
	currentLocation = pCurrentLocation;
}
int Player::getCurrentLocation()
{
	return currentLocation;
}