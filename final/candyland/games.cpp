#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>   
#include "games.h"


using namespace std;

Games::Games() {
    
}


int Games::randnumberforriddle(int lowerrange, int upperrange) {

    int inttoreturn;

    inttoreturn =  rand() % (upperrange - lowerrange + 1) + lowerrange;

    return inttoreturn;
}


void Games::playRockPaperScissors(string player_name) {
    cout << "Welcome to Rock, Paper, Scissors, " << player_name << "!" << endl;


    srand(static_cast<unsigned int>(time(nullptr)));

    string choices[] = {"rock", "paper", "scissors"};

    string player_choice;
    cout << "Enter your choice (rock, paper, or scissors): ";
    cin >> player_choice;

    string computer_choice = choices[rand() % 3];

    cout << "Player's choice: " << player_choice << endl;
    cout << "Computer's choice: " << computer_choice << endl;


    if (player_choice == computer_choice) {
        cout << "It's a tie!" << endl;
    } else if (
        (player_choice == "rock" && computer_choice == "scissors") ||
        (player_choice == "scissors" && computer_choice == "paper") ||
        (player_choice == "paper" && computer_choice == "rock")
    ) {
        cout << player_name << " wins!" << endl;
        isWinner = true;
    } else {
        cout << "Computer wins!" << endl;
        isWinner = false;
    }
}






void Games::loadAndPlayRiddles() {
    ifstream file("text_files/riddles.txt");
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << endl;
        return;
    }

    Riddle riddle;
    string line;
    string riddleanswer;

    while (getline(file, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            riddle.question = line.substr(0, pos);
            riddle.answer = line.substr(pos + 1);
            riddles.push_back(riddle);
        }
    }

    file.close();


    if (riddles.empty()) {
        cout << "No riddles loaded." << endl;
        return;
    }


    int randriddle = randnumberforriddle(0, riddles.size() - 1);

 
    Riddle selectedRiddle = riddles[randriddle];

    cout << "Riddle Question: " << selectedRiddle.question << endl;

    cin >> riddleanswer;

    if(selectedRiddle.answer == riddleanswer){ 
        isWinner = true; 
        cout << "Congrats! You answered the riddle correctly!" << endl;
    }
 

}



