#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "DoublyLinkedList.h"
using namespace std;

void theGame(int &numGuess)
{
	numGuess = 0; //resetting to zero for now while i test out why it inserted as 20...
	int guess;
	int randNum = (rand() % 100) + 1;
	do{
		cout << "Guess the number from 1 to 100" << endl;
		cin >> guess;
		numGuess++;
		if (guess > 100 || guess < 0)
		{
			cout << "Remember to make a good guess..." << endl;
		}
		else if (guess > randNum)
		{
			cout << "Too high!!" << endl;
		}
		else if (guess < randNum)
		{
			cout << "Too low!!" << endl;
		}
	} while (guess != randNum);
}
void text(int numGuess)
{
	if (numGuess <= 4 && numGuess > 0) //Not including 0, since that should be impossible
	{
		cout << "Amazing! Or was it luck?" << endl;
	}
	else if (numGuess == 5 || numGuess == 6)
	{
		cout << "That's a very good score..." << endl;
	}
	else if (numGuess == 7 || numGuess == 8)
	{
		cout << "That's pretty good but you can do better..." << endl;
	}
	else if (numGuess == 9 || numGuess == 10)
	{
		cout << "Not too shabby, but not too good either..." << endl;
	}
	else if (numGuess > 10)
	{
		cout << "What a terrible score!..." << endl;
	}
	else
	{
		cout << "Something must've gone wrong... Sorry about that" << endl;
	}

	cout << "It took you " << numGuess << " tries to accurately guess the number!" << endl;
}

void showLeaderboard()
{
	ifstream highscores;
	string line; //Used for getting linefeed.
	int scores = 1; //Initialized to 1 to print out 10 scores.
	highscores.open("highscores.txt");

	cout << "Top 10 High Scores" << endl;
	if (highscores.is_open()) //Goes through top 10 scores
	{
		while (getline(highscores, line) && scores <= 10)
		{
			cout << line << endl;
			scores++;
		}
		cout << endl;
	}
	else
	{

		cout << "There doesn't seem to be a highscores file. Currently building one." << endl;
	}
	highscores.close();
}

int main()
{
	srand(time(NULL)); 	//Seed Generator
	int leaderboardGuess, playerGuess = 0;
	string firstName, lastName, word;
	linkedlist list;
	ifstream leaderboard;
	ofstream leaderboardOut;
	//Introduction && leaderboard
	cout << "Welcome to the number guessing game!" << endl;
	showLeaderboard();
	//Linked List Initializer
	leaderboard.open("highscores.txt");
	//Did an initial input right after opening, since getline starts reading the second
	//line, meaning the first one will be skipped and erased from the file.
	leaderboard >> firstName;
	leaderboard >> lastName;
	leaderboard >> leaderboardGuess;
	list.initialize(firstName, lastName, leaderboardGuess);
	while (getline(leaderboard, word))
	{
		leaderboard >> firstName;
		leaderboard >> lastName;
		leaderboard >> leaderboardGuess;

		list.initialize(firstName, lastName, leaderboardGuess);
	}
	leaderboard.close();
	//HiLo Game
	cout << "What is your name? [First Last] " << endl;
	cin >> firstName >> lastName;
	theGame(playerGuess); 

	text(playerGuess);
	//Insert The Score Into Leaderboard
	list.insertNode(firstName, lastName, playerGuess);
	leaderboardOut.open("highscores.txt");
	list.save(leaderboardOut);
	leaderboardOut.close();
	//Top 10
	if (list.checkTop10(playerGuess) == true)
	{
		cout << "Congratulations, you made it to the top 10!" << endl;
	}

	return 0;
}