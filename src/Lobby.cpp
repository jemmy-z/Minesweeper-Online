#include <Lobby.hpp>
#include <random>

lobby::lobby(){
    genMines();
}

void lobby::startLobby(){
    for(Player p : playerList){
        //Set the local player board
        p.getGame()->setGame(BOARD_N, BOARD_M, mineLoc);
        
        //Allow players to grab their boards
        p.getGame()->setGrabable(true);
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
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> rowGen(0, BOARD_N-1);
    std::uniform_int_distribution<std::mt19937::result_type> colGen(0, BOARD_M-1);

    while(mineLoc.size() < NUM_MINES){
        int r = rowGen(rng);
        int c = colGen(rng);
        std::tuple<int, int> location = std::make_tuple(r,c);
        if(std::find(mineLoc.begin(), mineLoc.end(), location) == mineLoc.end()){
            mineLoc.push_back(std::make_tuple(r,c));
        }
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

std::tuple<int, int> lobby::getDimensions(){
    return std::make_tuple(BOARD_N,BOARD_M);
}

int lobby::getNumMines(){
    return NUM_MINES;
}

bool lobby::lobbyEnd(){
    return playerList.size() == 1 && playerList[0].getGame()->getMinesLeft() == 0;
}

void lobby::setGID(int gid){
    this->gid = gid;
}

int lobby::getGID(){
    return gid;
}

bool lobby::playerInLobby(int pid){
    for(Player p: playerList){
        if(p.getPlayerId() == pid){
            return true;
        }
    }
    return false;
}

void lobby::sendMessage(int pid, std::string msg){
    chatRoom.push_back(std::make_tuple(pid,msg));
}

std::vector<std::tuple<int, std::string>> lobby::getChat(){
    return chatRoom;
}