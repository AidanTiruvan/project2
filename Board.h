#include "Tile.h"
#include "Player.h"
#include <fstream>
#include <vector>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board
{
private:
    static const int _BOARD_SIZE = 52;       // constant for the number of tiles in each player's path
    static const int _MAX_PLAYERS = 4;       // max players allowed in the game

    Tile _prideTiles[_BOARD_SIZE];           // replaced _tiles with _prideTiles for pride lands board
    Tile _cubTiles[_BOARD_SIZE];             // added _cubTiles for cub training board
    int _player_positions[_MAX_PLAYERS];     // tracks each player's position on the board
    Player players[_MAX_PLAYERS];            // an array of player objects to store the players and their stats
    int _player_count;                       // the actual number of players in the game, set dynamically based on user input

    // Helper functions
    void displayTile(char pathType, int pos);   //changed signature to displaytile
    bool isPlayerOnTile(int player_index, char pathType, int pos); //modified the signature to include pathType

    // Tile initialization
    void initializeTiles();   // removed string pathType,int index parameters

    //Imports
    vector<string> _characterVec;
    vector<string> _advisorVec;
    vector<string> _riddleVec;
    vector<string> _eventsVec;
    vector<string> _ruleVec;

public:
    // Constructors
    Board();                              // default constructor
    Board(int player_count);              // constructor that sets up the board based on how many players are playing

    // Board initialization
    void initializeBoard();               // creates the entire board + handles both paths

    // Board display
    void displayTrack(int player_index);  // shows all the tiles for one player's path
    void displayBoard();                  // shows the entire board, including both paths for all players

    // Player and tile interaction
    bool movePlayer(int player_index, int spinner);    // moves a player forward and triggers the effect of the tile they land on
    int getPlayerPosition(int player_index) const; // gets a player's current position
    Player getPlayer(int player_index);  // returns a copy of a player object

    //Stats
    void displayStats(int index);
    void playerPride(int index);
    void playerAdvisor(int index);
    static const int getBoardSize();

    //Imports
    void importFiles();
    int checkValid(int start, int end, int choice);//including this since the stupid header file is being buggy
    void printLines();//this too
    void duringTurnBoard();
    void displayRules();
};

#endif
