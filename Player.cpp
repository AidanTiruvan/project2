#include "Player.h"

//Zach Roberson and Aidan Tiruvan

//Constructors

Player::Player(){
    _name = "";
    _strength = 100;
    _stamina = 100;
    _wisdom = 100;
    _age = 1;
    _pride_points = 0;
}

Player::Player(string name, int strength, int stamina, int wisdom, int age, int pridePoints){
    //add check for valid name
    _name = name;
    if(strength >= 100 && strength <= 1000){
        _strength = strength;
    }else{
        _strength = 100;
    }
    if(stamina >= 100 && stamina <= 1000){
        _stamina = stamina;
    }else{
        _stamina = 100;
    }
    if(wisdom >= 100 && wisdom <= 1000){
        _wisdom = wisdom;
    }else{
        _wisdom = 100;
    }
    if(age >= 1 && age <= 20){
        _age = age;
    }else{
        _age = 1;
    }
    if(pridePoints < 0){
        _pride_points = 0;
    }else{
        _pride_points = pridePoints;
    }
    _advisorNum = 0;
}

//Getters

string Player::getName(){
    return _name;
}

int Player::getStrength(){
    return _strength;
}

int Player::getStamina(){
    return _stamina;
}

int Player::getWisdom(){
    return _wisdom;
}

int Player::getPride(){
    return _pride_points;
}

int Player::getAge(){
    return _age;
}

string Player::getPath(){
    return _path;
}

int Player::getPathNum(){
    return _path_num;
}

string Player::getAdvisor(){
    return _advisor;
}

int Player::getAdvisorNum(){
    return _advisorNum;
}

//Setters

void Player::setName(string name){
    //Add check
    _name = name;
}

    //Strength Stuff

void Player::setStrength(int strength){
    if(strength >= 100 && strength <= 1000){
        _strength = strength;
    }else{
        _strength = 100;
    }
}

void Player::addStrength(int strength){
    _strength = _strength + strength;
}

void Player::subStrength(int strength){
    if(_strength - strength < 0){
        _strength = 0;
    }else{
        _strength = _strength - strength;
    }
}

    //Stamina Stuff

void Player::setStamina(int stamina){
    if(stamina >= 100 && stamina <= 1000){
        _stamina = stamina;
    }else{
        _stamina = 100;
    }
}

void Player::addStamina(int stamina){
    _stamina = _stamina + stamina;
}

void Player::subStamina(int stamina){
    if(_stamina - stamina < 0){
        _stamina = 0;
    }else{
        _stamina = _stamina - stamina;
    }
}

    //Wisdom Stuff

void Player::setWisdom(int wisdom){
    if(wisdom >= 100 && wisdom <= 1000){
        _wisdom = wisdom;
    }else{
        _wisdom = 100;
    }
}

void Player::addWisdom(int wisdom){
    _wisdom = _wisdom + wisdom;
}

void Player::subWisdom(int wisdom){
    if(_wisdom - wisdom < 0){
        _wisdom = 0;
    }else{
        _wisdom = _wisdom - wisdom;
    }
}

void Player::setPride(int pridePoints){
    _pride_points = pridePoints;
}

void Player::addPride(int prideChange){
    _pride_points += prideChange;
}

void Player::setAge(int age){
    if(age >= 1 && age <= 20){
        _age = age;
    }else{
        _age = 1;
    }
}

//Picks path and provides bonuses from workbook
void Player::setPath(string choice) {
        if (choice == "1") {
            _path = "P";
            _path_num = 1;
            addPride(2500);
            addStrength(200);
            addStamina(200);
            addWisdom(200);
        } else if (choice == "2") {
            _path = "T";
            _path_num = 0;
            addPride(-5000);
            addStrength(500);
            addStamina(500);
            addWisdom(1000);
    }
}

//Sets advisor num for use in events
void Player::setAdvisor(vector<string> advisors, int choice){
    string name;
    _advisor = advisors[choice - 1];
    name = _advisor.substr(0, _advisor.find(' '));
    if(name == "Rafiki"){
        _advisorNum = 1;
    }else if(name == "Nala"){
        _advisorNum = 2;
    }else if(name == "Sarabi"){
        _advisorNum = 3;
    }else if(name == "Zazu"){
        _advisorNum = 4;
    }else if(name == "Sarafina"){
        _advisorNum = 5;
    }
}

//Others

void Player::printAdvisors(vector<string> advisors){
    cout<<"Pick your advisor: "<<endl;
    for(int i = 0; i < advisors.size(); i++){
        cout<<i+1<<". "<<advisors[i]<<endl;
    }
}
void Player::trainCub(int strength, int stamina, int wisdom){
    addStrength(strength);
    addStamina(stamina);
    addWisdom(wisdom);
    _pride_points -= 5000;
    _path = 'T';
}

void Player::toPrideLands(){
    subStrength(2000);
    subStamina(1000);
    subWisdom(2000);
    _pride_points += 5000;
    _path = 'P';
}


void Player::printStats(){
    //All work to make sure lines match up with variable length variables
    string nameLine = "--- " + _name + ", Age " + to_string(_age);
    string strengthLine = "--- Strength: " + to_string(_strength);
    string staminaLine = "--- Stamina: " + to_string(_stamina);
    string wisdomLine = "--- Wisdom: " + to_string(_wisdom);
    string ageLine = "--- Age: " + to_string(_age);
    string prideLine = "--- Pride Points: " + to_string(_pride_points);
    int nameLength = 28 - nameLine.length();
    int strengthLength = 28 - strengthLine.length();
    int staminaLength  = 28 - staminaLine.length();
    int wisdomLength = 28 - wisdomLine.length();
    int ageLength = 28 - ageLine.length();
    int prideLength = 28 - prideLine.length();

    cout<<"-------------------------------"<<endl;
    cout<<"|         Player Stats        |"<<endl;
    cout<<"|-----------------------------|"<<endl;
    cout<<"|-| " <<_name<<", Age "<<_age;
    for(int i = 0; i < nameLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"|-| Strength: "<<_strength;
    for(int i = 0; i < strengthLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"|-| Stamina: "<<_stamina;
    for(int i = 0; i < staminaLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"|-| Wisdom: "<<_wisdom;
    for(int i = 0; i < wisdomLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"|-| Age: "<<_age;
    for(int i = 0; i < ageLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"|-| Pride Points: "<<_pride_points;
    for(int i = 0; i < prideLength; i++){
        cout<<" ";
    }
    cout<<"|-|"<<endl;
    cout<<"-------------------------------"<<endl;
}

//Final computation for end of game
int Player::finalStats(){
    int finalPride = _pride_points;
    finalPride += (_strength / 100) * 1000;
    finalPride += (_stamina / 100) * 1000;
    finalPride += (_wisdom / 100) * 1000;
    return finalPride;
}

//Lets player see stats before end of game converted to pride points
void Player::visualizeStats(){
    int fakePride = _pride_points;
    int fakeStrength = _strength;
    int fakeStamina = _stamina;
    int fakeWisdom = _wisdom;
    while(fakeStrength > 99){
        fakeStrength = fakeStrength - 100;
        fakePride = fakePride + 1000;
    }
    while(fakeStamina > 99){
        fakeStamina = fakeStamina - 100;
        fakePride = fakePride + 1000;
    }
    while(fakeWisdom > 99){
        fakeWisdom = fakeWisdom - 100;
        fakePride = fakePride + 1000;
    }
    cout<<"Visualized Pride Points: "<<fakePride<<endl;
}