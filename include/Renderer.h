#ifndef RENDERER_H
#define RENDERER_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Map.h"
#include <string>
#include <vector>

class Renderer
{
    private:

    public:

        SDL_Surface *screen = NULL;

        void renderTileMap (Map worldmap);

        void renderText (std::string message, int xOffset, int yOffset);

        void displayTiles (Map worldmap, int xOffset, int yOffset);

        Renderer ();

};

#endif // RENDERER_H
