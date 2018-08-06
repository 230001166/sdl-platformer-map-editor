#ifndef TILE_H
#define TILE_H

#include "GraphicFunctions.h"

class Tile {

    public:
        Tile ();
        Tile (std::string imageFileName);

        std::string imageFileName = "";

        SDL_Surface* image = NULL;

        bool isCollidable = true;

    protected:

    private:

};

#endif // TILE_H
