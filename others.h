#include "Player.h"
#ifndef SPLIT_H
#define SPLIT_H

//Zach Roberson and Aidan Tiruvan

//Will make sure input is an integer, everything else rejected, handles string or char input errors
int checkValid(int first, int last, int choice){
    while (true) {
        if (!(cin >> choice)){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input."<<endl;;
        }else if(choice < first || choice > last){
            cout << "Invalid input."<<endl;
        }else{
            return choice;
        }
    }
}

//Makes board look pretty
void printLines(){
    cout<<"------------------------------------------------------------------------------------------------------------------------------------";
    cout<<"------------------------"<<endl;
}

#endif