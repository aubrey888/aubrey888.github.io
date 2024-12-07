// CandyStore.cpp

#include "candystore.h"
#include <iostream>
#include <fstream>
#include "player.h"
#include "tile.h"

TileClass tileclass;

CandyStore::CandyStore() : _storename(""), _candy_count(0)
{
}

CandyStore::CandyStore(string store_name) : _storename(store_name), _candy_count(0)
{
}

bool CandyStore::addCandy(Candy candy)
{
    if (_candy_count >= 100)
    {
        return false;
    }
    _candies.push_back(candy); // Add candy to the vector
    _candy_count++;
    return true;
}

bool CandyStore::removeCandy(string candy_name)
{
    for (int i = 0; i < _candy_count; i++)
    {
        if (_candies[i].name == candy_name)
        {
            // Remove candy from the vector
            _candies.erase(_candies.begin() + i);
            _candy_count--;
            return true;
        }
    }
    return false;
}

void CandyStore::displayCandies() const
{
    cout << "Candies in " << _storename << ":\n";
    for (const Candy& candy : _candies)
    {
        cout << "Name: " << candy.name << "\n";
        cout << "Description: " << candy.description << "\n";
        cout << "Price: $" << candy.price << "\n";
        //cout << "Type: " << candy.candy_type << "\n\n";
    }
}

vector<Candy> CandyStore::loadCandiesFromFile() {
    vector<Candy> candies; // Create a vector to store the candies read from the file

    ifstream file("text_files/candies.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file 'Candies.txt'" << endl;
        return candies; // Return an empty vector in case of an error
    }

    // Skip the first line (header)
    string header;
    getline(file, header);

    string line;
    while (getline(file, line)) {
        // Split the line into components using '|' as the delimiter
        size_t pos = 0;
        string token;
        vector<string> components;
        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);
            components.push_back(token);
            line.erase(0, pos + 1);
        }
        components.push_back(line); // Add the remaining part

        if (components.size() == 6) {
            // If there are exactly 6 components, create a Candy object
            Candy candy(
                components[0], // Name
                components[1], // Description
                components[2], // Effect type
                stoi(components[3]), // Effect value (convert from string to int)
                components[4], // Candy type
                stoi(components[5]) // Price (convert from string to int)
            );

            candies.push_back(candy); // Add the candy to the vector
        } else {
            cerr << "Skipping invalid line in 'Candies.txt': " << line << endl;
        }
    }

    file.close();
    return candies; // Return the vector of candies read from the file
}



CandyStore::CandyArray CandyStore::showCandyStoreMenu(const CandyArray& characterCandies, vector<Candy> loadedCandies) {
    string choice;
    string candyOption;
    int candyDiscardint;
    int randcand1;
    int randcand2;
    int randcand3;

    CandyArray modifiedCandies = characterCandies;






                    cout << "You landed on a candy store! Here are your candy store options:" << endl << endl;
//IMPROVEMENT could have been better to load 3 rand numbers in array and loop. - could have ensured three different candies every time
                    randcand1 = tileclass.tileRandomNumber(0,10,3);
                    cout << loadedCandies[randcand1].name + "|" + loadedCandies[randcand1].description + "|" + loadedCandies[randcand1].effectType;
                    cout << "|" << loadedCandies[randcand1].effectValue << "|" << loadedCandies[randcand1].candyType << "|" << loadedCandies[randcand1].price << endl << endl;
                    randcand2 = tileclass.tileRandomNumber(0,10,3);           
                    cout << loadedCandies[randcand2].name + "|" + loadedCandies[randcand2].description + "|" + loadedCandies[randcand2].effectType;
                    cout << "|" << loadedCandies[randcand2].effectValue << "|" << loadedCandies[randcand2].candyType << "|" << loadedCandies[randcand2].price << endl << endl;
                    randcand3 = tileclass.tileRandomNumber(0,10,3);    
                    cout << loadedCandies[randcand3].name + "|" + loadedCandies[randcand3].description + "|" + loadedCandies[randcand3].effectType;
                    cout << "|" << loadedCandies[randcand3].effectValue << "|" << loadedCandies[randcand3].candyType << "|" << loadedCandies[randcand3].price << endl << endl;


    cout << "Do you want to buy one of these candies? (y/n)" << endl;

    cin.clear();
    cin >> choice;
    bool validchoice = false;
    if (choice == "y") {

        do{
                cout << "Enter the candy you would like to buy: ";
                //cin.clear();
                //cin.ignore();  
                getline(cin, candyOption);
                //only presented candies allowed too chosen
                if( candyOption == loadedCandies[randcand1].name || candyOption == loadedCandies[randcand2].name || candyOption == loadedCandies[randcand3].name ){
                    validchoice = true;
                } else {
                    cout << endl << endl << "Choose a candy from the store." << endl << endl;
                }

        } while (validchoice == false);



        cout << endl << "You are purchasing " << candyOption << endl;




        bool foundEmptySlot = false;

        for (int i = 0; i < modifiedCandies.size(); ++i) {
            if (modifiedCandies[i].empty()) {
                //modifiedCandies[i] = candyOption;
                int purchasedcandyindex;
                //look up the cost. convert to string and append.
                for(int lci = 0; lci < loadedCandies.size(); lci++ ){ // lci loaded candies index
                    if (loadedCandies[lci].name == candyOption){ purchasedcandyindex = lci; break; }
                }
                modifiedCandies[i] = candyOption + "|" + to_string(loadedCandies[purchasedcandyindex].price);
                foundEmptySlot = true;
                break;
            }
        }

        if (!foundEmptySlot) { // a purchase would exceed the size of array
            cout << "All slots are full. Choose a candy to discard.";
        
            for (int i = 0; i < modifiedCandies.size(); ++i) {
                cout << endl;
                if (!modifiedCandies[i].empty()) {
                    cout << i + 1 << ".  [" << modifiedCandies[i] << "]  ";
                }
                cout << endl;
            }
            cout << endl << "Item number of Candy to Discard: ";
            //cin.ignore();  // This does not work!!
            cin >> candyDiscardint;
            
            int purchasedcandyindex;
            //look up the cost. convert to string and append.
            for(int lci = 0; lci < loadedCandies.size(); lci++ ){ // lci loaded candies index
                if (loadedCandies[lci].name == candyOption){ purchasedcandyindex = lci; break; }
            }
        
            modifiedCandies[candyDiscardint - 1] = candyOption + "|" + to_string(loadedCandies[purchasedcandyindex].price);

        }
    }

    return modifiedCandies;
}






