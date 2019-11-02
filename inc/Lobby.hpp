#ifndef LOBBY_H
#define LOBBY_H

#include <Player.h>
#include <MineSweeper.hpp>
#include <stdlib.h>

class lobby{
private:
    std::vector<Player> playerList;
    std::vector<std::tuple<int, int>> mineLoc;
    std::vector<std::tuple<int, std::string>> chatRoom;
    MineSweeper initBoard;

    int MAX_PLAYERS = 1;
    int BOARD_N = 20;
    int BOARD_M = 35;
    int NUM_MINES = 140;
    int gid;
    bool joinable = true;
    
    void genMines();

public:
    lobby();
    void startLobby();
    minesweeper::json joinLobby(Player);
    Player getPlayerFromID(int);
    int startable();
    std::tuple<int, int> getDimensions();
    int getNumMines();
    bool lobbyEnd();
    void setGID(int);
    int getGID();
    bool playerInLobby(int);
    void sendMessage(int, std::string);
    std::vector<std::tuple<int, std::string>> getChat();
};

#endif