#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "Renderer.h"

SDL_Event event;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

void loadMap (std::string filename, Map &worldmap) {

    std::string line;
   std::ifstream file (filename.c_str ());

    if (file.is_open())  {

        int numberOfTiles;

        file >> worldmap.tilemapLengthInTiles;
        file >> worldmap.tilemapHeightInTiles;

        file >> numberOfTiles; std::cout << numberOfTiles << std::endl;

        for (unsigned int i = 0; i < numberOfTiles; i++) {

            std::string temp_image_path;

            file >> temp_image_path;

            Tile temp (temp_image_path); std::cout << temp_image_path << std::endl;

            file >> temp.isCollidable;

            worldmap.tiles.push_back (temp);

        }

        for (unsigned int i = 0; i < worldmap.tilemapHeightInTiles * worldmap.tilemapLengthInTiles; i++) { std::cout << i << std::endl;

            int temp_integer_input = 0;

            file >> temp_integer_input; worldmap.tileArray.push_back (temp_integer_input);
            file >> temp_integer_input; worldmap.backgroundTileArray.push_back (temp_integer_input);

        }

        file >> worldmap.playerXOffset;
        file >> worldmap.playerYOffset;

        file.close();

    } else std::cout << "Unable to open file";

}

void saveMap (std::string filename, Map worldmap) {

    std::string line;
    std::ofstream file (filename.c_str ());

    if (file.is_open()) {

        file << worldmap.tilemapLengthInTiles << "\n";
        file << worldmap.tilemapHeightInTiles << "\n";

        file << worldmap.tiles.size () << "\n";

        for (int i = 0; i < worldmap.tiles.size (); i++ ) {

            file << worldmap.tiles[i].imageFileName << "\n";
            file << worldmap.tiles[i].isCollidable << "\n";

        }


        for (int i = 0; i < worldmap.tilemapHeightInTiles * worldmap.tilemapLengthInTiles; i++) {

            file << worldmap.tileArray [i] << "\n";
            file << worldmap.backgroundTileArray [i] << "\n";

        }

        file << worldmap.playerXOffset << "\n";
        file << worldmap.playerYOffset << "\n";

        file.close();

    }
}

std::string returnCursorCoordinatesAsString (int cursorX, int cursorY) {

    std::stringstream cursorCoordinateString; cursorCoordinateString << "x "; cursorCoordinateString << cursorX;
        cursorCoordinateString << "   "; cursorCoordinateString <<  "y ";cursorCoordinateString <<  cursorY;

    return cursorCoordinateString.str ();

}

Renderer renderer;
Map worldmap;

int main ( int argc, char* args[] ) {

    bool quit = false; int cursorX = 32, cursorY = 32; int tileCode = 0; bool isGettingTextInput = false; std::string textInput = "";

    bool isOnBackgroundLayer = false;

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }

    renderer.screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE );

    if( renderer.screen == NULL )
    {
        return 1;
    }

    loadMap ("hills_01.map", worldmap);

    while( quit == false ) {

        if( SDL_PollEvent( &event ) ) {


            if( event.type == SDL_KEYDOWN ) {

                if (!isGettingTextInput) {

                    switch( event.key.keysym.sym ) {

                        case SDLK_UP: { if (cursorY > 32) { cursorY -= 32; }
                             } break;
                        case SDLK_LEFT: { if (cursorX > 32) { cursorX -= 32; }
                             } break;
                        case SDLK_DOWN: { if (cursorY < 32*worldmap.tilemapHeightInTiles) { cursorY += 32; }
                             } break;
                        case SDLK_RIGHT: { if (cursorX < 32*worldmap.tilemapHeightInTiles) { cursorX += 32; }
                             } break;
                        case SDLK_2: {

                            tileCode++;

                             } break;
                        case SDLK_1: {

                            if (tileCode > 0) { tileCode--; }

                            } break;
                        case SDLK_RETURN: {

                            if (isOnBackgroundLayer) {

                                worldmap.backgroundTileArray [(cursorX/32 - 1) + (worldmap.tilemapLengthInTiles*(cursorY/32 - 1))] = tileCode;

                            } else {

                                worldmap.tileArray [(cursorX/32 - 1) + (worldmap.tilemapLengthInTiles*(cursorY/32 - 1))] = tileCode;

                            }

                            } break;
                        case SDLK_s: {

                            isGettingTextInput = true;

                        }
                        case SDLK_b: {

                            if (isOnBackgroundLayer == true) {

                                isOnBackgroundLayer = false;

                            } else {

                                isOnBackgroundLayer = true;

                            }

                        }
                        case SDLK_x: {

                            worldmap.playerXOffset = cursorX - 32;
                            worldmap.playerYOffset = cursorY - 32;

                        }
                        default: break;

                    }

                } else {

                    if (event.key.keysym.sym == SDLK_RETURN) {

                            isGettingTextInput = false;
                            saveMap (textInput + ".map", worldmap);

                            textInput = "";

                            renderer.renderText ("file saved", 544, 320);

                            if( SDL_Flip( renderer.screen ) == -1 ) {

                                return 1;

                            }

                            SDL_Delay (2500);

                    } else {

                        textInput += (char) event.key.keysym.sym;

                    }

                }

            } else if ( event.type == SDL_QUIT ) {

                quit = true;

            }

            SDL_WM_SetCaption( "Tilemap Editor", NULL);

            renderer.renderTileMap (worldmap);

            renderer.displayTiles (worldmap, 544, 32);

            if (isGettingTextInput) {

                    renderer.renderText (textInput, 544, 320);

            }

            renderer.renderText (returnCursorCoordinatesAsString (cursorX, cursorY), 32,16);

            if (isOnBackgroundLayer) { renderer.renderText ("background", 244,16); }

            GraphicFunctions::apply_surface (cursorX, cursorY, worldmap.tiles[tileCode].image, renderer.screen);

            if( SDL_Flip( renderer.screen ) == -1 ) {

                return 1;

            }

            SDL_FillRect(renderer.screen, NULL, SDL_MapRGB(renderer.screen->format, 0, 0, 0));

        }

    }

    SDL_Quit ();

    return 0;

}
