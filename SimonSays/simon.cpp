#include "simon.h"
#include "player.cpp"

#include <iostream>

Simon::Simon() {

    this->gameOver = true;
    this->colorList = {};

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


int Simon::getListCounter() {
    return this->listCounter;
}

void Simon::setListCounter(int count) {
    this->listCounter = count;
}


// chooses one of the 4 colors
string Simon::chooseRandomColor() {
    string chosenColor = "";

    int randomNum = rand() % 4; // random number between 0 and 3

    vector<string> colors = {"red", "green", "blue", "yellow"};

    chosenColor = colors[randomNum];

    /* just used to show what color was selected in console
    cout << chosenColor << endl;
    */

    return chosenColor;
}
