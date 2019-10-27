#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <MineSweeper.hpp>

class Player 
{
private:
    int playerId;
    MineSweeper *game;
public:
    Player();
    Player(int pid);
    int getPlayerId();
    MineSweeper* getGame();
    void setPlayerId(int pid);
    void setGame(MineSweeper init);
};

#endif