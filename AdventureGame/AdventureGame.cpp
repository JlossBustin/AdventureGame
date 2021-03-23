// FinalPrep.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <fstream>
#include <iostream>
#include "Player.h"
#include "RoomOrArea.h"

using namespace std;

class Game
{
private:
	vector<RoomOrArea> areas;	//A vector of areas in the game
	const int NUM_AREAS = 7;	//My sample story only have 7 areas
	const int START_ROOM = 0;	//The position in the vector where they player starts
	Player thePlayer;			//The player of the game
	bool endOfGame;
public:
	/********************************************************************
	CreatePlayer():  Prompt the user for information about the player and 
	then create a Player object called thePlayer
	*********************************************************************/
	void CreatePlayer()
	{
		cout << "Enter your name:" << endl;
		string userName;
		getline(cin, userName);
		thePlayer.setName(userName);
		thePlayer.setCurrentLocation(0); //Set the default location to the start
		thePlayer.setIsAlive(true); //Set the player to be alive
		cin.ignore(256, '\n');
	}
	/******************************************************************
		CreateAreaChoices(): Reads the choices for each area in the story
		and adds them to the area object's vector of options
	********************************************************************/
	void CreateAreaChoices()
	{
		ifstream choicesFile;
		choicesFile.open("Choices.txt");
		string lineOfText;
		string currentChoices;
		vector<string> areaOptions;
		for (int i = 0; i < NUM_AREAS; i++)
		{
			getline(choicesFile, lineOfText);

			while (lineOfText != "" && !choicesFile.eof())
			{
				currentChoices = currentChoices + lineOfText + "\n";
				getline(choicesFile, lineOfText);
			}
			areas[i].addOptions(currentChoices);
			currentChoices = "";


		}


	}

	void CreateAreaConnections()
	{
		ifstream locationsFile;
		locationsFile.open("Connections.txt");
		string lineOfText;
		string locationsString;

		for (int i = 0; i < NUM_AREAS; i++)
		{
			getline(locationsFile, lineOfText);

			while (lineOfText != "" && !locationsFile.eof())
			{
				//This is a little different because we need to store
				//integers in the Room locations vector.  These represent the
				//"exits" from each room
				areas[i].addConnection(stoi(lineOfText));
				getline(locationsFile, lineOfText);
				
			}
	
		}

		locationsFile.close();
	}

	/*****************************************************************************
	CreateAreaDescriptions(): Reads the descripotions for each area in the story
	and adds them to the area object's description attribute
	******************************************************************************/
	void CreateAreaDescriptions()
	{
		ifstream storyFile;
		storyFile.open("story.txt");
		string lineOfText;
		string currentStory;

		for (int i = 0; i < NUM_AREAS; i++)
		{
			getline(storyFile, lineOfText);
			while (lineOfText != "" && !storyFile.eof())
			{
				currentStory = currentStory + lineOfText + "\n";
				getline(storyFile, lineOfText);
			}
			areas.push_back(RoomOrArea(currentStory));

			currentStory = "";
		}
		
		storyFile.close();

	}


	int displayMenu()
	{
		int userChoice = -1;
		cout << areas[thePlayer.getCurrentLocation].getDescription() << endl;
		vector<string> choices = areas[thePlayer.getCurrentLocation].getChoices();
		for (int i = 0; i < choices.size(); i++)
		{
			cout << choices[i];
			if (choices[i] == "THE END")
			{
				endOfGame = true;
			}
			else
			{
				cout << "Please choose one of the options:";
				cin >> userChoice;
			}
		}
		return userChoice;
	}

	


	void GameLoop()
	{
		while (!endOfGame && thePlayer.getIsAlive())
		{
			int retUserChoice = displayMenu();
			if (retUserChoice == -1)
			{
				endOfGame == true;
			}
			else
			{

			}
		}
	}
};

	

int main()
{
	Game prep;
	prep.CreateAreaDescriptions();
	prep.CreateAreaChoices();
	prep.CreateAreaConnections();
	prep.CreatePlayer();
	return 0;
}

