#include "simon.h"
#include "player.cpp"

#include <iostream>

Simon::Simon(Player player) {

    this->gameOver = true;
    this->colorList = {};
    this->player = player;

}

// Checks the player input against what simon says
void Simon::compareLists(vector<string> playerList) {

    if (this->colorList.back() != playerList.back()) {
        this->gameOver = true;
    }

}

vector<string>* Simon::getColorList() {
    return &this->colorList;
}

void Simon::setColorList(vector<string> list) {
    this->colorList = list;
}


void Simon::setGameOver(bool state) {
    this->gameOver = state;
}

bool Simon::getGameOver() {
    return this->gameOver;
}


string Simon::chooseRandomColor() {
    string chosenColor = "";

    int randomNum = rand() % 4; // random number between 0 and 3

    vector<string> colors = {"red", "green", "blue", "yellow"};

    chosenColor = colors[randomNum];

    cout << chosenColor << endl;

    return chosenColor;
}


int Simon::getListCounter() {
    return this->listCounter;
}

void Simon::setListCounter(int count) {
    this->listCounter = count;
}
