#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player 
{
private:
    int playerId;
    int boardId;
public:
    Player();
    Player(int pid, int bid);
    int getPlayerId();
    int getBoardId();
    void setPlayerId(int pid);
    void setBoardId(int bid);
};

#endif