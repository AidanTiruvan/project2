#include "Tile.h"
#include <iostream>

// default constructor cuz most are green
Tile::Tile() : color('G') {}

// parameterized constructor
Tile::Tile(char color) : color(color) {}

// getter from tile.h
char Tile::getColor() const {
    return color;
}

// setter from tile.h
void Tile::setColor(char newColor) {
    color = newColor;
}

// this is basically all the tiles and their respective events 
std::tuple<int, int, int, int> Tile::event() const {
    int prideChange = 0, staminaChange = 0, strengthChange = 0, wisdomChange = 0;

    if (color == 'G') { // green is the regular tile
        if (rand() % 2 == 0) { // we define this to have a 50% chance
            std::cout << "Random event, you win 100 Pride Points\n"; //lets make this an actual random event from random_events.txt later
            prideChange = 100;
        } else {
            std::cout << "Womp womp nothing happens on this tile\n";
        }
    } else if (color == 'B') { // blue is oasis tile
        std::cout << "Epic u found an oasis, u gain 200 stamina, strength, and wisdom\n";
        staminaChange = 200;
        strengthChange = 200;
        wisdomChange = 200;
    } else if (color == 'P') { // pink is counseling tile
        std::cout << "Counseling tile (to be implemented)\n";
        // we can add the counseling logic and whatnot later 
    } else if (color == 'R') { // red is the graveyard tile
        std::cout << "Womp womp this is the graveyard tile, u lose 100 stamina, strength, and wisdom\n";
        prideChange = -100;
        staminaChange = -100;
        strengthChange = -100;
        wisdomChange = -100;
    } else if (color == 'N') { // brown is the hyene tile 
        std::cout << "L the hyenas got u, they take back to your previous position\n";
        // we can implement this later as it involves active position state management
    } else if (color == 'U') { // purple is the challenge tile
        std::cout << "Nice one now solve this riddle (to be implemented)\n";
        wisdomChange = 500;
        // lets implement a good list of riddles the user can do or whatnot then call it here 
    } else if (color == 'O') { // orange is the final pride rock
        std::cout << "nice u reached the pride rock, pride rocks man!\n";
    }

    return std::make_tuple(prideChange, staminaChange, strengthChange, wisdomChange); //all of these are called in board 
}
