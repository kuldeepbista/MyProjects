//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Kuldeep on 5/15/19.
//  Copyright © 2019 KuldeepCompany. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>

#endif /* FBullCowGame_hpp */

/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on MasterMind
 */

#pragma once
#include <string>
// do not put namespace on header file

// to make the syntax Unreal friendly
using FString = std::string;
using int32 = int;

// Structure are used in place of class for public variables only. No methods or private variables
// FBullCowCount keep tracks of Bulls and Cows count
struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

// Check enum vs enum class; if just enum, variables are global
// EGuessStatus keep tracks of all the possible errors or invalidity
enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    Not_Alphabet,
    WhiteSpace,
    ZeroLength
};

// FBullCowGame has all the variables and methods prototypes
class FBullCowGame {
public:
    FBullCowGame(); // Constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset(); // Resets game to initial state
    
    FBullCowCount SubmitValidGuess(FString);
    
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    
    bool IsAlphabet(FString) const;
    bool IsWhiteSpace(FString) const;
    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};
