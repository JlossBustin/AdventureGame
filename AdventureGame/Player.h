#pragma once
#include <string>
using namespace std;
class Player
{
public:
	Player();
	Player(string pName);
	void setName(string pName);
	string getName() { return name; };
	void setCurrentLocation(int pCurrentLocation);
	int getCurrentLocation();
	bool getIsAlive() {return isAlive;};				//Inline
	void setIsAlive(bool pAlive) { isAlive = pAlive; }; //Inline function
private:
	string name;
	int currentLocation;
	bool isAlive;
};	