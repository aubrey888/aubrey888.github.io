#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "player.h"
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct activeParticipant;

struct Tile
{
    string color;
    string tile_type;
};


//example of an array of a struct :
class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    //int _player_position; // after get player position is able to be looked up.

public:
    Board();

    struct Card 
    {
        string color;
        bool doublefeature;
    };


    int _player_position; // Move to private once the current player can be looked up.
    void resetBoard();
    //void displayTile(int, const vector<activeParticipant>& activeParticipants);
    //void displayBoard(const vector<activeParticipant>& activeParticipants);
    void displayTile(int position, const vector<activeParticipant>& activeParticipants);
    void displayBoard(const vector<activeParticipant>& activeParticipants);


    bool setPlayerPosition(int);

    int getBoardSize() const;
    int getCandyStoreCount() const;
    int getPlayerPosition() const;
    int getCandyStoreIndex(int);

    bool addCandyStore(int);
    bool isPositionCandyStore(int); 

    bool movePlayer(int tile_to_move_forward);

    int drawCard();
    Card cardDrawn(int currentposition, int movedspaces);
};

#endif