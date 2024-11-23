#include <iostream>
#include "Board.h"
#include "Tile.h"
#include "Player.h"

int main()
{
    srand(time(0)); // random number for board

    int numPlayers;
    do
    {
        cout << "Enter the number of players (2-4): ";
        cin >> numPlayers;

        if (numPlayers < 2 || numPlayers > 4)
        {
            cout << "Thats not 2-4, try again" << endl;
        }
    } while (numPlayers < 2 || numPlayers > 4);

    // this creates the board with the selected number of players, this works now somehow
    Board b(numPlayers);

    b.displayBoard(); // initial board state

    bool game_over = false;

    while (!game_over)
    {
        for (int i = 0; i < numPlayers; i++) // simulates each player turn for testing
        {
            cout << "Player " << i + 1 << "'s turn:" << endl;
            int spinner = rand() % 6 + 1; // random num generation between 1 and 6
            cout << "Spinner result: " << spinner << endl;

            for (int move = 0; move < spinner; move++)
            {
                if (b.movePlayer(i))
                {
                    cout << "Player " << i + 1 << " reached Pride Rock" << endl;
                    game_over = true;
                    break;
                }
            }

            b.displayBoard();

            if (game_over)
            {
                break;
            }
        }
    }

    cout << "\nGame Over! Thanks for playing." << endl;

    return 0;
}
