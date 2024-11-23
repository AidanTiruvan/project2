#include "Board.h"
#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"  /* Grassy Green (34,139,34) */
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0) */
#define GREY "\033[48;2;128;128;128m" /* Grey (128,128,128) */
#define RESET "\033[0m"

void Board::initializeBoard()
{
    // Seed random number generator in your main function once
    for (int i = 0; i < 3; i++) //CHANGE FOR NUM OF PLAYERS
    {
        //IF ELSE STATEMENT TO SAY WHICH INITIALIZE TILES TO CALL
        initializeTiles(i);  // This ensures each lane has a unique tile distribution
    }
}

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

void Board::initializeTiles(int player_index) //WILL BE DELETED, HERE FOR VISUALIZATION
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;
    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for start
            temp.color = 'Y';
        } 
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
                case 0:
                    temp.color = 'B'; // Blue
                    break;
                case 1:
                    temp.color = 'P'; // Pink
                    break;
                case 2:
                    temp.color = 'N'; // Brown
                    break;
                case 3:
                    temp.color = 'R'; // Red
                    break;
                case 4:
                    temp.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}

//NEED PLAYER PATH CHOICE TO AFFECT WHICH INITIALIZE TILES IS CALLED
//DETERMINE HOW WE WANT RANDOMIZATION TO BE BALANCED
void Board::initializeTilesPride(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;
    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for start
            temp.color = 'Y';
        } 
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
                case 0:
                    temp.color = 'B'; // Blue
                    break;
                case 1:
                    temp.color = 'P'; // Pink
                    break;
                case 2:
                    temp.color = 'N'; // Brown
                    break;
                case 3:
                    temp.color = 'R'; // Red
                    break;
                case 4:
                    temp.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}

//SAME HERE AS ABOVE FUNCTION
void Board::initializeTilesTrain(int player_index)
{
    Tile temp;
    int green_count = 0;
    int total_tiles = _BOARD_SIZE;
    // Keep track of green tile positions to ensure we place exactly 30 greens
    for (int i = 0; i < total_tiles; i++)
    {
        if (i == total_tiles - 1) {
            // Set the last tile as Orange for "Pride Rock"
            temp.color = 'O';
        } 
        else if (i == 0) {
            // Set the first tile as grey for start
            temp.color = 'Y';
        } 
        else if (green_count < 30 && (rand() % (total_tiles - i) < 30 - green_count)) {
            temp.color = 'G';
            green_count++;
        }
        else
        {
            // Randomly assign one of the other colors: Blue, Pink, Brown, Red, Purple
            int color_choice = rand() % 5;
            switch (color_choice)
            {
                case 0:
                    temp.color = 'B'; // Blue
                    break;
                case 1:
                    temp.color = 'P'; // Pink
                    break;
                case 2:
                    temp.color = 'N'; // Brown
                    break;
                case 3:
                    temp.color = 'R'; // Red
                    break;
                case 4:
                    temp.color = 'U'; // Purple
                    break;
            }
        }

        // Assign the tile to the board for the specified lane
        _tiles[player_index][i] = temp;
    }
}


Board::Board()
{
     _player_count = 1;

     // Initialize player position
     _player_position[0] = 0;

     // Initialize tiles
     initializeTiles(0);
}


Board::Board(int player_count)
{
    if (player_count > _MAX_PLAYERS)
    {
        _player_count = _MAX_PLAYERS;
    }
    else
    {
        _player_count = player_count;
    }

    // Initialize player position
    for (int i = 0; i < _player_count; i++)
    {
        _player_position[i] = 0;
    }

    // Initialize tiles

    initializeBoard();
}

bool Board::isPlayerOnTile(int player_index, int pos)
{
    if (_player_position[player_index] == pos)
    {
        return true;
    }
    return false;
}

void Board::displayTile(int player_index, int pos)
{
    // string space = "                                       ";
    string color = "";
    int player = isPlayerOnTile(player_index, pos);

    // Template for displaying a tile: <line filler space> <color start> |<player symbol or blank space>| <reset color> <line filler space> <endl>

    // Determine color to display
    if (_tiles[player_index][pos].color == 'R')
    {
        color = RED;
    }
    else if (_tiles[player_index][pos].color == 'G')
    {
        color = GREEN;
    }
    else if (_tiles[player_index][pos].color == 'B')
    {
        color = BLUE;
    }
    else if (_tiles[player_index][pos].color == 'U')
    {
        color = PURPLE;
    }
    else if (_tiles[player_index][pos].color == 'N')
    {
        color = BROWN;
    }
    else if (_tiles[player_index][pos].color == 'P')
    {
        color = PINK;
    }
    else if (_tiles[player_index][pos].color == 'O')
    {
        color = ORANGE;
    }
    else if (_tiles[player_index][pos].color == 'Y')
    {
        color = GREY;
    }

     if (player == true)
    {
        cout << color << "|" << (player_index + 1) << "|" << RESET;
    }
    else
    {
        cout << color << "| |" << RESET;
    }
}

void Board::displayTrack(int player_index)
{
    for (int i = 0; i < _BOARD_SIZE; i++)
    {
        displayTile(player_index, i);
    }
    cout << endl;
}

void Board::displayBoard() {
    for (int i = 0; i < 3; i++) { // this loops through each player track UPDATE VALUE FOR NUM OF PLAYERS
        displayTrack(i); // displays the track for the current player
        cout << endl;    // add an extra line between the two lanes cuz original format sucked
    }
}




bool Board::movePlayer(int player_index) {
    // update and increment each player on turn according to spinner
    _player_position[player_index]++;
    
    // makes sure the player doesn't exceed the board size and doesnt have random spazms
    if (_player_position[player_index] >= _BOARD_SIZE) {
        _player_position[player_index] = _BOARD_SIZE - 1;
        return true; // works if the player meets the end of the game, doesn't work with anything other than 2 players
    }
    return false; // player hasnt reached the end, only here for debugging cuz they will reach the end 
}


int Board::getPlayerPosition(int player_index) const
{
     if (player_index >= 0 && player_index <= _player_count)
     {
         return _player_position[player_index];
     }
     return -1;
}