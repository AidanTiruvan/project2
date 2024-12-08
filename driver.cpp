#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include "others.h"

int main()
{
    srand(time(0)); // random number generator to make sure that on the start of the game, the numbers are always different

    int numPlayers = 0;
    printLines();
    cout<<"Enter number of players. (2-4)"<<endl;
    numPlayers = checkValid(2, 4, numPlayers);
    printLines();

    // creates the board with the specified amount of players
    Board board(numPlayers);

    // displays the board for the first time in its starting state
    //cout << "\nInitial Board State:\n";
    board.displayBoard();


    bool game_over = false;
    bool turn_over = false;
    int menuChoice = 0;
    int subMenuChoice = 0;
    bool subExit = false;
    int spinner;
    int overCount = 0;
    while(!game_over){
        for(int i = 0; i <numPlayers; i++){
            turn_over = false;
            if(board.getPlayerPosition(i) == board.getBoardSize() - 1){ //Should skip the players turn if they have finished
                turn_over = true;
            }
            while(!turn_over){
                subExit = false; //When made true, will exit back out to main menu
                printLines();
                cout<<"Player "<<i + 1<<"'s Menu -- Please select an option."<<endl;
                cout<<"(1) Spin"<<endl;
                cout<<"(2) Check Player Progress"<<endl; //Will open a sub menu to display either their lane or check pride points
                cout<<"(3) Review Player Stats"<<endl;
                cout<<"(4) Review Advisor"<<endl;
                cout<<"(5) Review Game Rules"<<endl;
                cout<<"(6) End Game Early (No one will win!)"<<endl;
                menuChoice = checkValid(1, 6, menuChoice);
                printLines();
                switch(menuChoice){
                    case 1:{ //SOME KINDA ISSUE WITH GAME OVER LOGIC NOT WORKING
                        spinner = rand() % 6 + 1;
                        cout << "Spinner result: " << spinner << endl;
                            bool reachedEnd = board.movePlayer(i, spinner);//pass the spinner here to make it only do the event for the final tile
                            if (reachedEnd){
                                cout << "Player " << i + 1 << " has reached Pride Rock." << endl;
                                //game_over = true;
                                overCount++;
                                if(overCount == numPlayers){
                                    game_over = true;
                                }
                            }
                            printLines();
                            board.displayBoard();
                            turn_over = true;
                        break;
                    }
                    
                    case 2:
                        while(!subExit){
                            cout<<"(1) Show Lane"<<endl;
                            cout<<"(2) Check Pride Points"<<endl;
                            cout<<"(3) Back"<<endl;
                            subMenuChoice = checkValid(1, 3, subMenuChoice);
                            printLines();
                            switch(subMenuChoice){
                                case 1:
                                    board.displayTrack(i);
                                    subExit = true;
                                    break;
                                case 2:
                                    cout<<"Pride Points: "<<board.getPlayer(i).getPride()<<endl; //Will need to remember player name input
                                    subExit = true;
                                    break;
                                case 3:
                                    subExit= true;
                                    break;
                            }
                        }
                        break;
                    case 3:
                        while(!subExit){
                            cout<<"(1) Display Current Stats"<<endl;
                            cout<<"(2) Visualize Current Final Pride Points"<<endl;
                            cout<<"(3) Back"<<endl;
                            subMenuChoice = checkValid(1, 3, subMenuChoice);
                            printLines();
                            switch(subMenuChoice){
                                case 1:
                                    board.displayStats(i);
                                    subExit = true;
                                    break;
                                case 2:
                                    board.getPlayer(i).visualizeStats();
                                    subExit = true;
                                    break;
                                case 3:
                                    subExit = true;
                                    break;
                            }
                        }
                        break;
                    case 4:
                        if(board.getPlayer(i).getAdvisor() != ""){
                            cout<<board.getPlayer(i).getAdvisor()<<endl;
                        }else{
                            cout<<"No advisor :("<<endl;
                        }
                        break;
                    case 5:
                        board.displayRules();
                        break;
                    case 6:
                        //Just for testing
                        cout<<"What a shame."<<endl;
                        exit(0);
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
    std::cout << "\nThe game is over! Here are the final scores:" << std::endl;
    for (int i = 0; i < numPlayers; i++)
    {
        board.getPlayer(i).convertStats();
        int pridePoints = board.getPlayer(i).getPride();
        std::cout << "Player " << i + 1 << ": " << pridePoints << " Pride points" << std::endl;
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
