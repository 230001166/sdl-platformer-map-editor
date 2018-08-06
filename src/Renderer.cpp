#include "Renderer.h"
#include <string>
#include <sstream>

void Renderer::renderTileMap (Map worldmap) {

        for (unsigned int i = 0; i < worldmap.tileArray.size (); i++) {

            GraphicFunctions::apply_surface (32 * (i % worldmap.tilemapLengthInTiles) - worldmap.cameraXOffset,
                                             32 * (i / worldmap.tilemapHeightInTiles) - worldmap.cameraYOffset,
                                             worldmap.tiles[worldmap.backgroundTileArray [i]].image,
                                             screen);

            GraphicFunctions::apply_surface (32 * (i % worldmap.tilemapLengthInTiles) - worldmap.cameraXOffset,
                                             32 * (i / worldmap.tilemapHeightInTiles) - worldmap.cameraYOffset,
                                             worldmap.tiles[worldmap.tileArray [i]].image, screen);

        }

}

void Renderer::renderText (std::string message, int xOffset, int yOffset) {

    int temp_message_length = message.length () + 1;

    char messageCharacters [temp_message_length];

    strcpy (messageCharacters, message.c_str ());

    for (int i = 0; i < temp_message_length; i++) {

        std::string filename = "text/"; filename.append (1, messageCharacters[i]);  filename.append (".png");

        SDL_Surface* temp_image = GraphicFunctions::load_image (filename);

        GraphicFunctions::apply_surface (xOffset + (i*8), yOffset, temp_image, screen);

    }

}

void Renderer::displayTiles (Map worldmap, int xOffset, int yOffset) {

    int tileXOffset = 0, tileYOffset = 0;

    for (int i = 0; i < worldmap.tiles.size (); i++) {

            GraphicFunctions::apply_surface (xOffset + tileXOffset*64, yOffset + tileYOffset*64, worldmap.tiles [i].image, screen);

            std::stringstream temp; temp << i;
            renderText (temp.str (),xOffset + tileXOffset*64, yOffset+32+tileYOffset*64);

            tileXOffset++;

            if (tileXOffset == 6) { tileXOffset = 0; tileYOffset++; }

    }

}

Renderer::Renderer () { };

