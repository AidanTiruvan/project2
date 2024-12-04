#include <iostream>
#include <fstream>
#include <vector>
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
        cout << "Enter the number of players (2-4) ";
        cin >> numPlayers;

        if (numPlayers < 2 || numPlayers > 4)
        {
            cout << "Thats not 2-4 players try again " << endl;
        }
    } while (numPlayers < 2 || numPlayers > 4);

    // creates the board with the specified amount of players
    Board board(numPlayers);

    // displays the board for the first time in its starting state
    cout << "\nInitial Board State:\n";
    board.displayBoard();


    bool game_over = false;
    bool turn_over = false;
    int menuChoice;
    int subMenuChoice;
    bool subExit = false;
    int spinner;
    //Menu Code, not implemented yet
    while(!game_over){
        for(int i = 0; i <numPlayers; i++){
            turn_over = false;
            while(!turn_over){
                subExit = false; //When made true, will exit back out to main menu
                cout<<endl;
                cout<<"Player "<<i + 1<<"'s Menu -- Please select an option."<<endl;
                cout<<"(1) Spin"<<endl;
                cout<<"(2) Check Player Progress"<<endl; //Will open a sub menu to display either their lane or check pride points
                cout<<"(3) Review Player Stats"<<endl;
                cout<<"(4) Review Advisor"<<endl;
                cout<<"(5) Review Game Rules"<<endl;
                cout<<"(6) End Game Early (No one will win!)"<<endl;
                cin>>menuChoice;
                switch(menuChoice){
                    case 1:
                        spinner = rand() % 6 + 1;
                        cout << "Spinner result: " << spinner << endl;
                        for (int move = 0; move < spinner; move++){
                            // this is important since on every turn it moves the player and therefore applies the tile effect 
                            //(only works for the first 2 players as of now)
                            bool reachedEnd = board.movePlayer(i);

                            // checks if any player reached the pride rock, somehow this works for the 3rd player and
                            // because the board is messed up, tile events dont really work on any other players other than the first two
                            if (reachedEnd){
                                cout << "Player " << i + 1 << " has reached the pride rock" << std::endl;
                                game_over = true;
                                break;
                            }
                        }
                        turn_over = true;

                        // this basically displays the updated board after each turn, this works well 
                        board.displayBoard();

                        //if (game_over){
                            //break;
                        //}
                        break;
                        
                    case 2:
                        while(!subExit){
                            cout<<"(1) Show Lane"<<endl;
                            cout<<"(2) Check Pride Points"<<endl;
                            cout<<"(3) Back"<<endl;
                            cin>>subMenuChoice;
                            switch(subMenuChoice){
                                case 1:
                                    board.displayTrack(i);
                                    cout<<endl;
                                    subExit = true;
                                    break;
                                case 2:
                                    cout<<"Pride Points: "<<board.getPlayer(i).getPride(); //Will need to remember player name input
                                    subExit = true;
                                    break;
                                case 3:
                                    subExit= true;
                                    break;
                                default:
                                    cout<<"Invalid Choice - 1, 2, or 3."<<endl;
                                    cin>>subMenuChoice;
                                    break;
                            }
                        }
                        break;
                    case 3:
                        board.displayStats(i);
                        while(!subExit){
                            cout<<"(1) Back"<<endl;
                            cin>>subMenuChoice;
                            if(subMenuChoice == 1){
                                subExit = true;
                            }
                        }
                        break;
                    case 4:
                        cout<<endl;
                        cout<<board.getPlayer(i).getAdvisor()<<endl;
                        break;
                    case 5:
                        //Will print rules from imported game rules txt file
                        break;
                    case 6:
                        //Game end code will go here
                        turn_over = true;
                        game_over = true;
                        i = numPlayers;
                        break;
                    default:
                        cout<<"Invalid Input."<<endl;
                        break;
                }
            }
        }
    }
    
    
    
    

/*
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

*/
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
