// menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std; 


    class Character {
    public:
        Character(const string& name);

        string getName() const;
        bool isChosen() const;
        void choose();
        void startGame() const;

    private:
        string name;
        bool chosen;
    };

    class Game {
    public:
        Game();

        void displayMenu() const;
        void selectCharacter(const string& characterName);

    private:
        vector<Character> characters;
    };



#endif // MENU_H
