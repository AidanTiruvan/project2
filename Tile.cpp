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

int Tile::grassLand(string events[], int advisorNum, int age){
    if(rand() % 2 == 0){
        cout<<events[0]<<endl;
        //WILL BE MADE PATH DEPENDENT
        return 100; //placeholder
    }else{
        cout<<"You landed on an ordinary piece of land."<<endl;
        return 0;
    }
}

tuple<int, int, int> Tile::oasisTile(){
    int stamina = 200;
    int strength = 200;
    int wisdom = 200;
    cout<<"You arrive at a cute lil oasis."<<endl;
    cout<<"Change in Strength: +"<<strength<<endl;
    cout<<"Change in Stamina: +"<<stamina<<endl;
    cout<<"Change in Wisdom: +"<<wisdom<<endl;
    return make_tuple(strength, stamina, wisdom);
}


tuple<int, int, int> Tile::graveYard(){
    int strength = -100;
    int stamina = -100;
    int wisdom = -100;
    cout<<"The ghosts of players past drag you back 10 places!"<<endl;
    cout<<"Change in Strength: "<<strength<<endl;
    cout<<"Change in Stamina: "<<stamina<<endl;
    cout<<"Change in Wisdom: "<<wisdom<<endl;
    return make_tuple(strength, stamina, wisdom);
}

int Tile::hyenaTile(){
    cout<<"A wild pack of Hyenas jump you! You get carried back to your last position."<<endl;
    cout<<"Change in Stamina: -300"<<endl;
    return -300;
}

int Tile::riddleTile(string riddle[]){
    cout<<riddle[0]<<endl;
    string answer;
    cin>>answer;
    if(answer == riddle[1]){
        cout<<"You're such a smarty pants. The Pride Lands bestows upon you 500 wisdom points."<<endl;
        return 500; //If right
    }else{
        cout<<"You answer wrong. Nothing happens :("<<endl;
        return 0;
    }
}

void Tile::prideRock(){
    cout<<"You've finally reached Pride Rock!"<<endl;
}

// this is basically all the tiles and their respective events 
/*
tuple<int, int, int, int> Tile::event(string riddlearr[], string eventarr[]) const {
    int prideChange = 0, staminaChange = 0, strengthChange = 0, wisdomChange = 0;
    int riddleChoice; //spinner to pick a random riddle
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
        staminaChange = -100;
        strengthChange = -100;
        wisdomChange = -100;
    } else if (_color == 'N') { // brown is the hyene tile 
        cout << "L the hyenas got u, they take back to your previous position\n";
        staminaChange = -300;
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
*/
