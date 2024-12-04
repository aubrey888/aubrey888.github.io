// menu.cpp
#include "menu.h"
#include "player.h"

using namespace std;


    Character::Character(const string& name) : name(name), chosen(false) {}

    string Character::getName() const {
        return name;
    }

    bool Character::isChosen() const {
        return chosen;
    }

    void Character::choose() {
        chosen = true;
    }

    void Character::startGame() const {
        cout << "Character " << name << " is starting the game." << endl;
    }

    Game::Game() {
        // Load characters from file
        //loadCharactersFromFile("text_files/characters.txt");
    } 

    //Player theplayerclass;

    void Game::displayMenu() const {
        cout << "Available Characters:" << endl;
        for (const auto& character : characters) {
            if (!character.isChosen()) {
                cout << character.getName() << endl;
            }
        }
    }

    void Game::selectCharacter(const string& characterName) {
        auto it = find_if(characters.begin(), characters.end(),
                          [characterName](const Character& character) {
                              return character.getName() == characterName && !character.isChosen();
                          });

        if (it != characters.end()) {
            it->choose();
            it->startGame();
        } else {
            cout << "Invalid character selection. Please choose an available character." << endl;
        }
    }


    

