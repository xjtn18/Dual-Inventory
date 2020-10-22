#pragma once

#include "mySDL.h"
#include "debug.h"
#include "Inventory.h"
#include <map>


// get resource path
const std::string basePath = getResourcePath();

// declare textures
inline SDL_Texture *tx_bg; 
inline SDL_Texture *tx_cell; 
inline SDL_Texture *tx_cell_select; 
inline SDL_Texture *tx_apple; 
inline SDL_Texture *tx_knife; 
inline SDL_Texture *tx_notebook; 
inline SDL_Texture *tx_mp3player; 

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 460;


namespace render {
	void drawInventory(SDL_Renderer *ren, Inventory* I);
}

