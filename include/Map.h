#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <vector>

class Map
{
    public:
        Map();
        virtual ~Map();

        int tilemapLengthInTiles = 10;
        int tilemapHeightInTiles = 10;

        int cameraXOffset = -32;
        int cameraYOffset = -32;

        int playerXOffset = 0;
        int playerYOffset = 128;

        std::vector<Tile> tiles;

        std::vector<int> tileArray;
        std::vector<int> backgroundTileArray;

    protected:

    private:
};

#endif // MAP_H
