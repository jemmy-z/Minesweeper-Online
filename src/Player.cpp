#include "Player.h"

Player::Player () {
    playerId = -1;
    boardId = "";
}

Player::Player (int pid, int bid) {
    playerId = pid;
    boardId = bid;
}

std::string Player::getPlayerId () {
    return playerId;
}

void Player::setPlayerId (int pid) {
    playerId = pid;
}

int Player::getBoardId () {
    return boardId;
}

void Player::setBoardId (int bid) {
    boardId = bid;
}