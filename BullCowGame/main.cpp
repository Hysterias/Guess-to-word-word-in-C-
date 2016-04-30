#pragma once 

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GuetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;  // instantiate a new game, which we re-use across plays

// the entry point for our application
int main() {
	std::cout << BCGame.GetCurrenTry();

	bool bPlayAgain = false;

	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);


	return 0;
}

void PrintIntro()
{

	std::cout << "\n\nHello to  Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of? \n";
	std::cout << std::endl;
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// lopp asking for guess while the game
	// is NOT won and tthere are still tries remaing
	while (!BCGame.IsGameWon() && BCGame.GetCurrenTry() <= MaxTries) {
		FText Guess = GuetValidGuess();

		// submit vald guess to the game AND RECIEVE COUNT
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bults;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

FText GuetValidGuess() {
	FText Guess = "";
	EGuessStatus  Status = EGuessStatus::Invalid_Status;

	do {
		// get a guess form the player
		int32 CurrentTry = BCGame.GetCurrenTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter you guess: ";

		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n'";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word witout repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);

	return Guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "WLL DONE - YOU WIN!!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
}
