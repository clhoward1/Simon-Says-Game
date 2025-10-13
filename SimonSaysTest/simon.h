#ifndef SIMON_H
#define SIMON_H

#include "player.h"
#include <string>
#include <vector>
#include <random>

using namespace std;


class Simon {
    private:
        bool gameOver;
        vector<string> colorList;
        Player player;
        int listCounter;
    public:
        Simon(Player player);

        void compareLists(vector<string> playerList);

        vector<string>* getColorList();
        void setColorList(vector<string> list);

        bool getGameOver();
        void setGameOver(bool state);

        string chooseRandomColor();

        int getListCounter();
        void setListCounter(int count);



};

#endif // SIMON_H
