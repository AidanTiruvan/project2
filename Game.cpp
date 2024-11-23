#include "Game.h"

Game::Game(int playersCount){
    while(playersCount < 2 || playersCount > 4){
    if(playersCount <= 4 && playersCount >= 2){
       _players_count = playersCount;
    }else{
        cout<<"Invalid amount. Try again: ";
        cin>>playersCount;
    }
    }
}

void Game::setPlayers(){
    Player player;
    for(int i = 0; i < _players_count; i++){
        _players.push_back(player);
    }
}

void Game::setPlayerCount(int playersCount){
    while(playersCount < 2 && playersCount > 4){
        if(playersCount <= 4 && playersCount >= 2){
            _players_count = playersCount;
        }else{
            cout<<"Invalid amount. Try again: ";
            cin>>playersCount;
        }
    }
}

void Game::setGameEnd(bool end){
    //Code for when the game is over, will signal for scoring to begin
}