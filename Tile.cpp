#include "Tile.h"
#include <iostream>

// default constructor cuz most are green
Tile::Tile() : _color('G') {}

// parameterized constructor
Tile::Tile(char color) : _color(color) {}

// getter from tile.h
char Tile::getColor() const {
    return _color;
}

// setter from tile.h
void Tile::setColor(char newColor) {
    _color = newColor;
}

// this is basically all the tiles and their respective events 
tuple<int, int, int, int> Tile::event() const {
    int prideChange = 0, staminaChange = 0, strengthChange = 0, wisdomChange = 0;

    if (_color == 'G') { // green is the regular tile
        if (rand() % 2 == 0) { // we define this to have a 50% chance
            cout << "Aidan's spirit blesses you. You win 100 Pride Points!\n"; //lets make this an actual random event from random_events.txt later
            prideChange = 100;
        } else {
            cout << "Womp womp nothing happens on this tile\n";
        }
    } else if (_color == 'B') { // blue is oasis tile
        cout << "Epic u found an oasis, u gain 200 stamina, strength, and wisdom\n";
        staminaChange = 200;
        strengthChange = 200;
        wisdomChange = 200;
    } else if (_color == 'P') { // pink is counseling tile
        cout << "Counseling tile (to be implemented)\n";
        // we can add the counseling logic and whatnot later 
    } else if (_color == 'R') { // red is the graveyard tile
        cout << "Womp womp this is the graveyard tile, u lose 100 stamina, strength, and wisdom\n";
        prideChange = -100;
        staminaChange = -100;
        strengthChange = -100;
        wisdomChange = -100;
    } else if (_color == 'N') { // brown is the hyene tile 
        cout << "L the hyenas got u, they take back to your previous position\n";
        // we can implement this later as it involves active position state management
    } else if (_color == 'U') { // purple is the challenge tile
        cout << "Nice one now solve this riddle (to be implemented)\n";
        wisdomChange = 500;
        // lets implement a good list of riddles the user can do or whatnot then call it here 
    } else if (_color == 'O') { // orange is the final pride rock
        cout << "nice u reached the pride rock, pride rocks man!\n";
    }

    return make_tuple(prideChange, staminaChange, strengthChange, wisdomChange); //all of these are called in board 
}
