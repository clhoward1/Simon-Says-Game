#include "player.h"

Player::Player() {
    this->playerList = {};
    this->setScore(0);
    this->setHighscore(0);
}

vector<string>* Player::getPlayerList(){
    return &this->playerList;
}

void Player::setPlayerList(vector<string> list) {
    this->playerList = list;
}


int* Player::getScore() {
    return &this->score;
}

void Player::setScore(int score) {
    this->score = score;
}


int* Player::getHighscore() {
    return &this->highscore;
}

void Player::setHighscore(int highscore) {
    this->highscore = highscore;
}
