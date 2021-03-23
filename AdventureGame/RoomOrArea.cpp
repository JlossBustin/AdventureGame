#include "pch.h"
#include "RoomOrArea.h"


RoomOrArea::RoomOrArea()
{
	description = "";
	
}
RoomOrArea::RoomOrArea(string pDescription)
{
	description = pDescription;

}
void RoomOrArea::displayDescription()
{
	cout << description << endl;
}
void RoomOrArea::displayOptions()
{
	for (int i = 0; i < options.size(); i++)
	{
		cout << options[i] << endl;
	}
}
void RoomOrArea::addOptions(string pOptions)
{
	options.push_back(pOptions);
}
void RoomOrArea::setConnections(vector<int> pConnections)
{
	connections = pConnections;
}

void RoomOrArea::setDescription(string pDescription)
{
	description = pDescription;
}

string RoomOrArea::getDescription()
{
	return description;
}

void RoomOrArea::addConnection(int pConnection)
{
	connections.push_back(pConnection);
}

int RoomOrArea::getConnection(int pSelection) 
{
	return connections[pSelection-1];
}