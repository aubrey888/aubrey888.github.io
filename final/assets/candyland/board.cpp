#include "board.h"
#include "player.h"
#include <cstdlib>  // random

Board::Board()
{
    resetBoard();
}


void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;
    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular tile"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular tile"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;
}

void Board::displayTile(int position, const vector<activeParticipant>& activeParticipants)
{
    //Player player;
    //const vector<activeParticipant>& activeParticipants = player.getActiveParticipants();
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";

    //cout << "The position of the tile. " << endl;

    //cout << "Player one: " << player.activeParticipants[0].name;

    //cout << "Player active participant size : " << activeParticipants.size() << endl;
    // Check if activeParticipants vector is not empty

        if (position > 0) {
            bool foundcharacter = false;
        // Display information for each active participant 
            for (const auto& participant : activeParticipants) {
                    //cout << "Player: " << participant.name << " board position: " << participant.board_position << endl;
                    if (position == participant.board_position)
                    {
                        cout << participant.name;
                        foundcharacter = true;
                        continue; // leave the for loop.
                    }

            }
            if (foundcharacter == false) { //if there is not a character in that tile then print a space.
                    cout << " ";
            }
        } else {cout << " ";} //the first square.
    
    
/*
    if (position == _player_position) //was working with test 15 moves.
    {
        cout << player.activeParticipants[0].name;
    }
    else
    {
        cout << " ";
    }
*/




    cout << " " << RESET;
}

void Board::displayBoard(const vector<activeParticipant>& activeParticipants)
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i, activeParticipants);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i, activeParticipants);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i, activeParticipants);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i, activeParticipants);
        for (int j = 0; j < 23; j++)
        {
            cout << "  ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i, activeParticipants);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getCandyStoreIndex(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++) {
        if(_candy_store_position[i] == board_position ){
            return 1;
        }
    }
    return -1;
}

int Board::getPlayerPosition() const
{
    //need current position.
    return _player_position;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward)
{
    int new_player_position = tile_to_move_forward + _player_position;
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    _player_position = new_player_position;
    return true;
}




int Board::drawCard() {
    
    // Generate a random number between 1 and 5 (inclusive)
    int randomValue = rand() % 5 + 1;

    // Check if the randomValue is less than or equal to 3 (60% chance)
    if (randomValue <= 3) {
        return randomValue; // Return 1, 2, or 3
    } else {
        return randomValue + 1; // Return 4 or 5 (20% chance)
    }
}
Board::Card card;

Board::Card Board::cardDrawn(int currentposition, int movedspaces){

            //string carddrawn;
        //int currentposition = 0;

       //  cout << "Moved Spaces passed to function " << movedspaces << endl;
        
        switch (movedspaces)
        {
        case 1:
            if(currentposition % 3 == 0){
                card.color = "Minty Green";
                card.doublefeature = false;
                //return "You drew a Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
            }
            else if(currentposition % 3 == 1){
                card.color = "Bubblegum Blue";
                card.doublefeature = false;                
                //return "You drew a Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:";
            }
            else {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = false; 
                
               // return "You drew a Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";}   
            }
            break;

        case 2:
            if(currentposition % 3 == 0)
            { 
                card.color = "Bubblegum Blue";
                card.doublefeature = false;
                
                //return "You drew a Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:";}
            }

            else if(currentposition % 3 == 1)
            {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = false;
               
               // return "You drew a Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";
                
                }


            else {
                card.color = "Minty Green";
                card.doublefeature = false;

                
               // return "You drew a Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
                
                } 

            break; 


        case 3:
            if(currentposition % 3 == 0)
            {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = false;               
               // return "You drew a Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";
                
                }
            else if(currentposition % 3 == 1){

                card.color = "Minty Green";
                card.doublefeature = false;                   
                
                //return "You drew a Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
            
            }
            else {
                card.color = "Bubblegum Blue";
                card.doublefeature = false;               
               // return "You drew a Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:"
                
                }        
            break;
            
        case 4:
            if(currentposition % 3 == 0)
            {
                card.color = "Minty Green";
                card.doublefeature = true;                  
                //return "You drew a double Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
            
            }

            else if(currentposition % 3 == 1)
            {
                card.color = "Bubblegum Blue";
                card.doublefeature = true;   
               // return "You drew a double Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:";
                
                }

            else {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = true;  

               // return "You drew a double Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";
                
                }

            break;
            
        case 5:
            if(currentposition % 3 == 0)
            {
                card.color = "Bubblegum Blue";
                card.doublefeature = true;                 
                
              //  return "You drew a double Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:";
            
            }

            else if(currentposition % 3 == 1)
            {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = true;   

                // return "You drew a double Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";
            
            }
            else {
                card.color = "Minty Green";
                card.doublefeature = true;

        
               // return "You drew a double Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
                
                }  

            break;


        case 6:
            if(currentposition % 3 == 0)
            {
                card.color = "Cotton Candy Magenta";
                card.doublefeature = true;

                // return "You drew a double Cotton Candy Magenta card. Your game piece advances to magenta tile. Here is the updated trail:";
                
                }
            else if(currentposition % 3 == 1)
            
            {
                card.color = "Minty Green";
                card.doublefeature = true;               
              //  return "You drew a double Minty Green card. Your game piece advances to green tile. Here is the updated trail:";
                
                }
            else {
                card.color = "Bubblegum Blue";
                card.doublefeature = true;                
                
        //        return "You drew a double Bubblegum Blue card. Your game piece advances to blue tile. Here is the updated trail:";
                
                }

            break;
                              
        default:
            card.color = "Something is wrong.";
            card.doublefeature = false;
            
        }

        return card;

}
