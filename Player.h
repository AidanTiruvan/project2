#include <iostream>
#include <vector>
using namespace std;
#ifndef PLAYER_H
#define PLAYER_H
class Player{
    private:
        string _name;
        string _advisor;
        int _strength;
        int _stamina;
        int _wisdom;
        int _pride_points; //money equivalent
        int _age;
        char _path; //Path = 'p' for pridelands, 't' for train cub
    public:
        //Default constructor, empty name, 100 for each value, pride 0, age 1
        Player();
        //name, strength, stamina, wisdom (all between 100 - 1000), age (1 - 20) Should default to lowest if invalid
        Player(string, int, int, int, int);
        
        //Getters

        //return name 
        string getName();
        //return strength
        int getStrength();
        //return stamina
        int getStamina();
        //return wisdsom
        int getWisdom();
        //get pride points
        int getPride();
        //get age
        int getAge();
        //get path
        char getPath();
        //get advisor
        string getAdvisor();
        

        //Setters

        //change name
        void setName(string);
        //set strength
        void setStrength(int);
        //Add Strength
        void addStrength(int);
        //Subtract Strength
        void subStrength(int);
        //set stamina
        void setStamina(int);
        //Add stamina
        void addStamina(int);
        //Subtract stamina
        void subStamina(int);
        //set wisdom
        void setWisdom(int);
        //add wisdom
        void addWisdom(int);
        //Subtract wisdom
        void subWisdom(int);
        //set pride points
        void setPride(int);
        //set age
        void setAge(int);
        //set path
        void setPath(char);
        //set advisor
        void setAdvisor(vector<string> advisors, int);

        //Others

        //train cub, set values of strength stamina and wisdom to parameters, decrease pride by 5000
        void trainCub(int, int, int);
        //skip training, increase pride by 5000, decrease strength by 2k, stamina 1k, widsom 2k
        void toPrideLands();
        //print stats
        void printStats();
        //show advisors
        void printAdvisors(vector<string>);

};

#endif