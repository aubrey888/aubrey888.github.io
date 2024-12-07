#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include<array>
#include "candystore.h"


using namespace std;

struct ThePlayer //the character chosen.
{
    string name;
    int stamina;
    double gold;
    //vector<string> candies;
    //string candies[9];
    CandyStore::CandyArray candies;
};

struct activeParticipant // the real life participant
{
    string name;
    ThePlayer character;
    int board_position;
    int skip_turns;
    bool robersrepel;
};

class Player
{
private:
    string _storename;
    int _candy_count;

    string _player_name;
    int _player_count;

    int _player_stamina;
    int _player_skip_count;
    bool _player_can_move;
    

public:
    Player();
    Player(string player_name);

    int setPlayerStamina(int);
    int getPlayerStamina();

    int spendPlayerGold(int);
    int getPlayerGold();

    vector<activeParticipant> activeParticipants;

    vector<string> splitString(const string& input, char delimiter);

    //void printCharacters(vector<ThePlayer>); // moved this to boardDriver.cpp
    vector<ThePlayer> getCharactersFromFile();

    //remove chosen characters and add to active player list.
    vector<ThePlayer> removeCharactersFromVector(vector<ThePlayer>& thecharacters, string thecharactertoremove, vector<activeParticipant>& activeParticipants, string participantname);

    void removePlayerCandy(int); // index of the candy to remove.
    vector<string> getPlayerCandies();
//maybe dont need
    const vector<activeParticipant>& getActiveParticipants() const {
        cout << "getting an empty arrsy?" << endl;
        cout << activeParticipants.size() << endl;
        return activeParticipants;
    }
//maybe dont need
    void setActiveParticipants(const vector<activeParticipant>& participants) {
        activeParticipants = participants;
    }




};

#endif
