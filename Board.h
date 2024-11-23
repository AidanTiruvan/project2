#ifndef BOARD_H
#define BOARD_H
#include "Tile.h"
#include "Player.h"

class Board
{
private:
    static const int _BOARD_SIZE = 52;
    Tile _tiles[3][_BOARD_SIZE]; //CHANGE FOR NUM OF PLAYERS
    static const int _MAX_PLAYERS = 3; //CHANGE FOR NUM OF PLAYERS
    int _player_count;
    int _player_position[_MAX_PLAYERS];
    void displayTile(int player_index, int pos);
    void initializeTiles(int player_index); //WILL BE REMOVED, JUST HERE TO VISUALIZE RN
    void initializeTilesPride(int player_index);
    void initializeTilesTrain(int player_index);
    bool isPlayerOnTile(int player_index, int pos);
    Player players[2]; //Update for number of players

public:
    Board();
    Board(int player_count);
    void displayTrack(int player_index);
    void initializeBoard();
    void displayBoard();
    bool movePlayer(int player_index);
    int getPlayerPosition(int player_index) const;
};

#endif