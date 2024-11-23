#ifndef GAME_H
#define GAME_H
#include "Board.h"
#include "Player.h"
#include "Tile.h"
#include <vector>

struct Game{
    int _players_count; //Keeps track of number of players for mulitplayer game
    bool _game_end; //Bool checking to make sure everyone has made it to the end of the game for scoring
    vector<Player> _players; //Will create however many player objects are needed
    Game();
    Game(int playersCount);
    void setPlayers();
    void setGameEnd(bool);
    void setPlayerCount(int);
};


#endif