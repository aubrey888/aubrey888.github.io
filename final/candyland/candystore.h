#ifndef CANDYSTORE_H
#define CANDYSTORE_H

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <fstream>
using namespace std;

struct Candy {
    string name;        // Candy name
    string description; // Candy description
    string effectType;  // Effect type
    int effectValue;    // Effect value (changed to int)
    string candyType;   // Candy type
    int price;          // Candy price (changed to int)

    // Constructor to initialize the struct
    Candy(const string& n, const string& desc, const string& effType, int effVal, const string& candType, int p)
        : name(n), description(desc), effectType(effType), effectValue(effVal), candyType(candType), price(p) {}
};


class CandyStore {
private:
    string _storename;
    vector<Candy> _candies; // Use a vector to store candies
    int _candy_count;

public:
    CandyStore();
    CandyStore(string store_name);
    bool addCandy(Candy candy);
    bool removeCandy(string candy_name);
    void displayCandies() const;
    
    // Function to load candies from "Candies.txt" file
    vector<Candy> loadCandiesFromFile();
    using CandyArray = array<string, 9>;
    CandyArray showCandyStoreMenu(const CandyArray& characterCandies, vector<Candy> loadedCandies); 
    
};

#endif
