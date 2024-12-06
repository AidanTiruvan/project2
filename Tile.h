#ifndef TILE_H
#define TILE_H

#include "Player.h"
#include <tuple>

class Tile {
private:
    char _color; // represents the color of the tile the player is on in a char for simplicity

public:
    // constructors for tile.cpp
    Tile();
    Tile(char color);

    // getters for original state
    char getColor() const;

    // setters for updating player color
    void setColor(char newColor);

    int grassLand(); //Will determine if a randomEvent happens and will change pridePoints
    tuple<int, int, int> oasisTile(); //Will add 200 to each stat
    int advisorTile();//should return index of counselor, -1 if no change
    tuple<int, int, int> graveYard(); //subtract 100 from each stat
    int hyenaTile(); //should subtract 300 stamina
    int riddleTile(); //if right, plus 500 wisdom
    void prideRock(); 

    tuple<int, int, int, int> event(string array[], string array2[]) const;
};

#endif
