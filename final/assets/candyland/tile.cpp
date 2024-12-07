#include "tile.h"

using namespace std;

TileClass::TileClass() {}

int TileClass::tileRandomNumber(int lowerrange, int upperrange, int modthree) { //this will return all the 

    int randomNumber = rand() % (upperrange - lowerrange + 1) + lowerrange;

    if (modthree >= 0 && modthree <= 2) {
        int modulus = randomNumber % 3;

        if (modulus != modthree) {
            randomNumber += (modthree - modulus + 3) % 3;
        }
    }

    return randomNumber;
}

void TileClass::generateInitialTiles(TileType boardtiles[]) {
    for (int i = 0; i < 83; ++i) {
        boardtiles[i].tile_position = i;
        boardtiles[i].droppedcandy = "none";
        
        // Set color based on position % 3
        switch (i % 3) {
            case 0:
                boardtiles[i].color = "magenta";
                break;
            case 1:
                boardtiles[i].color = "green";
                break;
            case 2:
                boardtiles[i].color = "blue";
                break;
        }

        boardtiles[i].specialtiletype = "regular" ; 
    }

    //load candy stores!

    int tileupdate;
    //Candy Stores. = 3
    tileupdate = tileRandomNumber(1,27,0);
    boardtiles[tileupdate].specialtiletype = "candystore" ;
    tileupdate = tileRandomNumber(28,54,1);
    boardtiles[tileupdate].specialtiletype = "candystore" ;
    tileupdate = tileRandomNumber(55,82,2);
    boardtiles[tileupdate].specialtiletype = "candystore" ;
//hiddentreasure = 4
    int updatenumber = 0;
    do {
        tileupdate = tileRandomNumber(1,82,3);
        if ( updateTileType(boardtiles[tileupdate], tileupdate) ) {
            boardtiles[tileupdate].specialtiletype = "hiddentreasure";
            updatenumber++ ;
        }
    }
    while (updatenumber < 4);

//specialtile 19 tiles is 25% of remaining regular tile to uptdate to special tiles
    updatenumber = 0;
    do {
        tileupdate = tileRandomNumber(1,82,3);
        if ( updateTileType(boardtiles[tileupdate], tileupdate) ) {
            boardtiles[tileupdate].specialtiletype = "specialtile";
            updatenumber++ ;
        }
    }
    while (updatenumber < 19);

}


bool TileClass::updateTileType(TileType tiletoupdate, int tileIndex) {

    //check if boardtiles[tileupdate].specialtiletype == "regular"
    if(tiletoupdate.specialtiletype == "regular"){
        return true;
    } else { return false;}

}



/*
string TileClass:: getTileType(TileType boardtiles[], int tile_position) {

    return boardtiles[tile_position].specialtiletype;
}
*/
