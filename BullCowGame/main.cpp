//
//  main.cpp
//  BullCowGame
//
//  Created by Kuldeep on 5/12/19.
//  Copyright © 2019 KuldeepCompany. All rights reserved.
//


/* This is the console executable, that makes use of the BullCow class.
 This acts as the view in a MVC pattern, and is responsible for all
 user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// to make syntax Unreal Friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
static void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// the entry point for our application
int main()
{
    PrintIntro();
    
    bool bPlayAgain = false;
    
    do {
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    return 0; // exit the application
}

void PrintIntro()
{
    
    std::cout << "Hello, Welcome to the Bulls and Cows, a fun game!";
    
    std::cout << " _____    _    _      _      _____            ____   ____    _    _   _____       _____    ___    __   __   _____\n";
    std::cout << "| ___ |  | |  | |    | |    /  ___|          /  __  /  _  | | |  | | /  ___|     |  __ |  | _ |  |  |_|  | |  ___|\n";
    std::cout << "| |_/ /  | |  | |    | |    | `--.   ______  | /    | | | | | |  | | | `--.      | |     | |_| | | . _ . | | |__\n";
    std::cout << "| ___ |  | |  | |    | |     `--. | |______| | |    | | | | | |/|| |  `--. |     | |  __ |  _  | | |   | | |  __|\n";
    std::cout << "| |_/ /  |_|  | |___ | |___/ |__/ /          | |__/ | |_/ / |  / | |  ___/ /     | |_| | | | | | | |   | | | |___\n";
    std::cout << "|____/   |__/ |____/ |____/ |____/            |____/ |___/  | /   || |____/       |____/ |_| |_/ |_|   |_/ |____/\n";
    
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() <<" letter isogram that I am thinking of? \n\n";
    return;
}

// plays a single game to completion
static void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls =  " << BullCowCount.Bulls << std::endl;
        std::cout << "Cows =  " << BullCowCount.Cows << std::endl;
        std::cout << std::endl;
    }
    
    PrintGameSummary();
}

FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FText Guess = "";
    int32 CurrentTry = BCGame.GetCurrentTry();
    
    do {
        std::cout << "Try " << CurrentTry << " of " <<  BCGame.GetMaxTries() <<": Please enter your guess: ";

        std::getline(std::cin, Guess);
        
        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status)
        {
            case EGuessStatus::Wrong_Length:
                std::cout << "The word you entered is of wrong length. \n";
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word: \n\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters. \n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters. \n\n";
                break;
            case EGuessStatus::ZeroLength:
                std::cout << "This word has no length. Please enter a word. \n\n";
                break;
            case EGuessStatus::Not_Alphabet:
                std::cout << "Please enter a word with alphabets only. \n\n";
                break;
            case EGuessStatus::WhiteSpace:
                std::cout << "Please enter a word without whitespace. \n\n";
                break;
            default:
                break;
        }
    }
    while (Status != EGuessStatus::OK);
    
    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again with the same hidden word? [y/n] ";
    
    FText Response = "";
    getline(std::cin, Response);
    
    return (Response[0] == 'y') || (Response[0] == 'Y'); //single quote for char and double quote for string
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon()){
        std::cout << "Hurray! Well done! You have won the game! \n\n";
    }
    else {
        std::cout << "Sorry! Bad Luck! You have ran out of tries. \n\n";
    }
}
