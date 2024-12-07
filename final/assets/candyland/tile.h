#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;


struct TileType {

int tile_position;
string specialtiletype;
string color;
string droppedcandy;


};


class TileClass
{
private:
    string tile_type;
    string droppedcandy;
    int tile_position;
    int candystorecount;
    int tileIndex;
    string updateVal;
    
    

public:
    TileClass();
    int tileRandomNumber(int lowerrange, int upperrange, int modthree); // modthree will be the color 0 = magenta
    
    string determineTileType();
    //vector<Tile> boardtiles populatetiles();
    array<TileType, 83> boardtiles;

    void generateInitialTiles(TileType boardtiles[]);

    bool updateTileType(TileType tiletoupdate, int tileIndex);

    //string getTileType(TileType boardtile, int tile_position);

};

#endif