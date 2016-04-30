#pragma once

#include "FBullCowGame.h"
#include <map>

#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7},{5,10}, {6,16}, {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrenTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

void FBullCowGame::Reset()
{
	const FString HIIDEN_WORD = "plane"; // this MUS be a isogram
	MyHiddenWord = HIIDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID  guess. increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WorldLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 MHWCharacter = 0; MHWCharacter < WorldLength; MHWCharacter++) {
		// copare letters against the guess
		for (int32 GChar = 0; GChar < WorldLength; GChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWCharacter]) { // if they match then			
				if (MHWCharacter == GChar) {  // if they're in the same place				 
					BullCowCount.Bults++; // incriments bulls				
				}
				else {
					BullCowCount.Cows++;   // incriment cows
				}
			}
		}
	}

	if (BullCowCount.Bults == WorldLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) {
		return true;
	}

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word) {

		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // for all letters of the word
			return false;  // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {

		if (!islower(Letter)) {
			return false;
		}
	}

	return true;
}
