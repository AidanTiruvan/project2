#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Board.h"
#include "Tile.h"
#include "Player.h"
#include "others.h"

//Zach Roberson and Aidan Tiruvan


// define the playerscore structure to hold player number and pride points
struct PlayerScore {
    int playerNumber; // player identifier
    int pridePoints;  // players pride points

    // constructor for convenience
    PlayerScore(int number, int points) : playerNumber(number), pridePoints(points) {}
};

// function to perform bubble sort on the leaderboard and return a sorted vector
vector<PlayerScore> bubbleSortLeaderboard(vector<PlayerScore> leaderboard) {
    int n = leaderboard.size(); // get the number of players
    bool swapped; // flag to check if any swaps occurred in a pass

    // perform n-1 passes through the leaderboard
    for (int i = 0; i < n - 1; ++i) {
        swapped = false; // reset the swapped flag at the start of each pass

        // compare adjacent elements and swap if necessary
        for (int j = 0; j < n - i - 1; ++j) {
            if (leaderboard[j].pridePoints < leaderboard[j + 1].pridePoints) {
                // swap players
                PlayerScore temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
                swapped = true; // set the flag since a swap occurred
            }
        }

        // if no swaps occurred, the leaderboard is sorted
        if (!swapped)
            break;
    }

    return leaderboard; // return the sorted leaderboard
}

int main()
{
    srand(time(0)); // random number generator to make sure that on the start of the game, the numbers are always different

    int numPlayers = 0;
    printLines();
    cout << "Enter number of players. (2-4)" << endl;
    numPlayers = checkValid(2, 4, numPlayers);
    printLines();

    // creates the board with the specified amount of players
    Board board(numPlayers); //board now manages two separate boards internally

    // displays the board for the first time in its starting state
    //cout << "\nInitial Board State:\n";
    board.displayBoard(); //now displays both the pride lands and cub training boards

    bool game_over = false;
    bool turn_over = false;
    int menuChoice = 0;
    int subMenuChoice = 0;
    bool subExit = false;
    int spinner;
    //int winningPlayer = -1; // to store the index of the winning player
    int playersFinished = 0; // to track the number of players who have reached Pride Rock
    vector<bool> finished(numPlayers, false); // To track which players have reached Pride Rock

    // Initialize playersFinished based on players already at Pride Rock
    for(int i = 0; i < numPlayers; i++){
        if(board.getPlayerPosition(i) >= board.getBoardSize() - 1){
            playersFinished++;
            finished[i] = true;
            cout << "Debug: Player " << i + 1 << " is already at Pride Rock at game start." << endl;
        }
    }

    while(!game_over){
        for(int i = 0; i < numPlayers; i++){
            turn_over = false;
            playersFinished = 0;
            // check if the player has already reached the final tile
            for(int j = 0; j < numPlayers; j++){
                if(board.getPlayerPosition(j) >= board.getBoardSize() - 1){
                    playersFinished++;
                }
            }

            if(playersFinished == numPlayers){
                game_over = true;
            }
            
            if(board.getPlayerPosition(i) >= board.getBoardSize() - 1){ 
                // player finished, skip their turn
                turn_over = true;
                continue;
            }

            while(!turn_over){
                subExit = false; //when made true, will exit back out to main menu
                printLines();
                cout << "Player " << i + 1 << "'s Menu -- Please select an option." << endl;
                cout << "(1) Spin" << endl;
                cout << "(2) Check Player Progress" << endl; //Will open a sub menu to display either their lane or check pride points
                cout << "(3) Review Player Stats" << endl;
                cout << "(4) Review Advisor" << endl;
                cout << "(5) Review Game Rules" << endl;
                cout << "(6) End Game Early (No one will win!)" << endl;
                menuChoice = checkValid(1, 6, menuChoice);
                printLines();

                switch(menuChoice){
                    case 1:{
                        spinner = rand() % 6 + 1;
                        cout << "Spinner result: " << spinner << endl;
                        board.movePlayer(i, spinner); //pass the spinner here to make it only do the event for the final tile
                        printLines();
                        board.displayBoard(); //displayBoard now shows the updated positions on both boards
                        turn_over = true;
                        break;
                    }
                    case 2:
                        while(!subExit){
                            cout << "(1) Show Lane" << endl;
                            cout << "(2) Check Pride Points" << endl;
                            cout << "(3) Back" << endl;
                            subMenuChoice = checkValid(1, 3, subMenuChoice);
                            printLines();
                            switch(subMenuChoice){
                                case 1:
                                    board.displayTrack(i); //displayTrack now shows the player board based on their path
                                    subExit = true;
                                    break;
                                case 2:
                                    cout << "Pride Points: " << board.getPlayer(i).getPride() << endl;
                                    subExit = true;
                                    break;
                                case 3:
                                    subExit= true;
                                    break;
                                default:
                                    cout << "Invalid Input." << endl;
                                    break;
                            }
                        }
                        break;
                    case 3:
                        while(!subExit){
                            cout << "(1) Display Current Stats" << endl;
                            cout << "(2) Visualize Current Final Pride Points" << endl;
                            cout << "(3) Back" << endl;
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
                                default:
                                    cout << "Invalid Input." << endl;
                                    break;
                            }
                        }
                        break;
                    case 4:
                        if(board.getPlayer(i).getAdvisor() != ""){
                            cout << board.getPlayer(i).getAdvisor() << endl;
                        }
                        else{
                            cout << "No advisor :(" << endl;
                        }
                        break;
                    case 5:
                        board.displayRules();
                        break;
                    case 6:
                        cout << "What a shame." << endl;
                        game_over = true; // end the game early
                        exit(0);
                        break;
                    default:
                        cout << "Invalid Input." << endl;
                        break;
                }
            }
        } // end for loop
    } // end while(!game_over)

    /*
        // main meat of the gameplay loop, this just acts as a simulation almost for what should be played
        while (!game_over)
        {
            for (int i = 0; i < numPlayers; i++)
            {
                cout << "\nPlayer " << i + 1 << "'s turn:" << endl;

                // this just simulates the spinner results, maybe at the end of the project we can create a UI for this or something
                int spinner = rand() % 6 + 1;
                cout << "Spinner result: " << spinner << endl;

                for (int move = 0; move < spinner; move++)
                {
                    // this is important since on every turn it moves the player and therefore applies the tile effect 
                    //(only works for the first 2 players as of now)
                    bool reachedEnd = board.movePlayer(i);

                    // checks if any player reached the pride rock, somehow this works for the 3rd player and
                    // because the board is messed up, tile events dont really work on any other players other than the first two
                    if (reachedEnd)
                    {
                        cout << "Player " << i + 1 << " has reached the pride rock" << endl;
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
    
    // determine the winner based on the highest pride points
    int winnerIndex = 0;
    int maxPridePoints = board.getPlayer(0).finalStats();
    for (int i = 1; i < numPlayers; i++)
    {
        if (board.getPlayer(i).finalStats() > maxPridePoints)
        {
            maxPridePoints = board.getPlayer(i).finalStats();
            winnerIndex = i;
        }
    }
    printLines();

    cout << "\nCongrats Player " << winnerIndex + 1 << "! You have the most pride!" << endl;

    // process leaderboard only if all players have finished
    //if(playersFinished == numPlayers){
        // create vector to hold player scores
        vector<PlayerScore> leaderboard;
        for(int i = 0; i < numPlayers; ++i){
            int pride = board.getPlayer(i).finalStats();
            leaderboard.emplace_back(i + 1, pride); // player numbers start at 1
        }

        // sort the leaderboard using bubble sort and get the sorted vector
        vector<PlayerScore> sortedLeaderboard = bubbleSortLeaderboard(leaderboard);

        // open a file stream to write the leaderboard
        ofstream leaderboardFile("leaderboard.txt");
        if(!leaderboardFile){
            cerr << "Error: Could not open leaderboard.txt for writing." << endl;
            return 1; // exit with error code
        }

        // write a header to the file
        leaderboardFile << "===== Leaderboard =====\n";
        // write each players score to the file
        for (PlayerScore player : sortedLeaderboard) {
            leaderboardFile << "Player " << player.playerNumber << ": " << player.pridePoints << " Pride Points\n";
        }
        leaderboardFile.close(); // close the file stream

        // display the sorted leaderboard to the users
        cout << "\n===== Final Leaderboard =====\n";
        for(int i = 0; i < sortedLeaderboard.size(); ++i){
            cout << (i + 1) << ". Player " << sortedLeaderboard[i].playerNumber 
                 << " - " << sortedLeaderboard[i].pridePoints << " Pride Points\n";
        }
    //}
    cout<<endl;

    return 0;
} // end of main
