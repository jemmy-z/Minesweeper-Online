#include "Player.h"

Player::Player () {
    playerId = -1;
    game = new MineSweeper();
}

Player::Player (int pid) {
    playerId = pid;
    game = new MineSweeper();
}

int Player::getPlayerId () {
    return playerId;
}

void Player::setPlayerId (int pid) {
    playerId = pid;
}

MineSweeper* Player::getGame () {
    return game;
}

void Player::setGame (MineSweeper init) {
    
}