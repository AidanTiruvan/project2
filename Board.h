#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "Player.h"
#include <fstream>

class Board
{
private:
    static const int _BOARD_SIZE = 52;       // constant for the number of tiles in each player's path
    static const int _MAX_PLAYERS = 4;       // max players allowed in the game

    Tile _tiles[_MAX_PLAYERS][_BOARD_SIZE];             // represents the tiles for each path 
    int _player_positions[_MAX_PLAYERS];    // tracks each player's position on the board
    Player players[_MAX_PLAYERS];           // an array of player objects to store the players and their stats
    int _player_count;                      // the actual number of players in the game, set dynamically based on user input

    // Helper functions
    void displayTile(int player_index, int pos);   // shows a single tile for the specified players position
    bool isPlayerOnTile(int player_index, int pos); // checks if a player is standing on a specific tile (useful for board display logic)

    // Tile initialization
    void initializeTiles(char pathType, int index);   // sets up the tiles for each path

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
    bool movePlayer(int player_index);    // moves a player forward and triggers the effect of the tile they land on
    int getPlayerPosition(int player_index) const; // gets a player's current position
    Player getPlayer(int player_index);  // returns a copy of a player object

    //Stats
    void displayStats(int index);
    void playerPride(int index);
    void playerAdvisor(int index);

    //Imports
    void importFiles();
};

#endif
