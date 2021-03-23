#pragma once

#include <string>
#include <iostream>
#include <vector>
using namespace std;
/*******************************************************************************
	Class:  RoomOrArea -- Text adventure for a room.  Contains a description
	options and connecting rooms or areas
********************************************************************************/
class RoomOrArea
{
public:
	RoomOrArea();								//Default Constructor
	RoomOrArea(string pDescription);			//Overloaded Constructor to take a Description
	void displayDescription();					//Display the description of the room
	void displayOptions();						//Display the list of options for the room
	void addOptions(string pOptions);	//Sets a vector of options
	void setConnections(vector<int>connections);//Sets a vector of connections
	void setDescription(string pDescription);
	string getDescription();					//Get the description for the room
	void addConnection(int pConnection);  //Read a connection from the Connections.txt
	int getConnection(int pSelection);	//gets the connection from the selection made
	int getConnectionSize() { return connections.size(); };
private:
	string description;			//Description of the room
	vector<string> options;		//A vector of options for each room
	vector<int> connections;	//A vector for the connections to other rooms	
};