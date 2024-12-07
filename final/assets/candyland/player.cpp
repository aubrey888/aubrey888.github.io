#include "player.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm> // for remove_if

using namespace std;

Player::Player() : _storename(""), _candy_count(0)
{
}

Player::Player(string player_name) : _player_name(player_name), _player_count(0)
{
}


vector<ThePlayer> Player::getCharactersFromFile()
{
    vector<ThePlayer> characters;

    ifstream inputFile("text_files/characters.txt");
    if (!inputFile.is_open())
    {
        cerr << "Failed to open the file 'characters.txt'" << endl;
        return characters; 
    }

    // Skip the first line (header)
    string header;
    getline(inputFile, header);

    string line;
    while (getline(inputFile, line))
    {
        istringstream iss(line);
        ThePlayer player;

        getline(iss, player.name, '|');
        iss >> player.stamina;

        iss.ignore(); // Ignore the delimiter '|'
        iss >> player.gold;

        // Read candies as a string
        string candiesStr;
        getline(iss, candiesStr);

        // Process candiesStr to get individual candies
        istringstream candiesStream(candiesStr);
        string candy;


/*
//when candies were added to a vector
        while (getline(candiesStream, candy, ','))
        {
            // Exclude the first character if it is the delimiter '|'
            if (!candy.empty() && candy[0] == '|')
            {
                candy = candy.substr(1);
            }
            player.candies.push_back(candy);
        }
*/


while (getline(candiesStream, candy, ','))
{
    // Exclude the first character if it is the delimiter '|'
    if (!candy.empty() && candy[0] == '|')
    {
        candy = candy.substr(1);
    }

    // Find an empty slot in the array and add the candy
    for (int i = 0; i < 9; ++i)
    {
        if (player.candies[i].empty())
        {
            player.candies[i] = candy;
            break; // Exit the loop after adding the candy
        }
    }
}


        characters.push_back(player);
    }

    inputFile.close();
    return characters;
}

vector<string> Player::splitString(const string& input, char delimiter)
{
    vector<string> result;
    stringstream ss(input);
    string token;
    while (getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}


vector<ThePlayer> Player::removeCharactersFromVector(vector<ThePlayer>& thecharacters, string thecharactertoremove, vector<activeParticipant>& activeParticipants, string participantname)
{
    activeParticipant participant;

    auto removedPlayer = find_if(thecharacters.begin(), thecharacters.end(),
                                      [thecharactertoremove](const ThePlayer& player) {
                                          return player.name == thecharactertoremove;
                                      });

    if (removedPlayer != thecharacters.end())
    {
        activeParticipant participant;
        participant.name = participantname;
        participant.character = *removedPlayer;
        participant.board_position = 0; // Initialize with a default position
        participant.skip_turns = 0;     // Initialize with no skipped turns
        participant.robersrepel = false;

        activeParticipants.push_back(participant);

        // Erase the moved element from thecharacters vector
        thecharacters.erase(removedPlayer);
    }

    return thecharacters;
}



void Player::removePlayerCandy(int index)
{
    // Implementation for removing player candy by index goes here
}

vector<string> Player::getPlayerCandies()
{
    // Implementation for getting player candies goes here
    return vector<string>();
}
