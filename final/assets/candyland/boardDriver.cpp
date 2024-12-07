#include "board.h"
#include "candystore.h"
#include "player.h"
#include <cassert>
#include "menu.h"
#include "tile.h"
#include "games.h"
#include <array>
#include <algorithm>

void endPlayerStats(const activeParticipant& player) {
    cout << "Player Initial: " << player.name << endl;
    cout << "Character Name: " << player.character.name << endl;
    cout << "Stamina: " << player.character.stamina << endl;
    cout << "Gold: " << player.character.gold << endl;

    cout << "Candies: " << endl;
    for (const auto& candy : player.character.candies) {
        cout << "[" << candy << "]   ";
    }
    cout << endl << endl;
}


void printCharacters(const vector<ThePlayer> &players) {
    for (const auto &player : players) {
        cout << "Character Name: " << player.name << endl;
        cout << "Stamina: " << player.stamina << endl;
        cout << "Gold: " << player.gold << endl;
        cout << "Candies: ";


        for (const auto &candy : player.candies) {
            if( !candy.empty()) {cout << candy << ", ";}
        }


        cout << endl << endl;
    }
}

int main()
{

// GAME SETUP - SETTING UP THE BOARD :

TileClass tileclass;
    TileType boardtiles[83];
    tileclass.generateInitialTiles(boardtiles);


    // Print the generated tiles
    for (int i = 0; i < 83; ++i) {
        cout << "Tile Position: " << boardtiles[i].tile_position << ", Color: " << boardtiles[i].color + " type: " + boardtiles[i].specialtiletype + " Dropped candy: " + boardtiles[i].droppedcandy << endl;
    }

    Board board;
    //Player player;
    Games game;
    Player player;
    CandyStore candyStore; 

    //board.displayBoard();

    //random number seeder
    srand(static_cast<unsigned>(time(0)));

    //Candy red = {"red", "red candy", 10, ""};
    //Candy yellow = {"yellow", "yellow candy", 20, ""};
    ///Candy blue = {"blue", "blue candy", 30, ""};
    //Candy green = {"green", "green candy", 40, ""};

    // Create candy stores
    CandyStore c1("Winnie's store"), c2("Bunny's store"), c3("Donald's store");

    CandyStore candy_stores[] = {c1, c2, c3};

    // Set candy store locations
    //assert(board.addCandyStore(20));
    //assert(board.addCandyStore(35));
    //assert(board.addCandyStore(50));
/*
    for (int i = 0; i < board.getBoardSize(); i++) {
        board.setPlayerPosition(i);
        if (board.isPositionCandyStore(i))
        {
            board.displayBoard();
            int candy_store_idx = board.getCandyStoreIndex(i);
            candy_stores[candy_store_idx].displayCandies();
        }
    }
 */  

    

    vector<ThePlayer> thecharacters = player.getCharactersFromFile();



    //loading candies
        // Load candies from file
    vector<Candy> loadedCandies = c1.loadCandiesFromFile();
    
    // Display loaded candies
    cout << "Loaded Candies:" << endl;


    for (const Candy& candy : loadedCandies) {
        cout << "Name: " << candy.name << endl;
        cout << "Description: " << candy.description << endl;
        // ... Display other candy properties ...
        cout << endl;
    }

    string dubval = " ";
    string tilecolor;
    Board::Card thecard;  // 

    string thecardmessage;



      vector<activeParticipant> activeParticipants; // Create a vector for active participants


    cout << "Welcome to the game of Candyland!! Please enter the number of participants:" << endl;
    int participantCount;
    cin >> participantCount;

    while (participantCount <= 0) {
        cout << "Invalid input. Please enter a positive number of participants: ";
        cin.clear();
        cin >> participantCount;
    }

    //initial load from file..
    // vector<ThePlayer> thecharacters = player.getCharactersFromFile(); // thecharacters is a vector of player objects. //defined above
    thecharacters = player.getCharactersFromFile(); // thecharacters is a vector of player objects.


    // Print out the loaded players using the Player instance
    //printCharacters(thecharacters); // Later.

    // Display menu for each participant
    for (int i = 1; i <= participantCount; ++i) {
        cout << "Participant " << i << ":" << endl;

       // while (true) {
            cout << "Menu:" << endl;
            //candyland.displayMenu();
            printCharacters(thecharacters);

            //  ask participant for their name and store in activeparticipants.
            string participantname;
            cout << "Enter an initial : (or 'quit' to exit): ";
            cin.clear();
            cin >> participantname;

            if (participantname == "quit") {
                cout << "Exiting the game. Goodbye!" << endl << endl;
                exit(1);
                //break;
            }

            string chosenCharacter;

            bool keep_asking = true;
            int prefunctioncharactercount = thecharacters.size();
            int postfunctioncharactercount = thecharacters.size();

            do {      
                    
                cout << "Enter the name of the character you want to choose (or 'quit' to exit): ";
                cin.clear();
                cin >> chosenCharacter;

                if (chosenCharacter == "quit") {
                    cout << "Exiting the game. Goodbye!" << endl << endl;
                    exit(1);
                    //break;
                } else { // passing that string to the player class and returning a vactor of player objects with chosen charater removed.

                
                        prefunctioncharactercount = thecharacters.size();
                        
                        // remove this player
                            thecharacters = player.removeCharactersFromVector(thecharacters, chosenCharacter, activeParticipants, participantname);
                            postfunctioncharactercount = thecharacters.size();
                        
                    if (prefunctioncharactercount > postfunctioncharactercount){   
                        keep_asking = false;  
                    } else {
                        cout << "Please choose available character." << endl; 
                    }
                }
                //debug print to list the active participants.

                    for (const auto& participant : activeParticipants) {
                        cout << "Name: " << participant.name << endl;
                        cout << "Character Name: " << participant.character.name << endl;
                        cout << "Board Position: " << participant.board_position << endl;
                        cout << endl;
                    }
                
            
            } while (keep_asking) ;

           //the active people are now loadning from the choice. 

       // } //end of while true
    }// end of of participant count loopage to load the set up info.

//==================================


    //let the game play begin. 

//===================================


    bool wedonthaveawinner = true;
    int currentposition;
    //test
    //activeParticipants[0].skip_turns = 2;


    //test
    // activeParticipants[0].stamina = 1;
    do {
        // loop though the participants in order.
        for (int i = 0; i < activeParticipants.size(); i++) {

            //This is the start of the turnisnotover do while.
            bool turnisnotover = false;

            do {

            //check if that participant has skipped turns.

            cout << "It's " << activeParticipants[i].name << "'s turn" << endl;

            if(activeParticipants[i].skip_turns > 0){
                    //lose two turns.
                    activeParticipants[i].skip_turns--;
                    cout << endl << "Sorry " << activeParticipants[i].name << " you have to skip this turn." << endl << endl;
                    //i++;
                    continue;
            }



            cout << "Please select a menu option (1, 2 or 3):" << endl << "1. Draw card" << endl<< "2. Use Candy" << endl<< "3. Show player stats" << endl;
            int chosenoption;
            //cout << "Enter your name : (or 'quit' to exit): ";
            cin.clear();
            cin >> chosenoption;

            // option 2 and 3 do not end the player turn
            bool turnisover = false;


            if(chosenoption == 1){
                //get this player's current position
                currentposition = activeParticipants[i].board_position;

                int movedspaces = board.drawCard(); //return int with number of spaces
                thecard = board.cardDrawn(currentposition, movedspaces);  // Corrected assignment

                // cout << "debuggg color " << thecard.color << " the dubval " << thecard.doublefeature << endl;

                if (thecard.doublefeature) {
                    dubval = "double ";
                } else { dubval = " "; }
                if (thecard.color == "Cotton Candy Magenta") {
                    tilecolor = "magenta";
                } else if (thecard.color == "Minty Green") {
                    tilecolor = "green";
                } else {
                    tilecolor = "blue";
                }
                // can be overridden when marshmallow hail storm occurs.
                thecardmessage = "You drew a " + dubval + thecard.color + " card. Your game piece advances to the " + tilecolor + " tile. Here is the updated trail:";


                int proposedposition = activeParticipants[i].board_position + movedspaces;

// cout << endl << endl << "error " << activeParticipants[i].board_position + movedspaces << endl << endl;


                //Search the other players' poitions.
                bool sametile = true;
                        // Display information for each active participant

                do {
                    for ( const auto& participant : activeParticipants )
                        {
                            //cout << "Player: " << participant.name << " board position: " << participant.board_position << endl;
                            if (proposedposition == participant.board_position)
                            {
                                cout << "Landing on the same spot as " << participant.name << ". You will be moved back one place.";


                                proposedposition-- ;

                                break;
                            }
                            else
                            {
                                sametile = false;
                            }
                        }
                    
                    } 
                while(sametile);


                //CHECK IF WINNER - if they get to space 82 first
                if (proposedposition >= 82) {
//GAME END - save stats to file - print a message congratulating the player on their success

                    //Display Stats. Funciton
                    //Write to file. Function
                for (const auto& player : activeParticipants) {
                    endPlayerStats(player);
                }
                    

                    activeParticipants[i].board_position = 82; //activeParticipants[i].board_position + movedspaces;
                    board.displayBoard(activeParticipants);

                    ofstream outputFile("results.txt");
                    if (outputFile.is_open()) {
                        for (const auto& player : activeParticipants) {
                            outputFile << "Player Initial: " << player.name << endl;
                            outputFile << "Character Name: " << player.character.name << endl;
                            outputFile << "Stamina: " << player.character.stamina << endl;
                            outputFile << "Gold: " << player.character.gold << endl;

                            outputFile << "Candies: ";


                            for (const auto& candy : player.character.candies) {
                            if(!candy.empty()){ outputFile << "[" << candy << "]   ";}
                            }


                            outputFile << endl << endl;
                        }
                        outputFile.close();
                    }

                    cout << endl << endl << endl << "CONGRATULATIONS " << activeParticipants[i].name << " YOU WON WITH " << activeParticipants[i].character.name << "!! GREAT JOB!!" << endl << endl;

                    exit(1);
                } // end of the finner declaration


//testing 
//boardtiles[proposedposition].droppedcandy = "Frosty Fizz";

//// This comes after the simetile check and winner check


//CHECK THE TILE FOR A DROPPED CANDY!

if(boardtiles[proposedposition].droppedcandy != "none"){
    cout << endl << endl << "SOME ONE DROPPED A CANDY HERE!!" << endl << endl;
    cout << endl << endl << "it is a " << boardtiles[proposedposition].droppedcandy << endl << endl;
}





if (boardtiles[proposedposition].droppedcandy == "Fearsome Fudge" || boardtiles[proposedposition].droppedcandy == "Ruby Rapture")
{
    cout << endl << "You landed on a gummy candy. You will skip the next turn." << endl << endl;
// lose a turn;
activeParticipants[i].skip_turns = 1;

//  remove the candy after a player lands.
boardtiles[proposedposition].droppedcandy = "none";


}

//Sort out the 25% of the time there is a calimity of some other special schinanigans.

//cout << "The tile type: " << boardtiles[proposedposition].specialtiletype << endl;


            int tiletypeint = 4; //always set to regular tile. many more.
            if (boardtiles[proposedposition].specialtiletype == "candystore"){ tiletypeint = 1;}
            if (boardtiles[proposedposition].specialtiletype == "hiddentreasure"){ tiletypeint = 2;}
            if (boardtiles[proposedposition].specialtiletype == "specialtile"){ tiletypeint = 3;}

// for testing set the tyletypeint
//tiletypeint = 1; // force a candystore.
//tiletypeint = 2; // force a hiddentreasure.
//tiletypeint = 3; // force a specialtile.
//tiletypeint = 4; // force a regular tile.

            CandyStore::CandyArray modifiedCandies;

            char delimiter = '|';
            string costpart; 
            string namepart;
            int candycost;
            int theloadedindex;
            string gamblediscount;
            string scrambleanswer;
            int randspecialtile;
            bool getsanotherturn = false;



            int randcand; // needed for the random candies
switch (tiletypeint) {
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    //    candy store!
    //\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    //load the candy options.
    case 1: //candystore
        // sample bubble gum|20

        // modifiedcandies = candyStore.showCandyStoreMenu(activeParticipants[i].character.candies);
        modifiedCandies = candyStore.showCandyStoreMenu(activeParticipants[i].character.candies, loadedCandies);

        //find the purchased candy and split | then string to int and deduct from activeParticipants[i].character.gold.
        for (int mci = 0; mci < modifiedCandies.size(); mci++) {
            size_t pos = modifiedCandies[mci].find(delimiter);

            // see if delim exists in the string
            if (pos != string::npos) {
                costpart = modifiedCandies[mci].substr(pos + 1); // Get the part after delim for cost.
                namepart = modifiedCandies[mci].substr(0, pos);
                try {
                    candycost = stoi(costpart); // string to integer
                } catch (const invalid_argument& e) {
                    cerr << "conversion of string candy cost to integer error " << e.what() << endl;
                }
                theloadedindex = mci;
                break;
            }
        }

        /*
        chocolatier ilrcelhtacoo
        cottoncandy dotnoctynac
        */

        // another approach - only present candies that the participant can afford in candystore.cpp

        //gamble and unscramble
        cout << "The regular price is: " << candycost << endl;
        cout << "Do you want to try to unscramble a word for a discount? (y/n) ";
        cin >> gamblediscount;
        if (gamblediscount == "y") {
            cout << endl << "Please uncramble this for a 2 gold discount - dotnoctynac. If you are wrong then it cost you 3 gold." << endl << "Please enter in all lowercase letters. ";
            cin >> scrambleanswer;

            if (scrambleanswer == "cottoncandy") {
                cout << endl << "EXCELLENT!! You received a 2 gold discount!" << endl << endl;
                candycost -= 2;
            } else {
                cout << endl << "SORRY, incorrect!! You are being charged 3 gold more!" << endl << endl;
                candycost += 3;
            }
        }
        //charge the candy too the participant
        if (activeParticipants[i].character.gold - candycost < 1) {
            activeParticipants[i].character.gold = 0;
        } else {
            activeParticipants[i].character.gold = activeParticipants[i].character.gold - candycost;
        }

        modifiedCandies[theloadedindex] = namepart;

        activeParticipants[i].character.candies = modifiedCandies;

        break;



    case 2: //hiddentreasure
        cout << endl << endl << "THIS IS HIDDEN TREASURE!!" << endl << endl;
        bool awinner;
        int randhiddentreasure;
        randhiddentreasure = tileclass.tileRandomNumber(1,100,3);

        
    
        if( randhiddentreasure <= 30){ // Stamina Refill
            game.loadAndPlayRiddles();
            awinner = game.isWinner;
            if (awinner){            
                int randstamina = tileclass.tileRandomNumber(10,30,3);
                if(activeParticipants[i].character.stamina + randstamina < 100){
                    activeParticipants[i].character.stamina = activeParticipants[i].character.stamina + randstamina;
                    cout << endl << "Congratulations!! You landed on Stamina Refill and have been awarded " << randstamina << " stamina!" << endl;
                } else if(activeParticipants[i].character.stamina + randstamina > 100 && activeParticipants[i].character.stamina < 100 ) {
                        activeParticipants[i].character.stamina = 100;
                    cout << endl << "Congratulations!! You landed on Stamina Refill and have been awarded up to the maximum amount of stamina (100)!" << endl;
                } else {
                    cout << endl << "You landed on Stamina Refill but alreadu have 100 or more stamina. Noo change was made" << endl;
                }
            } //end of if riddle winer.
        } // end of Stamina Refill
        else if(randhiddentreasure > 30 && randhiddentreasure <= 40){ // Gold Windfall
            game.loadAndPlayRiddles();
            awinner = game.isWinner;
            if (awinner){
                int randgold = tileclass.tileRandomNumber(10,40,3);
                if(activeParticipants[i].character.gold + randgold < 100){
                    activeParticipants[i].character.gold = activeParticipants[i].character.gold + randgold;
                    cout << endl << "Congratulations!! You landed on Gold Windfall and have been awarded " << randgold << " gold!" << endl;
                } else if(activeParticipants[i].character.gold + randgold > 100 && activeParticipants[i].character.gold < 100 ) {
                        activeParticipants[i].character.gold = 100;
                    cout << endl << "Congratulations!! You landed on Gold Windfall and have been awarded up to the maximum amount of gold (100)!" << endl;
                } else {
                    cout << endl << "You landed on Gold Windfall but alreadu have 100 or more gold. Noo change was made" << endl;
                }
            } //end of solved riddle.

        } // end of Gold Windfall
        else if(randhiddentreasure > 40 && randhiddentreasure <= 70){ // Robber's repel
            game.loadAndPlayRiddles();
            awinner = game.isWinner;
            if (awinner){ 
                activeParticipants[i].robersrepel = true;
            }

        } // end of Robber's repel
        else{ // 30% is > 70% Candy Acquisition (30% chance): Two types of candies can be found in the treasure:

            game.loadAndPlayRiddles();
            awinner = game.isWinner;
            if (awinner){            
                int randcandtype = tileclass.tileRandomNumber(1,100,3);
                if(randcandtype <=70 ){
                        cout << endl << "You landed on Jellybean of Vigor!! You will be given stamina!!" << endl;
                        //add to the stamina
                    int randstamina = 50;
                    if(activeParticipants[i].character.stamina + randstamina < 100){
                        activeParticipants[i].character.stamina = activeParticipants[i].character.stamina + randstamina;
                        cout << endl << "Congratulations!! You have been awarded " << randstamina << " stamina!" << endl;
                    } else if(activeParticipants[i].character.stamina + randstamina > 100 && activeParticipants[i].character.stamina < 100 ) {
                            activeParticipants[i].character.stamina = 100;
                        cout << endl << "Congratulations!! You have been awarded up to the maximum amount of stamina (100)!" << endl;
                    } else {
                        cout << endl << "You alreadu have 100 or more stamina. Noo change was made" << endl;
                    }

                } else { // 30% inside Candy Acquisition Treasure Hunter's Truffle
                    int candytrufflechoice;
                    cout << "CONGRATULATIONS!! You have solved the riddle and landed on Treasure Hunter's Truffle" << endl;
                    cout << "Please choose the reward: ";
                    cout << "1. 10 Gold" << endl << "2. 10 Stamina" << endl << "Please coose the number: ";
                    cin >> candytrufflechoice;
                    if(candytrufflechoice == 1){    activeParticipants[i].character.gold = activeParticipants[i].character.gold + 10;  }
                    else {   activeParticipants[i].character.stamina = activeParticipants[i].character.stamina +  10;  }
                    

                } // end of 30% Treasure Hunter's Truffle inside Candy Acquisition
            } // end of if riddle wineer

        } //end of Candy Acquisition (30% chance): Two types of candies can be found in the treasure:
    
    
    
        break; // end of hidden terasures


    case 3: // special tile
        cout << endl << endl << "THIS IS SPECIAL TILE!!" << endl << endl;

        randspecialtile = tileclass.tileRandomNumber(1, 4, 3);

         if (randspecialtile == 1) { 
            // 1. Shortcut Tile - leap forward by four tiles
            cout << "You landed on a Shortcut Tile! Leap forward by four tiles." << endl;
            activeParticipants[i].board_position += 4;
    }
    else if (randspecialtile == 2) { 
            // 2. Ice Cream Stop Tile - draw a card again, granting an additional turn
            cout << "You landed on an Ice Cream Stop Tile! Draw a card again for an additional turn." << endl;
            // additional turn logic
            // make this player
            getsanotherturn = true; 
            
    }
    else if (randspecialtile == 3) { 
            // 3. Gumdrop Forest Tile - go back four tiles, losing random gold
            cout << "You landed on a Gumdrop Forest Tile! Go back four tiles and lose a random amount of gold (5-10)." << endl;
            int randgoldloss = tileclass.tileRandomNumber(5, 10, 3);
            activeParticipants[i].board_position -= 4;
            int newGold = activeParticipants[i].character.gold - randgoldloss;
            if (newGold < 0) {
                activeParticipants[i].character.gold = 0;
            } else {
                activeParticipants[i].character.gold = newGold;
            }
    }
    else {  
            // 4. Gingerbread House Tile - go back to the previous position & lose one immunity candy
            cout << "You landed on a Gingerbread House Tile! Go back to the previous position and lose one immunity candy." << endl;
            proposedposition = currentposition;
            // Implement logic to remove one immunity candy.
            // Bubblegum Blast, Sparkling Sapphire, Caramel Comet
            for( int playercandiesindex = 0; playercandiesindex < 9; playercandiesindex++ ){
                    if (!activeParticipants[i].character.candies[playercandiesindex].empty()) {
                        if(
                            activeParticipants[i].character.candies[playercandiesindex] == "Bubblegum Blast" || 
                            activeParticipants[i].character.candies[playercandiesindex] == "Sparkling Sapphire" ||
                            activeParticipants[i].character.candies[playercandiesindex] == "Caramel Comet"
                        
                        ){ 
                            activeParticipants[i].character.candies[playercandiesindex] = "";
                        }
                    }

            }
    }


    default: // regular tile
        cout << endl << endl << "THIS IS REGULAR TILE!!" << endl << endl;
        //set the probability 1 to 100
        int randcalamity = tileclass.tileRandomNumber(1, 100, 3);

        //cout << endl << endl << endl << randcalamity << endl << endl << endl;

// testing calamity subtypes
randcalamity = 37;

        if (randcalamity <= 5) { // Switch statement in the regular switch?
            //random setback between 2 and 5 for each character
            int randsetback = tileclass.tileRandomNumber(1, 5, 3); //three doesn't concern the modus 3 for assigning candy stores.
            thecardmessage = "ATTENTION: " + activeParticipants[i].name + " drew a " + dubval + thecard.color + " which caused a MARSHMALLOW HAIL STORM!! Everyone is set back " + to_string(randsetback) + " spaces!!";
            //loop through participants removing the number of spaces.
            for (int sbp = 0; sbp < activeParticipants.size(); sbp++) { //sbp set back participant
                if (activeParticipants[sbp].board_position - randsetback < 0) {
                    activeParticipants[sbp].board_position = 0;
                } else {
                    activeParticipants[sbp].board_position = activeParticipants[sbp].board_position - randsetback;
                }
            }
        } else if (randcalamity >= 6 && randcalamity <= 46) { // 40% of the time.

            //get another probability
            int regtilecalamity = tileclass.tileRandomNumber(1, 100, 3);
            char recovercalamity;
//testing the calamity
regtilecalamity = 40;

            if (regtilecalamity <= 30) {
                cout << endl << endl << "Oh no! Candy Bandits have swiped your gold coins!" << endl << endl;

                int randcoinrob = tileclass.tileRandomNumber(1, 10, 3); //three doesn't concern the modus 3 for assigning candy stores.
                if (activeParticipants[i].character.gold - randcoinrob < 0) {
                    activeParticipants[i].character.gold = 0;
                } else {
                    activeParticipants[i].character.gold = activeParticipants[i].character.gold - randcoinrob;
                }
            } else if (regtilecalamity > 30 && regtilecalamity <= 65) {
                cout << endl << endl << "Oh dear! You got lost in the lollipop labyrinth!" << endl << endl;

                cout << "Do you want to play Rock Paper Scissors to get out? (y/n) ";
                cin >> recovercalamity;
                if (recovercalamity == 'y') {

                   

                    game.playRockPaperScissors("Player1");

                    cout << endl << endl << game.isWinner << endl << endl;

                    if (game.isWinner) {
                        // does not lose turn

                        cout << "Congratulations! You won Rock, Paper, Scissors. You found your way back!" << endl;
                    } else {
                        // loses their turn 
                        cout << "Sorry, you lost Rock, Paper, Scissors. You remain lost in the lollipop labyrinth." << endl;

                        activeParticipants[i].skip_turns = 1;

                    }

                    // implement rock paper scissors game

                }  else {
                    cout << endl << endl << "Oops! You are stuck in a sticky taffy trap!" << endl << endl;
                    activeParticipants[i].skip_turns = 1;
                }
            }

            else if (regtilecalamity > 65 && regtilecalamity <= 80) {

                    cout << endl << endl << "Watch out! A candy avalanche has struck!" << endl << endl;

                    cout << "Do you want to play Rock Paper Scissors to get out? (y/n) ";
                    cin >> recovercalamity;
                    if (recovercalamity == 'y') {

                        //Games game; // up top now.

                        game.playRockPaperScissors("Player1");

                        cout << endl << endl << game.isWinner << endl << endl;

                        if (game.isWinner) {
                            // does not lose turn

                            cout << "Congratulations! You won Rock, Paper, Scissors. You found your way back!" << endl;
                        } else {
                            // loses their turn 
                            cout << "Sorry, you lost Rock, Paper, Scissors. You remain lost in the lollipop labyrinth." << endl;

                            activeParticipants[i].skip_turns = 1;
                            if (activeParticipants[i].character.stamina - 5 < 0) {
                                activeParticipants[i].character.stamina = 0;
                            } else {
                                activeParticipants[i].character.stamina = activeParticipants[i].character.stamina - 5;
                            }

                        }
                    }
                }
                else { 
                    cout << "Oops! You are stuck in a sticky taffy trap!" << endl; 
                    activeParticipants[i].skip_turns = 1;
                    
                }

            //cout << endl << endl << " error ######################## " << endl << regtilecalamity << endl;
        }
        break;
}

//  Menu to purchase candy - check max candy 9? 8? then present cin option and decrease gold.


//based on tiletype do stuff.

//cout << endl << endl << "if tile is a regular then anytime this reruns a 1 then shinanigans. " << tileclass.tileRandomNumber(1,4,3) << endl << endl;


//check tile index in a vector for candies left on board that have an 
//Check for dropped Candy. and execute that logic on the participant skip turn lose gold then update the tile to remove 



//sort out the percentages here and call functions in TileClass? Board? to return int for turn loss, gold spend, candy, stamina.
// 5% othe time if tile is regular then marshmallo hail everyone board position decreased by ran











//testing
//                cout << "stamina before : " << activeParticipants[i].character.stamina << endl;

//Move the participant.
                activeParticipants[i].character.stamina-- ; // decreae stamina by one.
                if(activeParticipants[i].character.stamina < 1){
                    //lose two turns.
                    activeParticipants[i].skip_turns = 2;
                }

                // end the player's move
                turnisover =  true;




//testing
                //cout << "stamina after : " << activeParticipants[i].character.stamina << endl;

                //update the player instance of the vector so it can be accessed when making the board.
                //player.activeParticipants = activeParticipants;

//testing
                    for (const auto& participant : activeParticipants) {
                        cout << "Name: " << participant.name << endl;
                        cout << "Character Name: " << participant.character.name << endl;
                        cout << "Board Position: " << participant.board_position << endl;
                        cout << endl;
                    }




                //player.setActiveParticipants(activeParticipants);

                cout << thecardmessage << endl;
                //cout << endl << endl << " error" << endl << endl;
                //cout << "The tile type even if overridden for testing: " << boardtiles[proposedposition].specialtiletype << endl;

// Move the character;

                activeParticipants[i].board_position = proposedposition;



                //display the board.
                board.displayBoard(activeParticipants);


                //if the player gets another turn set the i back by one.
                if(getsanotherturn){
                    if( i > 0 ){ i--;}
                    else { i = activeParticipants.size() - 1; }
                    getsanotherturn = false;
                }

            } //end of option one.








            else if (chosenoption == 2){

string usecandyName;
int chosenopi;

                cout << endl << "You picked use candy." << endl;

                cout << "Which of your your candies would you like to use?";

// Display user's candies.
for (int ca = 0; ca < 9; ca++) {
    if (!activeParticipants[i].character.candies[ca].empty()) {
        cout << "[" << activeParticipants[i].character.candies[ca] << "]   ";
    }
}
cout << endl;

// clear buffer or else infinity loop
cin.ignore(numeric_limits<streamsize>::max(), '\n');

// read candy name
cout << "Enter the name of the candy you want to use: ";
getline(cin, usecandyName);

//cout << endl << " error " << usecandyName << endl << endl;


//exit(1);

/*** most likely another infineloo problem.

                  //cycle through the vector of candies - string.
                for(int ca = 0; ca < 9; ca++ ){ // candy array.
                    if( !activeParticipants[i].character.candies[ca].empty() ){cout << "[" << activeParticipants[i].character.candies[ca] << "]   ";}    
                }
                cout << endl << endl;

    //string usecandyName;
    cout << "Enter the name of the candy you want to use: ";
    cin >> usecandyName;

*/


        if (usecandyName == "Frosty Fizz") {
            // boosts player's stamina by 10 units
            activeParticipants[i].character.stamina += 10;
            cout << "You used Frosty Fizz. Your stamina increased by 10 units." << endl;

            continue;

        } else if (usecandyName == "Lucky Licorice") {
            // Decreases opponents' stamina by 10 units (mild)


            for(int opi = 0; opi < activeParticipants.size(); opi++){

                cout << opi << ". Oppoonent initial: " << activeParticipants[opi].name;

            } //oppent index
            cout << "chose a number from above: ";
            cin >> chosenopi;

            
            //check if that person has a cany that is a shield

            /***
            Bubblegum Blast will only protect against Lucky Licorice.
            Sparkling Sapphire will only protect against Lucky Licorice and Venomous Vortex.
            Caramel Comet will protect against all the poison candies: Lucky Licorice, Venomous Vortex, and Toxic Taffy.
            
            */
            // check immunity
            for (int opc = 0; opc < activeParticipants[chosenopi - 1].character.candies.size(); opc++){
                if (  activeParticipants[chosenopi - 1].character.candies[opc] == "Sparkling Sapphire" || activeParticipants[chosenopi - 1].character.candies[opc] == "Caramel Comet" )
                {
                    cout << "Sorry " << activeParticipants[chosenopi - 1].name << " has an immunity candy" <<endl;
                }
            }//opc oppionent candies



            cout << "Enter opponent :" << endl;
            activeParticipants[chosenopi].character.stamina -= 10;
            cout << "You used Lucky Licorice. Opponent's stamina decreased by 10 units." << endl;
continue;

        } else if (usecandyName == "Ruby Rapture") {
            // Forms a gummy barrier on a chosen tile, and opponent loses 2 turns
            
            cout << "You are dropping Ruby Rapture on this tile. A gummy barrier formed on tile. Opponent will lose 1 turn." << endl;

            //capture the participant board position
            int partbp;
            partbp = activeParticipants[i].board_position;
            boardtiles[partbp].droppedcandy = "Fearsome Fudge";

continue;
        } else if (usecandyName == "Crimson Crystal") {
            // Boosts player's stamina by 15 units
            activeParticipants[i].character.stamina += 15;
            cout << "You used Crimson Crystal. Your stamina increased by 15 units." << endl;
continue;

        } else if (usecandyName == "Fearsome Fudge") {
            // Forms a gummy barrier on a chosen tile, and opponent loses 1 turn
            // Assuming there's a function to choose a tile for the barrier boardtiles[proposedposition].droppedcandy = "Frosty Fizz";
            //int chosenTile = chooseTile(); // Implement the function or replace with your logic
            
            
            cout << "You are dropping Fearsome Fudge on this tile. A gummy barrier formed on tile. Opponent will lose 1 turn." << endl;

            //capture the participant board position
            int partbp;
            partbp = activeParticipants[i].board_position;
            boardtiles[partbp].droppedcandy = "Fearsome Fudge";



continue;
        } else if (usecandyName == "Venomous Vortex") {
            // Decreases opponents' stamina by 15 units (moderate)
            
            cout << "Enter opponent :" << endl;
            activeParticipants[chosenopi].character.stamina -= 15;
            cout << "You used Venomous Vortex. Opponent's stamina decreased by 15 units." << endl;

continue;
        } else if (usecandyName == "Bubblegum Blast") {
            // Protects against mild poison candy (use logic to determine protection)
            
            // Use your logic to check if the opponent uses mild poison candy and adjust protection accordingly

            cout << "You used Bubblegum Blast. Protected against mild poison candy." << endl;

continue;
        } else if (usecandyName == "Mystic Marshmallow") {
            // Boosts player's stamina by 20 units
            activeParticipants[i].character.stamina += 20;
            cout << "You used Mystic Marshmallow. Your stamina increased by 20 units." << endl;

continue;
        } else if (usecandyName == "Sparkling Sapphire") {
            // Protects against mild and moderate poison candies (use logic to determine protection)
            
            // Use your logic to check if the opponent uses mild or moderate poison candy and adjust protection accordingly
            cout << "You used Sparkling Sapphire. Protected against mild and moderate poison candies." << endl;

continue;
        } else if (usecandyName == "Toxic Taffy") {
            // Decreases opponents' stamina by 20 units (strong)
            
            cout << "Enter opponent :" << endl;
            //activeParticipants[chosenopi].character.stamina -= 20;

            for(int opi = 0; opi < activeParticipants.size(); opi++){

                cout << opi << ". Oppoonent initial: " << activeParticipants[opi].name;

            } //oppent index
            cout << "Chose a number from above: ";
            cin >> chosenopi;
            cout << "You used Toxic Taffy. Opponent's stamina decreased by 20 units." << endl;

            bool chosenoppenthasimmunity = false;
            // check immunity
            for (int opc = 0; opc < activeParticipants[chosenopi - 1].character.candies.size(); opc++){
                if ( activeParticipants[chosenopi - 1].character.candies[opc] == "Caramel Comet" )
                {
                    cout << "Sorry " << activeParticipants[chosenopi - 1].name << " has an immunity candy" <<endl;
                    chosenoppenthasimmunity = true;
                }
            }//opc oppionent candies


            if (!chosenoppenthasimmunity){            
                if ( (activeParticipants[chosenopi].character.stamina - 20) < 0 ) {
                activeParticipants[chosenopi].character.stamina = 0;
                } else {
                 activeParticipants[chosenopi].character.stamina = activeParticipants[chosenopi].character.stamina - 20 ;
                 }
            }

continue;
        } else if (usecandyName == "Caramel Comet") {
            // Protects against all poison candies (use logic to determine protection)
            
            cout << "You used Caramel Comet. Protected against all poison candies." << endl;

    } else {
        cout << "Invalid candy selection." << endl;

        continue;
    }


    //UPDATE THE BOARRD/??


                //to drop a congy do this - drope on a file.



            } // endo of option 2;
            else { // WHEN PLAYER PICKS 3

                cout << endl << "Here are your stats." << endl;
                cout << "Player Initial: " << activeParticipants[i].name << endl;
                cout << "Character Name: " << activeParticipants[i].character.name << endl;
                cout << "Stamina: " << activeParticipants[i].character.stamina << endl;
                cout << "Gold: " << activeParticipants[i].character.gold << endl;
//testing
//activeParticipants[i].robersrepel = true;

                cout << "Rober's Repel: " << activeParticipants[i].robersrepel << endl;

                cout << "Candies: " << endl;

                //cycle through the vector of candies - string.
                for(int ca = 0; ca < 9; ca++ ){ // candy array.
                    if( !activeParticipants[i].character.candies[ca].empty() ){cout << "[" << activeParticipants[i].character.candies[ca] << "]   ";}    
                }
                cout << endl << endl;



            } // end of option 3
            
            cout << endl;

        //This is the end of the do while turnisnotover = true.

            } while (turnisnotover);



        } //endo of the for loop that cycles through the participant turns.



    } while (wedonthaveawinner);



    return 0;
}

