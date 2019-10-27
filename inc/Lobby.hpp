#ifndef LOBBY_H
#define LOBBY_H

#include <Player.h>
#include <MineSweeper.hpp>
#include <stdlib.h>

class lobby{
private:
    std::vector<Player> playerList;
    std::vector<std::tuple<int, int>> mineLoc;
    MineSweeper initBoard;

    int MAX_PLAYERS = 1;
    int BOARD_N = 3;
    int BOARD_M = 3;
    int NUM_MINES = 1;
    bool joinable = true;
    
    void genMines();

public:
    lobby();
    void startLobby();
    minesweeper::json joinLobby(Player p);
    Player getPlayerFromID(int PID);
    int startable();
};

#endif