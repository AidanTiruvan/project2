#ifndef TILE_H
#define TILE_H

#include "Player.h"
#include <tuple>

class Tile {
private:
    char color; // represents the color of the tile the player is on in a char for simplicity

public:
    // constructors for tile.cpp
    Tile();
    Tile(char color);

    // getters for original state
    char getColor() const;

    // setters for updating player color
    void setColor(char newColor);

    std::tuple<int, int, int, int> event() const;
};

#endif
