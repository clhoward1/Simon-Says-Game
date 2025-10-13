#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

using namespace std;

class Player {
    private:
        int score;
        int highscore;
        vector<string> playerList;
    public:
        Player();

        vector<string>* getPlayerList();
        void setPlayerList(vector<string> list);

        int* getScore();
        void setScore(int score);

        int* getHighscore();
        void setHighscore(int highscore);
    };

#endif // PLAYER_H
