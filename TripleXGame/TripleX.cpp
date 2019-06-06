#include <iostream>
#include <ctime>

void PrintIntroduction(int Difficulty)
{  
    std::cout << "Your difficult level is: " << Difficulty << std::endl; 
    std::cout << "You will be required to enter correct codes to enter the room\n";
    
}
bool PlayGame(int Difficulty) //returns bolean: true or false
{
    PrintIntroduction(Difficulty);

    //declaring constant so please do not try to change the code
    
    const int A = (rand() % Difficulty) + Difficulty;
    const int B = (rand() % Difficulty) + Difficulty;
    const int C = (rand() % Difficulty) + Difficulty;


    int CodeSum = A + B + C;
    int CodeProduct = A * B * C;


    std::cout << "The codes add-up to: " << CodeSum <<std::endl;
    std::cout << "The codes multiply to give: " << CodeProduct <<std::endl;

    /*
        Adding endline

    */
    std::cout << std::endl;

    int GuessA, GuessB, GuessC;
    std::cin >> GuessA;
    std::cin >> GuessB;
    std::cin >> GuessC;

    int GuessSum = GuessA + GuessB + GuessC;
    int GuessProduct = GuessA * GuessB * GuessC;

    if (GuessSum == CodeSum && GuessProduct == CodeProduct) 
    {
        return true;
    }
    else
    {
        std::cout << "You are wrong! Please try again \n";
        return false;
    }
}

int main()
{
    srand(time(NULL));
    std::cout << "Hello Agent! You are on a mission to hack into a secret server room\n";
    int LevelDifficulty = 1;
    const int MaximumLevel = 5;
    while (LevelDifficulty <= MaximumLevel)
    {
        bool bLevelComplete = PlayGame(LevelDifficulty);
        std::cin.clear(); // clears any errors
        std::cin.ignore(); // discards the buffer

        if (bLevelComplete)
        {
            ++LevelDifficulty;
            if (LevelDifficulty <= MaximumLevel) {
                std::cout << "You nailed it. You move to the next level now. \n";
            //increase the difficulty level of the game
            }
            
        }
        
    }
    std::cout << "Congratulation you are the winner\n";
    return 0;
}
