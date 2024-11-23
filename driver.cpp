#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Tile.h"
#include "Player.h"

int main()
{
    srand(time(0)); // random number generator to make sure that on the start of the game, the numbers are always different

    int numPlayers;
    do
    {
        std::cout << "Enter the number of players (2-4) ";
        std::cin >> numPlayers;

        if (numPlayers < 2 || numPlayers > 4)
        {
            std::cout << "Thats not 2-4 players try again " << std::endl;
        }
    } while (numPlayers < 2 || numPlayers > 4);

    // creates the board with the specified amount of players but doesnt really work for 2+ right now
    Board board(numPlayers);

    // displays the board for the first time in its starting state
    std::cout << "\nInitial Board State:\n";
    board.displayBoard();

    bool game_over = false;

    // main meat of the gameplay loop, this just acts as a simulation almost for what should be played
    while (!game_over)
    {
        for (int i = 0; i < numPlayers; i++)
        {
            std::cout << "\nPlayer " << i + 1 << "'s turn:" << std::endl;

            // this just simulates the spinner results, maybe at the end of the project we can create a UI for this or something
            int spinner = rand() % 6 + 1;
            std::cout << "Spinner result: " << spinner << std::endl;

            for (int move = 0; move < spinner; move++)
            {
                // this is important since on every turn it moves the player and therefore applies the tile effect 
                //(only works for the first 2 players as of now)
                bool reachedEnd = board.movePlayer(i);

                // checks if any player reached the pride rock, somehow this works for the 3rd player and
                // because the board is messed up, tile events dont really work on any other players other than the first two
                if (reachedEnd)
                {
                    std::cout << "Player " << i + 1 << " has reached the pride rock" << std::endl;
                    game_over = true;
                    break;
                }
            }

            // this basically displays the updated board after each turn, this works well 
            board.displayBoard();

            if (game_over)
            {
                break;
            }
        }
    }

    // spits out the scores and whatnot for the users to see the final standings
    std::cout << "\nNoice the game is over here are the scores:" << std::endl;
    for (int i = 0; i < numPlayers; i++)
    {
        int pridePoints = board.getPlayer(i).getPride();
        std::cout << "player " << i + 1 << ": " << pridePoints << " Pride points" << std::endl;
    }

    // this is supposed to determine the winner but it seems to not work when the values/scores are negative
    int winnerIndex = 0;
    int maxPridePoints = 0;
    for (int i = 0; i < numPlayers; i++)
    {
        if (board.getPlayer(i).getPride() > maxPridePoints)
        {
            maxPridePoints = board.getPlayer(i).getPride();
            winnerIndex = i;
        }
    }

    std::cout << "\ncongrats player " << winnerIndex + 1 << " u have the most pride" << std::endl;

    return 0;
}
