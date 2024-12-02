#include "Board.h"
#include <cstdlib>
#include <iostream>
#include <ctime>

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define RESET "\033[0m"

// default constructor for single-player board
Board::Board() {
    _player_count = 1;
    _player_positions[0] = 0;

    // initialize the board for a single player
    initializeBoard();
}

// constructor for custom number of players
Board::Board(int player_count) {
    if(player_count > _MAX_PLAYERS){
        _player_count = _MAX_PLAYERS;
    }else{
        _player_count = player_count;
    }

//Give each player in the Player array a path type, should be error handled by setPath
    string path_type;
    for(int i = 0; i < _player_count; i++){
        cout<<"Player "<<i + 1<<", please select your path. 'Pride Lands' or 'Cub Training'."<<endl;
        getline(cin, path_type);
        players[i].setPath(path_type);
    }

    // initialize positions for each player
    for (int i = 0; i < _player_count; i++) {
        _player_positions[i] = 0;
    }

    // initialize the board
    initializeBoard();
}

// initializes the board for both paths (cub training and pride lands)
void Board::initializeBoard() {
    for (int i = 0; i < _player_count; i++) {
        initializeTiles(players[i].getPath(), i);
    }
}

// initializes tiles for a specific path
void Board::initializeTiles(char pathType, int j) {
    int green_count = 0;
    Tile tile;
    //if player picks pridelands this happens
    if(pathType == 'P'){
        for (int i = 0; i < _BOARD_SIZE; i++) {
            //Track of green tile positions to ensure we place exactly 30 greens
            if (i == _BOARD_SIZE - 1) {
            // Set the last tile as Orange for "Pride Rock"
                tile.setColor('O');
            } else if (i == 0) {
            // Set the last tile as Orange for "Pride Rock"
                tile.setColor('Y');
            } else if (green_count < 30 && (rand() % (_BOARD_SIZE - i) <= 30 - green_count)) {
                tile.setColor('G');
                green_count++;
            } else {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red,Purple
                int color_choice = rand() % 100;
                if(color_choice < 30){
                    tile.setColor('P'); //30 Percent chance for advisor tile
                }else if(color_choice < 45){
                    tile.setColor('B'); //15 percent chance for oasis tile
                }else if(color_choice < 60){
                    tile.setColor('R'); //15 percent chance for graveyard tile
                }else if(color_choice < 80){
                    tile.setColor('N'); //20 percent chance for hyena tile
                }else{
                    tile.setColor('U'); //20 percent chance for riddle tile
                }
            }
            _tiles[j][i] = tile;
        }
    }else{ //If player picks cub training this happens
            //  WILL WANT TO MAKE IT SO ADVISORS GIVE MORE BONUS ON GREEN STUFF AND OASIS TO NEGATE HOW MUCH MORE BAD STUFF
        for (int i = 0; i < _BOARD_SIZE; i++) {
            //Track of green tile positions to ensure we place exactly 30 greens
            if (i == _BOARD_SIZE - 1) {
            // Set the last tile as Orange for "Pride Rock"
                tile.setColor('O');
            } else if (i == 0) {
            // Set the last tile as Orange for "Pride Rock"
                tile.setColor('Y');
            } else if (green_count < 30 && (rand() % (_BOARD_SIZE - i) <= 30 - green_count)) {
                tile.setColor('G');
                green_count++;
            } else {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red,Purple
                int color_choice = rand() % 100;
                if(color_choice < 10){
                    tile.setColor('P'); //10 Percent chance for advisor tile
                }else if(color_choice < 25){
                    tile.setColor('B'); //15 percent chance for oasis tile
                }else if(color_choice < 55){
                    tile.setColor('R'); //30 percent chance for graveyard tile
                }else if(color_choice < 80){
                    tile.setColor('N'); //25 percent chance for hyena tile
                }else{
                    tile.setColor('U'); //20 percent chance for riddle tile
                }
            }
            _tiles[j][i] = tile;
        }
    }
}

// displays a single tile with color and player presence
void Board::displayTile(int player_index, int pos) {
    string color = "";
    bool playerOnTile = isPlayerOnTile(player_index, pos);

    switch (_tiles[player_index][pos].getColor()) {
        case 'R': color = RED; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'N': color = BROWN; break;
        case 'U': color = PURPLE; break;
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
    }

    if (playerOnTile) {
        std::cout << color << "|" << (player_index + 1) << "|" << RESET;
    } else {
        std::cout << color << "| |" << RESET;
    }
}

// displays the track for a specific player
void Board::displayTrack(int player_index) {
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile(player_index, i);
    }
    std::cout << std::endl;
}

// displays the entire board for all players
void Board::displayBoard() {
    for (int i = 0; i < _player_count; i++) {
        cout << "player " << i + 1 << "'s path:\n";
        displayTrack(i);
        cout << endl;
    }
}

// moves a player forward and applies tile effects
bool Board::movePlayer(int player_index) {
    _player_positions[player_index]++;

    // check if the player reached the final tile
    if (_player_positions[player_index] >= _BOARD_SIZE) {
        _player_positions[player_index] = _BOARD_SIZE - 1;
        return true; // player reached pride rock
    }

    // apply effects from the tile the player lands on
    Tile currentTile = _tiles[player_index][_player_positions[player_index]];
    auto [prideChange, staminaChange, strengthChange, wisdomChange] = currentTile.event();

    players[player_index].setPride(players[player_index].getPride() + prideChange);
    players[player_index].addStamina(staminaChange);
    players[player_index].addStrength(strengthChange);
    players[player_index].addWisdom(wisdomChange);

    return false;
}

// checks if a player is on a specific tile
bool Board::isPlayerOnTile(int player_index, int pos) {
    return (_player_positions[player_index] == pos);
}

// gets the current position of a player
int Board::getPlayerPosition(int player_index) const {
    if (player_index >= 0 && player_index < _player_count) {
        return _player_positions[player_index];
    }
    return -1; // invalid player index
}

// returns a copy of the player object by index
Player Board::getPlayer(int player_index) {
    return players[player_index];
}
