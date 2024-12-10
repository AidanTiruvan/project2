#include "Board.h"
#include "split.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>

#define RED "\033[48;2;230;10;10m"
#define GREEN "\033[48;2;34;139;34m"
#define BLUE "\033[48;2;10;10;230m"
#define PINK "\033[48;2;255;105;180m"
#define BROWN "\033[48;2;139;69;19m"
#define PURPLE "\033[48;2;128;0;128m"
#define ORANGE "\033[48;2;230;115;0m"
#define GREY "\033[48;2;128;128;128m"
#define RESET "\033[0m"

// Zach Roberson and Aidan Tiruvan

using namespace std;

// default constructor for single-player board
Board::Board() {
    _player_count = 1;
    _player_positions[0] = 0;

    // initialize the board for a single player
    initializeBoard();
}

// constructor for custom number of players
Board::Board(int player_count) {
    importFiles(); // if any import fails, will exit

    if (player_count > _MAX_PLAYERS) { // makes sure players don't exceed max
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    // character selection
    for (int i = 0; i < _player_count; i++) {
        cout << "Player " << i + 1 << ", select your character." << endl;

        // character options 
        for (size_t j = 0; j < _characterVec.size(); j++) {
            string arr[6];
            int arrSize = 6;
            if (split(_characterVec[j], '|', arr, arrSize) != -1) {
                // formatted output of character options
                cout << "(" << j + 1 << ") " << arr[0]
                     << ", Age: " << arr[1]
                     << ", Strength: " << arr[2]
                     << ", Stamina: " << arr[3]
                     << ", Wisdom: " << arr[4]
                     << ", Pride Points: " << arr[5] << endl;
            }
        }

        // select the character
        int choice = 0;
        choice = checkValid(1, static_cast<int>(_characterVec.size()), choice);
        printLines();

        string arr[6];
        int arrSize = 6;
        split(_characterVec[choice - 1], '|', arr, arrSize);
        // parse and initialize the player object from the selected character
        players[i] = Player(arr[0], stoi(arr[2]), stoi(arr[3]), stoi(arr[4]), stoi(arr[1]), stoi(arr[5]));
        _characterVec.erase(_characterVec.begin() + choice - 1);

        // select path
        string path_type; // have it as string for error handling here, weird bug when its an int or char
        cout << "Player " << i + 1 << ", please select your path. Pride Lands or Cub Training." << endl;
        cout << "1: Pride Lands" << endl;
        cout << "2: Cub Training" << endl;
        cin >> path_type;
        while (path_type != "1" && path_type != "2") {
            cout << "Invalid choice." << endl;
            cin >> path_type;
        }
        players[i].setPath(path_type);
        printLines();

        // if the player chooses the cub training they should select advisor
        if (players[i].getPath() == "T") {
            cout << "Player " << i + 1 << " - ";
            players[i].printAdvisors(_advisorVec); // displays a numbered list of advisors
            int advisorChoice = 0;
            advisorChoice = checkValid(1, static_cast<int>(_advisorVec.size()), advisorChoice);
            players[i].setAdvisor(_advisorVec, advisorChoice);
            _advisorVec.erase(_advisorVec.begin() + advisorChoice - 1); // remove the advisor properly
            printLines();
        }
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
    initializeTiles(); // now sets up both pride and cub boards with no player index
}

// initializes tiles for both paths
void Board::initializeTiles() { // signature changed to no arguments
    // Initialize Pride Lands tiles
    int green_count_pride = 0; // Track the number of green tiles for Pride Lands
    for (int i = 0; i < _BOARD_SIZE; i++) { // filling _prideTiles
        if (i == 0) { // set the first tile as Grey for starting point
            _prideTiles[i].setColor('Y');
        } else if (i == _BOARD_SIZE - 1) { // set the last tile as Orange for pride roock
            _prideTiles[i].setColor('O');
        } else {
            // assigns G with a certain probability or count else assign other colors based on path type P
            if (green_count_pride < 30 && (rand() % (_BOARD_SIZE - i) <= 30 - green_count_pride)) {
                _prideTiles[i].setColor('G');
                green_count_pride++;
            } else {
                int color_choice = rand() % 100;
                if (color_choice < 30) _prideTiles[i].setColor('P');
                else if (color_choice < 60) _prideTiles[i].setColor('B');
                else if (color_choice < 75) _prideTiles[i].setColor('R');
                else if (color_choice < 90) _prideTiles[i].setColor('N');
                else _prideTiles[i].setColor('U');
            }
        }
    }

    // initialize Cub Training tiles
    int green_count_cub = 0; // tracks the number of green tiles for Cub Training
    for (int i = 0; i < _BOARD_SIZE; i++) { // filling _cubTiles
        if (i == 0) { // set the first tile as grey for a starting point
            _cubTiles[i].setColor('Y');
        } else if (i == _BOARD_SIZE - 1) { // sets the last tile as orange for pride rock
            _cubTiles[i].setColor('O');
        } else {
            //assign G with a certain probability or count or else assign other colors based on path type t
            if (green_count_cub < 30 && (rand() % (_BOARD_SIZE - i) <= 30 - green_count_cub)) {
                _cubTiles[i].setColor('G');
                green_count_cub++;
            } else {
                int color_choice = rand() % 100;
                if (color_choice < 10) _cubTiles[i].setColor('P');
                else if (color_choice < 35) _cubTiles[i].setColor('B');
                else if (color_choice < 50) _cubTiles[i].setColor('R');
                else if (color_choice < 70) _cubTiles[i].setColor('N');
                else _cubTiles[i].setColor('U');
            }
        }
    }
}

// displays a single tile with color and player presence
void Board::displayTile(char pathType, int pos) { // updated signature to displayTile(char pathType, int pos)
    string color = "";
    bool anyPlayerOnTile = false; // track if any player is on this tile
    string playersOnTile = ""; // to list multiple players

    // determine tile color based on board type
    char tileColor;
    if (pathType == 'P') {
        tileColor = _prideTiles[pos].getColor();
    } else {
        tileColor = _cubTiles[pos].getColor();
    }

    //assign color codes based on tile color
    switch (tileColor) { // no change in logic just using tilecolor
        case 'R': color = RED; break;
        case 'G': color = GREEN; break;
        case 'B': color = BLUE; break;
        case 'P': color = PINK; break;
        case 'N': color = BROWN; break;
        case 'U': color = PURPLE; break;
        case 'O': color = ORANGE; break;
        case 'Y': color = GREY; break;
    }

    // check which players are on this tile for the given path
    for (int i = 0; i < _player_count; i++) { // iterate over players to find those on this tile
        if (_player_positions[i] == pos) { // if player matches tile position
            if ((pathType == 'P' && players[i].getPath() == "P") || (pathType == 'T' && players[i].getPath() == "T")) { // makes sure the player path matches board
                if (playersOnTile.empty()) {
                    playersOnTile += to_string(i + 1);
                } else {
                    playersOnTile += " & " + to_string(i + 1);
                }
                anyPlayerOnTile = true;
            }
        }
    }

    if (anyPlayerOnTile) {
        cout << color << "|" << playersOnTile << "|" << RESET;
    } else {
        cout << color << "| |" << RESET;
    }
}

// displays the track for a specific player
void Board::displayTrack(int player_index) {
    // determine player's path to display the correct board
    char pathType = (players[player_index].getPath() == "P") ? 'P' : 'T'; // path type for display

    for (int i = 0; i < _BOARD_SIZE; i++) {
        // call the new displayTile with pathType
        displayTile(pathType, i);
    }
    cout << endl;
}

// displays the entire board for all players
void Board::displayBoard() {
    // display pride lands board separately
    cout << "Pride Lands Board:" << endl; // label pride lands board
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile('P', i); // display each tile for pride lands
    }
    cout << endl;

    // display cub training board separately
    cout << "Cub Training Board:" << endl; // label cub training board
    for (int i = 0; i < _BOARD_SIZE; i++) {
        displayTile('T', i); // display each tile for cub training
    }
    cout << endl;
}

// moves a player forward and applies tile effects
bool Board::movePlayer(int player_index, int spinner) {
    // Determine player's path type
    char pathType = (players[player_index].getPath() == "P") ? 'P' : 'T'; // P for Pride Lands and T for Cub Training

    // calculates a  new position
    int newPosition = _player_positions[player_index] + spinner;
    int oldPosition = _player_positions[player_index];

    //ensure new position doesnt exceed board size
    if (newPosition >= _BOARD_SIZE) {
        _player_positions[player_index] = _BOARD_SIZE - 1; // Move to final tile

        //trigger Pride Rock event
        if (pathType == 'P') {
            Tile finalTile = _prideTiles[_player_positions[player_index]];
            finalTile.prideRock();
            _prideTiles[_player_positions[player_index]] = finalTile;
        } else {
            Tile finalTile = _cubTiles[_player_positions[player_index]];
            finalTile.prideRock();
            _cubTiles[_player_positions[player_index]] = finalTile;
        }

        return true;
    }

    // update player position new
    _player_positions[player_index] = newPosition;

    //access the current tile based on path type
    Tile currentTile;
    if (pathType == 'P') {
        currentTile = _prideTiles[newPosition];
    } else {
        currentTile = _cubTiles[newPosition];
    }

    //handle tile effects based on tile color
    switch (currentTile.getColor()) {
        case 'G': { // GREEN TILE EVENTS
            duringTurnBoard();
            size_t eventChoice = rand() % _eventsVec.size(); // renamed local var to not conflict with int choice above
            string eventsArray[9];
            split(_eventsVec[eventChoice], '|', eventsArray, 9);
            while (stoi(eventsArray[1]) != (pathType == 'T' ? 0 : 1) &&
                   stoi(eventsArray[1]) != 0 &&
                   split(_eventsVec[eventChoice], '|', eventsArray, 9) == -1) { 
                eventChoice = rand() % _eventsVec.size();
                split(_eventsVec[eventChoice], '|', eventsArray, 9);
            }
            if (pathType == 'P') {
                // assuming grassLand returns the pride points to add
                int pridePoints = _prideTiles[newPosition].grassLand(eventsArray, players[player_index].getAdvisorNum(), players[player_index].getAge());
                players[player_index].addPride(pridePoints);
            } else {
                // assuming grassLand returns the pride points to add
                int pridePoints = _cubTiles[newPosition].grassLand(eventsArray, players[player_index].getAdvisorNum(), players[player_index].getAge());
                players[player_index].addPride(pridePoints);
            }
            break;
        }
        case 'B': { // OASIS TILE
            duringTurnBoard();
            int strengthChange, staminaChange, wisdomChange;
            if (pathType == 'P') {
                tie(strengthChange, staminaChange, wisdomChange) = _prideTiles[newPosition].oasisTile();
            } else {
                tie(strengthChange, staminaChange, wisdomChange) = _cubTiles[newPosition].oasisTile();
            }
            players[player_index].addStrength(strengthChange);
            players[player_index].addStamina(staminaChange);
            players[player_index].addWisdom(wisdomChange);
            break;
        }
        case 'P': { // ADVISOR TILE
            duringTurnBoard();
            if (players[player_index].getAdvisor() != "") {
                cout << "Would you like to switch your advisor? (1 = Yes | 2 = No)" << endl;
                int choice = checkValid(1, 2, 0);
                if (choice == 1) {
                    players[player_index].printAdvisors(_advisorVec);
                    int advChoice = checkValid(1, static_cast<int>(_advisorVec.size()), 0);
                    string advSwitch = players[player_index].getAdvisor();
                    players[player_index].setAdvisor(_advisorVec, advChoice);
                    _advisorVec.erase(_advisorVec.begin() + advChoice - 1);
                    _advisorVec.push_back(advSwitch);
                } else if (choice == 2) {
                    cout << "Your advisor thanks you for staying with them." << endl;
                }
            } else {
                cout << "Player " << player_index + 1 << ", please select your advisor." << endl;
                players[player_index].printAdvisors(_advisorVec);
                int advisorChoice = 0;
                advisorChoice = checkValid(1, static_cast<int>(_advisorVec.size()), advisorChoice);
                players[player_index].setAdvisor(_advisorVec, advisorChoice);
                _advisorVec.erase(_advisorVec.begin() + advisorChoice - 1);
            }
            break;
        }
        case 'R': { // GRAVEYARD TILE
            duringTurnBoard();
            int strengthChange, staminaChange, wisdomChange;
            if (pathType == 'P') {
                tie(strengthChange, staminaChange, wisdomChange) = _prideTiles[newPosition].graveYard();
            } else {
                tie(strengthChange, staminaChange, wisdomChange) = _cubTiles[newPosition].graveYard();
            }
            players[player_index].addStrength(strengthChange);
            players[player_index].addStamina(staminaChange);
            players[player_index].addWisdom(wisdomChange);
            // move player index back 10
            _player_positions[player_index] = newPosition - 10;
            if (_player_positions[player_index] < 0) {
                _player_positions[player_index] = 0;
            }
            break;
        }
        case 'N': { // HYENA TILE
            duringTurnBoard();
            int staminaChange;
            if (pathType == 'P') {
                staminaChange = _prideTiles[newPosition].hyenaTile();
            } else {
                staminaChange = _cubTiles[newPosition].hyenaTile();
            }
            players[player_index].addStamina(staminaChange);
            // move to previous index
            _player_positions[player_index] = oldPosition;
            break;
        }
        case 'U': { // RIDDLE TILE
            duringTurnBoard();
            size_t rChoice = rand() % _riddleVec.size(); // renamed variable to avoid shadowing choice
            string riddlesArray[2];
            split(_riddleVec[rChoice], '|', riddlesArray, 2);
            while (split(_riddleVec[rChoice], '|', riddlesArray, 2) == -1) {
                rChoice = rand() % _riddleVec.size();
                split(_riddleVec[rChoice], '|', riddlesArray, 2);
            }
            int wisdomChange;
            if (pathType == 'P') {
                wisdomChange = _prideTiles[newPosition].riddleTile(riddlesArray);
            } else {
                wisdomChange = _cubTiles[newPosition].riddleTile(riddlesArray);
            }
            players[player_index].addWisdom(wisdomChange);
            break;
        }
        default:
            break;
    }

    // checking to make sure players stats aren't negative
    if (players[player_index].getStrength() < 0) {
        players[player_index].setStrength(0);
    }
    if (players[player_index].getStamina() < 0) {
        players[player_index].setStamina(0);
    }
    if (players[player_index].getWisdom() < 0) {
        players[player_index].setWisdom(0);
    }

    return false; // the game continues on
}

// checks if a player is on a specific tile for a given path type
bool Board::isPlayerOnTile(int player_index, char pathType, int pos) { // implementation now matches declaration
    // checks if the player is on the specified pathType board at the given position
    if ((pathType == 'P' && players[player_index].getPath() == "P") ||
        (pathType == 'T' && players[player_index].getPath() == "T")) { // ensure path type matches player's path
        return (_player_positions[player_index] == pos);
    }
    return false; // return false if path type does not match player's path
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

void Board::displayStats(int index) {
    players[index].printStats();
}

void Board::playerPride(int index) {
    cout << "Player " << index + 1 << "'s Pride Points: " << players[index].getPride() << endl;
}

// Imports
void Board::importFiles() {
    ifstream characters("chars.txt");
    ifstream advisors("advisors.txt");
    ifstream riddles("riddles.txt");
    ifstream gameRules("game_rules.txt");
    ifstream events("random_events.txt");
    if (characters.fail() || advisors.fail() || riddles.fail() || gameRules.fail() || events.fail()) {
        cout << "One or more files failed to open, quitting program." << endl;
        exit(0);
    } else {
        string input;
        string worthless; //will be used to get rid of lines we don't want players to see
        getline(characters, worthless);
        while (!characters.eof()) {
            getline(characters, input);
            if (!input.empty()) {
                _characterVec.push_back(input);
            }
        }
        while (!advisors.eof()) {
            getline(advisors, input);
            if (!input.empty()) {
                _advisorVec.push_back(input);
            }
        }
        getline(riddles, worthless);
        while (!riddles.eof()) {
            getline(riddles, input);
            if (!input.empty()) {
                _riddleVec.push_back(input);
            }
        }
        while (!gameRules.eof()) {
            getline(gameRules, input);
            if (!input.empty()) {
                _ruleVec.push_back(input);
            }
        }
        for(int i = 0; i < 3; i++){
            getline(events, worthless);
        }
        while (!events.eof()) {
            getline(events, input);
            if (!input.empty()) {
                _eventsVec.push_back(input);
            }
        }
        // removes #._ from beginning of advisorVec
        for (int j = 0; j < _advisorVec.size(); j++) { // cast size to int for loop
            _advisorVec[j].erase(0, 3);
        }

        characters.close();
        advisors.close();
        riddles.close();
        gameRules.close();
        events.close();
    }
}

const int Board::getBoardSize()
{
    return _BOARD_SIZE;
}

int Board::checkValid(int start, int end, int choice){
    while (true) {
        if (!(cin >> choice)){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input."<<endl;;
        } else if(choice < start || choice > end){
            cout << "Invalid input."<<endl;
        } else{
            return choice;
        }
    }
}

void Board::printLines(){
    cout << "------------------------------------------------------------------------------------------------------------------------------------";
    cout << "------------------------" << endl;
}

void Board::duringTurnBoard(){
    printLines();
    displayBoard();
    printLines();
}

void Board::displayRules(){
    for(size_t i = 0; i < _ruleVec.size(); i++){
        cout << _ruleVec[i] << endl;
    }
}
