#include <Lobby.hpp>

lobby::lobby(){
    genMines();
    initBoard = MineSweeper(BOARD_N, BOARD_M, mineLoc.size());
    initBoard.setMines(mineLoc);
}

void lobby::startLobby(){

}

minesweeper::json lobby::joinLobby(Player p){
    assert(joinable);
    playerList.push_back(p);
    if(playerList.size() >= MAX_PLAYERS){
        joinable = false;
    }
}

void lobby::genMines(){
    for(int i = 0 ; i < NUM_MINES ; i++){
        int r = std::rand() % BOARD_N;
        int c = std::rand() % BOARD_M;
        mineLoc.push_back(std::make_tuple(r,c));
    }

}