#ifndef GAMES_H
#define GAMES_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


struct Riddle {
    string question;
    string answer;
};

class Games {
private:
    string _player_name;
    vector<Riddle> riddles;
    int upperrange;
    int lowerrange;
    int randriddle;

public:
    Games();
    void playRockPaperScissors(string player_name);

    bool isWinner;
    void loadAndPlayRiddles();
    int randnumberforriddle(int lowerrange, int upperrange);
};

#endif
