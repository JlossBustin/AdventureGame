#include "pch.h"
#include <fstream>
#include <iostream>
#include "Player.h"
#include "RoomOrArea.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Author: DJ Granda, Jason Phox, Justin Bloss
//Project: Text-Based Adventure
//Purpose: This project is meant to be a rudimentary introduction to C++, students will grasp the concepts of vectors, inputting and outputting
//		   information, and using multiple functions and method calls.
//Functionality: The project will prompt the user for their name, store their name in a string variable and begin a text-based adventure. The 
//user has full control over what paths they want to take through the inputting of integer values, which are read in through the program and
//direct the player to different rooms. This leads to completely different opportunities for play-throughs.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Game
{
private:
	vector<RoomOrArea> areas;
	const int NUM_AREAS = 91;
	const int START_ROOM = 0;
	Player thePlayer;
	bool endOfGame = false;
public:
	void CreatePlayer()
	{
		// asks user for name
		cout << "Please enter your name: ";
		string userName;
		// stores name entered into userName string var
		getline(cin, userName);
		thePlayer.setName(userName); //Set the player's name
		thePlayer.setCurrentLocation(START_ROOM); //set the player location to the start room (0)
		thePlayer.setIsAlive(true); // sets the alive value to true

	}

	// creates the area choices for the player that coincides with the area they are currently in
	void CreateAreaChoices() 
	{
		// new isntance of an ifstream
		ifstream choicesFile;
		// choicesFile opens choices text file
		choicesFile.open("Choices.txt");
		// new string var meant to store the text from choicesFile
		string lineOfText;
		// for loop
		for (int i = 0; i < NUM_AREAS; i++) {
			// stores text in choicesFile into lineOfText and displays it
			getline(choicesFile, lineOfText);

			// while loop that goes until lineOfText is equal to a blank space and if choicesFile is at the end of file
			while (lineOfText != "" && !choicesFile.eof()) 
			{
				// adds the options in area of i to the line of text
				areas[i].addOptions(lineOfText);
				// gets the next line of text from lineOfText
				getline(choicesFile, lineOfText);
			}
		}
	}

	// creates the connections for the room the player is currently in
	void CreateAreaConnections()
	{
		// declares a new instance of an ifstream named connectionsFile
		ifstream connectionsFile;
		// connectionsFile opens the connections text file and reads from it
		connectionsFile.open("Connections.txt");
		// new string var
		string lineOfText;
		
		// for loop that checks if i is less than the total amount of rooms in the game
		for (int i = 0; i < NUM_AREAS; i++) {
			// gets the next line of text from connectionsFile and stores it in lineOfText var
			getline(connectionsFile, lineOfText);
			// while loop that checks if lineOfText is not equal to an empty space and if connectionsFile is not at the end of file 
			while (lineOfText != "" && !connectionsFile.eof()) 
			{
				// the connections for the area the player is currently in are converted from string to int
				areas[i].addConnection(stoi(lineOfText));
				// gets the next line from connectionsFile and stores it in lineOfText
				getline(connectionsFile, lineOfText);
			}
		}
	}

	// creates the area description that the player is currently located in
	void CreateAreaDescriptions()
	{
		ifstream storyFile; //stream reader to read the story
		storyFile.open("story.txt"); // reads from the story text file
		string lineOfText; // declares a string var
		string currentStory; 

		// for loop that reads the area description in
		for (int i = 0; i < NUM_AREAS; i++)
		{
			getline(storyFile, lineOfText);
			// while loop with conditions of if storyfile is not at the end of file and the next line of text is not equal to a space
			while (!storyFile.eof() && lineOfText != "")
			{
				currentStory = currentStory + lineOfText + "\n";
				getline(storyFile, lineOfText);
			}
			areas.push_back(RoomOrArea(currentStory));
			currentStory = "";
		}
		// close storyfile when out of for loop
		storyFile.close();
	}

	// displays the user menu
	int displayMenu() 
	{
		// declares an int var and sets it to -1
		int userSelection = -1;
		// displays the description of the current area
		areas[thePlayer.getCurrentLocation()].displayDescription();
		// if not the end of the game
		if (!endOfGame) {
			// displays the options for the current location
			areas[thePlayer.getCurrentLocation()].displayOptions();
			// outputs a string with the player name included
			cout << thePlayer.getName() << ", please make a selection: ";
			// stores userselection
			cin >> userSelection;

			// while loop to make sure the user selection is nothing out of range or anything but a integer
			while (!cin || userSelection <= 0 || userSelection > areas[thePlayer.getCurrentLocation()].getConnectionSize()) 
			{
				// reprints the options and tells the user they need to enter a correct input
				areas[thePlayer.getCurrentLocation()].displayOptions();
				cout << "You stupid idiot. Enter a valid value. " << thePlayer.getName() << ", please make a selection.";
				// clears value stored in cin
				cin.clear();
				cin.ignore(256, '\n');
				cin >> userSelection;
			}
		}
		// returns user selection
		return userSelection;
	}

	// creates a game loop using a while loop with conditions if not end of game and if the player is alive currently
	void GameLoop() {
		while (!endOfGame && thePlayer.getIsAlive()) 
		{
			// the int returned from displaymenu is stored in retUserSelection
			int retUserSelection = displayMenu();
			// sets up the connection between pages based upon the value in retUserSelection
			thePlayer.setCurrentLocation(areas[thePlayer.getCurrentLocation()].getConnection(retUserSelection));
		}
	}
};

// main method of the program that calls other functions
int main()
{
		// instantiating a new game var
		Game theGame;
		// calling createPlayer function
		theGame.CreatePlayer();
		// creates the current area description of the player
		theGame.CreateAreaDescriptions();
		// creates the area choices for the specific room the player is in
		theGame.CreateAreaChoices();
		// creates the area connections for the specific room the player is in
		theGame.CreateAreaConnections();
		// calls the game loop function that loops the game until the player wins or dies
		theGame.GameLoop();
}