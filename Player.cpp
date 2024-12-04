#include "Player.h"

//Constructors

Player::Player(){
    _name = "";
    _strength = 100;
    _stamina = 100;
    _wisdom = 100;
    _age = 1;
    _pride_points = 0;
}

Player::Player(string name, int strength, int stamina, int wisdom, int age){
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
    _pride_points = 0;
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

char Player::getPath(){
    return _path;
}

string Player::getAdvisor(){
    return _advisor;
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
    //Will want to include add and subtract for pride points
}

void Player::setAge(int age){
    if(age >= 1 && age <= 20){
        _age = age;
    }else{
        _age = 1;
    }
}

void Player::setPath(char choice) {
    while (true) {
        if (choice == 'P') {
            _path = 'P';
            break;
        } else if (choice == 'T') {
            _path = 'T';
            break;
        }
        cout << "Invalid Choice. Please enter again: ";
        cin>>choice;
    }
}


void Player::setAdvisor(vector<string> advisors, int choice){ //COULD RETURN AN INDEX VALUE TO REMOVE THAT VALUE FROM THE ORIGINAL VECTOR
    _advisor = advisors[choice - 1];
}

//Others

void Player::printAdvisors(vector<string> advisors){
    cout<<"Pick your advisor: "<<endl;
    for(int i = 0; i < advisors.size(); i++){
        cout<<advisors[i]<<endl;
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