/*
	The game logic (no view code or direct user interaction)
	The game is a simple guess the word game based Mastermind
*/

#pragma once
#include  <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bults = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {

public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrenTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

	// Please try and ignore this and focus on the interface above
private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};