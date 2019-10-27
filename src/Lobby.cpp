#include <Lobby.hpp>

lobby::lobby(){
    genMines();
}

void lobby::startLobby(){
    for(Player p : playerList){
        //Set the local player board
        p.getGame().setGame(BOARD_N, BOARD_M, mineLoc);
        
        //Allow players to grab their boards
        p.getGame().setGrabable(true);
    }
}

minesweeper::json lobby::joinLobby(Player p){
    minesweeper::json result;
    if(joinable){
        playerList.push_back(p);
        if(playerList.size() >= MAX_PLAYERS){
            joinable = false;
        }
        result["success"] = 1;
        return result;
    }
    result["success"] = 0;
    return result;
}

void lobby::genMines(){
    for(int i = 0 ; i < NUM_MINES ; i++){
        int r = std::rand() % BOARD_N;
        int c = std::rand() % BOARD_M;
        mineLoc.push_back(std::make_tuple(r,c));
    }
}

Player lobby::getPlayerFromID(int PID){
    for(Player p: playerList){
        if(p.getPlayerId() == PID){
            return p;
        }
    }
}

int lobby::startable(){
    return !joinable;
}