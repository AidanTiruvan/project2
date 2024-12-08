#include "Board.h"
#include "split.h"
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
    importFiles();
    if (player_count > _MAX_PLAYERS) {
        _player_count = _MAX_PLAYERS;
    } else {
        _player_count = player_count;
    }

    // give each player in the Player array a path type, should be error handled by setpath
    for (int i = 0; i < _player_count; i++) {
        std::cout << "Player " << i + 1 << ", select your character." << std::endl;

        // character options 
        for (size_t j = 0; j < _characterVec.size(); j++) { // bro use size_t for unsigned shie
            std::string arr[6];
            int arrSize = 6;
            if (split(_characterVec[j], '|', arr, arrSize) != -1) {
                //formatted output of character options
                std::cout << "(" << j + 1 << ") " << arr[0]
                          << ", Age: " << arr[1]
                          << ", Strength: " << arr[2]
                          << ", Stamina: " << arr[3]
                          << ", Wisdom: " << arr[4]
                          << ", Pride Points: " << arr[5] << std::endl;
            }
        }

        // select the chharacter
        int choice = 0;
        choice = checkValid(1, static_cast<int> (_characterVec.size()), choice);
        printLines();

        std::string arr[6];
        int arrSize = 6;
        split(_characterVec[choice - 1], '|', arr, arrSize);
        //parse and initialize the player object from the selected character
        players[i] = Player(arr[0], std::stoi(arr[2]), std::stoi(arr[3]), std::stoi(arr[4]), std::stoi(arr[1]), std::stoi(arr[5]));
        _characterVec.erase(_characterVec.begin() + choice - 1);

        // select path
        string path_type;
        cout << "Player " << i + 1 << ", please select your path. Pride Lands or Cub Training." << endl;
        cout<<"1: Pride Lands"<<endl;
        cout<<"2: Cub Training"<<endl;
        cin >> path_type;
        while(path_type != "1" && path_type != "2"){
            cout<<"Invalid choice."<<endl;
            cin >> path_type;
        }
        players[i].setPath(path_type);
        printLines();

        // if the player chooses the cub training they should select advisor
        if (players[i].getPath() == "T") {
            cout << "Player " << i + 1 << " - ";
            players[i].printAdvisors(_advisorVec);
            int advisorChoice = 0;
            advisorChoice = checkValid(1, static_cast<int> (_advisorVec.size()), advisorChoice);
            players[i].setAdvisor(_advisorVec, advisorChoice);
            _advisorVec.erase(_advisorVec.begin() + advisorChoice - 1); // remove the advisor boi properly
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
    for (int i = 0; i < _player_count; i++) {
        initializeTiles(players[i].getPath(), i);
    }
}

// initializes tiles for a specific path
// COULD ALSO ADD DIFFERENT CHANCES AT DIFFERENT PARTS OF THE BOARD
void Board::initializeTiles(string pathType, int j) {
    int green_count = 0;
    Tile tile;

    for (int i = 0; i < _BOARD_SIZE; i++) {
        if (i == _BOARD_SIZE - 1) {
            // Set the last tile as Orange for "Pride Rock"
            tile.setColor('O');
        } else if (i == 0) {
            // Set the first tile as Grey for "Starting Point"
            tile.setColor('Y');
        } else if (green_count < 30 && (rand() % (_BOARD_SIZE - i) <= 30 - green_count)) {
            tile.setColor('G');
            green_count++;
        } else {
            // Assign other tile colors based on path type
            int color_choice = rand() % 100;
            if (pathType == "P") {
                if (color_choice < 30) tile.setColor('P');
                else if (color_choice < 45) tile.setColor('B');
                else if (color_choice < 60) tile.setColor('R');
                else if (color_choice < 80) tile.setColor('N');
                else tile.setColor('U');
            } else {
                if (color_choice < 10) tile.setColor('P');
                else if (color_choice < 25) tile.setColor('B');
                else if (color_choice < 55) tile.setColor('R');
                else if (color_choice < 80) tile.setColor('N');
                else tile.setColor('U');
            }
        }
        _tiles[j][i] = tile;
    }
}

// displays a single tile with color and player presence
void Board::displayTile(int player_index, int pos) {
    std::string color = "";
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
        displayTrack(i);
    }
}

// moves a player forward and applies tile effects
bool Board::movePlayer(int player_index, int spinner) {
    // calculates the final position of the player after the spin
    int newPosition = _player_positions[player_index] + spinner;
    int oldPosition = _player_positions[player_index];
    //IF NEW POSITION < 0, POSITION = 0 this is for graveyards and such
    // this is so that the player still shouldn't go farther than the board size
    if (newPosition >= _BOARD_SIZE) {
        _player_positions[player_index] = _BOARD_SIZE - 1; // if they do exceed the board size it just puts them on the final tile

        // pride rock event trigger 
        Tile finalTile = _tiles[player_index][_player_positions[player_index]];
        //auto [prideChange, staminaChange, strengthChange, wisdomChange] = finalTile.event();
        finalTile.prideRock();

        // update the player stats 
        //players[player_index].setPride(players[player_index].getPride() + prideChange);
        //players[player_index].addStamina(staminaChange);
        //players[player_index].addStrength(strengthChange);
        //players[player_index].addWisdom(wisdomChange);

        return true; //game finishes 
    }

    // update players position to the new position
    _player_positions[player_index] = newPosition;

    // trigger the regular event for the tile the player landed on
    Tile currentTile = _tiles[player_index][newPosition];
    
    //VARIABLES USED IN TILE INTERACTIONS
    int choice = 0;
    int advChoice = 0;
    string advSwitch = "";
    string riddlesArray[2];
    string eventsArray[9];

    //DIFFERENT TILES
    if(currentTile.getColor() == 'G'){ //GREEN TILE EVENTS
        duringTurnBoard();
        size_t choice = rand() % _eventsVec.size();
        split(_eventsVec[choice], '|', eventsArray, 9);
        while(stoi(eventsArray[1]) != players[player_index].getPathNum() && stoi(eventsArray[1]) != 0 
        && split(_eventsVec[choice], '|', eventsArray, 9) == -1){ //This covers different path types
            choice = rand() % _eventsVec.size();
            split(_eventsVec[choice], '|', eventsArray, 9);
        }
        players[player_index].addPride(currentTile.grassLand(eventsArray, players[player_index].getAdvisorNum(), players[player_index].getAge()));
    }else if(currentTile.getColor() == 'B'){
        duringTurnBoard();
        auto [strengthChange, staminaChange, wisdomChange] = currentTile.oasisTile();
        players[player_index].addStrength(strengthChange);
        players[player_index].addStamina(staminaChange);
        players[player_index].addWisdom(wisdomChange);
    }else if(currentTile.getColor() == 'P'){ //ADVISOR TILE
        duringTurnBoard();
        if(players[player_index].getAdvisor() != ""){
            cout<<"Would you like to swtich your advisor? (1 = Yes | 2 = No)"<<endl;
            choice = checkValid(1, 2, choice);
            if(choice == 1){
                players[player_index].printAdvisors(_advisorVec);
                advChoice = checkValid(1, static_cast<int> (_advisorVec.size()), advChoice);
                advSwitch = players[player_index].getAdvisor();
                players[player_index].setAdvisor(_advisorVec, advChoice);
                _advisorVec.erase(_advisorVec.begin() + advChoice - 1);
                _advisorVec.push_back(advSwitch);
            }else if(choice == 2){
                cout<<"Your advisor thanks you for staying with them."<<endl;
            }
        }else{
            cout << "Player " << player_index + 1 << ", please select your advisor." << endl;
            players[player_index].printAdvisors(_advisorVec);
            int advisorChoice = 0;
            advisorChoice = checkValid(1, static_cast<int> (_advisorVec.size()), advisorChoice);
            players[player_index].setAdvisor(_advisorVec, advisorChoice);
            _advisorVec.erase(_advisorVec.begin() + advisorChoice - 1);
        }
    }else if(currentTile.getColor() == 'R'){ //GRAVEYARD TILE
        duringTurnBoard();
        auto [strengthChange, staminaChange, wisdomChange] = currentTile.graveYard();
        players[player_index].addStrength(strengthChange);
        players[player_index].addStamina(staminaChange);
        players[player_index].addWisdom(wisdomChange);
        //Move player index back 10.
        _player_positions[player_index] = newPosition - 10;
        if(_player_positions[player_index] < 0){
            _player_positions[player_index] = 0;
        }
    }else if(currentTile.getColor() == 'N'){ //HYENA TILE
        duringTurnBoard();
        players[player_index].addStamina(currentTile.hyenaTile());
        //Move to previous index
        _player_positions[player_index] = oldPosition;
    }else if(currentTile.getColor() == 'U'){ //RIDDLE TILE
        duringTurnBoard();
        size_t choice = rand() % _riddleVec.size();
        split(_riddleVec[choice], '|', riddlesArray, 2);
        while(split(_riddleVec[choice], '|', riddlesArray, 2) == -1){
            choice = rand() % _riddleVec.size();
            split(_riddleVec[choice], '|', riddlesArray, 2);
        }
        int wisdomChange = currentTile.riddleTile(riddlesArray);
        players[player_index].addWisdom(wisdomChange);
    }else{
        //currentTile.prideRock();
    }
    
    //checking to make sure players stats aren't negative
    if(players[player_index].getStrength() < 0){
        players[player_index].setStrength(0);
    }
    if(players[player_index].getStamina() < 0){
        players[player_index].setStamina(0);
    }
    if(players[player_index].getWisdom() < 0){
        players[player_index].setWisdom(0);
    }

    //auto [prideChange, staminaChange, strengthChange, wisdomChange] = currentTile.event();//Should put in advisor and event vectors as parameters, and should
    //put in player[i]'s advisor name for event boosts and shit

    // update regular turn player stats
    //players[player_index].setPride(players[player_index].getPride() + prideChange);
    //players[player_index].addStamina(staminaChange);
    //players[player_index].addStrength(strengthChange);
    //players[player_index].addWisdom(wisdomChange);

    return false; // the game continues on
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

void Board::displayStats(int index) {
    players[index].printStats();
}

void Board::playerPride(int index) {
    std::cout << "Player " << index + 1 << "'s Pride Points: " << players[index].getPride() << std::endl;
}

// Imports
void Board::importFiles() {
    std::ifstream characters("chars.txt");
    std::ifstream advisors("advisors.txt");
    std::ifstream riddles("riddles.txt");
    std::ifstream gameRules("game_rules.txt");
    std::ifstream events("random_events.txt");
    if (characters.fail() || advisors.fail() || riddles.fail() || gameRules.fail() || events.fail()) {
        std::cout << "One or more files failed to open, quitting program." << std::endl;
        exit(0);
    } else {
        std::string input;
        std::string worthless; // Will be used to get rid of lines we don't want players to see
        getline(characters, worthless);
        while (!characters.eof()) {
            getline(characters, input);
            _characterVec.push_back(input);
        }
        while (!advisors.eof()) {
            getline(advisors, input);
            _advisorVec.push_back(input);
        }
        getline(riddles, worthless);
        while (!riddles.eof()) {
            getline(riddles, input);
            _riddleVec.push_back(input);
        }
        while (!gameRules.eof()) {
            getline(gameRules, input);
            _ruleVec.push_back(input);
        }
        for(int i = 0; i < 3; i++){
            getline(events, worthless);
        }
        while (!events.eof()) {
            getline(events, input);
            _eventsVec.push_back(input);
        }
        // removes #._ from beginning of advisorVec
        for (int j = 0; j < _advisorVec.size(); j++) {
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
        }else if(choice < start || choice > end){
            cout << "Invalid input."<<endl;
        }else{
            return choice;
        }
    }
}

void Board::printLines(){
    cout<<"------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"------------------------"<<endl;
}

void Board::duringTurnBoard(){
    printLines();
    displayBoard();
    printLines();
}

void Board::displayRules(){
    for(size_t i = 0; i < _ruleVec.size(); i++){
        cout<<_ruleVec[i]<<endl;
    }
}