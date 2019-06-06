//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Kuldeep on 5/15/19.
//  Copyright © 2019 KuldeepCompany. All rights reserved.
//

#pragma once

#include "FBullCowGame.hpp"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (uint32_t) MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };
    return WordLengthToMaxTries[(uint32_t) MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
    const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (Guess.length() == 0) {
        return EGuessStatus::ZeroLength;
    }
    else if (IsWhiteSpace(Guess)) {
        return EGuessStatus::WhiteSpace;
    }
    else if (!IsAlphabet(Guess)) {
        return EGuessStatus::Not_Alphabet;
    }
    else if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;

    FBullCowCount BullCowCount;
    int32 WordLength = (uint32_t) MyHiddenWord.length(); // assuming same length as guess

    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        for (int32 GChar = 0; GChar < WordLength; GChar++)
        {
            if (Guess[GChar] == MyHiddenWord[MHWChar]) {
                if (MHWChar == GChar) {
                    BullCowCount.Bulls++;
                }
                else {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    
    if (BullCowCount.Bulls == WordLength) {
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    if (Word.length() <= 1) { return true; }

    TMap<char, bool> LetterSeen;
    
    for (auto Letter : Word)
    {
        Letter = tolower(Letter);
        if (LetterSeen[Letter]) {
            return false;
        }
        else {
            LetterSeen[Letter] = true;
        }
    }
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
    for (auto Letter:Word)
    {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}

bool FBullCowGame::IsWhiteSpace(FString Word) const
{
    for (auto Letter:Word)
    {
        if (isspace(Letter)) {
            return true;
        }
    }
    return false;
}

bool FBullCowGame::IsAlphabet(FString Word) const
{
    for (auto Letter:Word)
    {
        if (!isalpha(Letter)) {
            return false;
        }
    }
    return true;
}
