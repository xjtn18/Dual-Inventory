#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <map>


std::string getResourcePath(const std::string &subDir = "");
void logSDLError(const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void loadSound(const std::string &file, Mix_Chunk *&chunk, int volume = 128);
void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int w, int h);
void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y);
int center(int big_xy, int little_xy);

// Audio functions
void play(Mix_Chunk *sample, int channel = -1);
void loop(Mix_Chunk *sample, int channel = -1);


// get resource path
const std::string basePath = getResourcePath();

// declare sounds
inline Mix_Chunk *audio_song; //TODO: move to an audio header
inline Mix_Chunk *audio_error;
inline Mix_Chunk *audio_ambi;
inline Mix_Chunk *audio_grab;
inline Mix_Chunk *audio_release;
inline Mix_Chunk *audio_swap;
inline Mix_Chunk *audio_move_selector;

// declare textures
inline SDL_Texture *tx_bg; 
inline SDL_Texture *tx_cell; 
inline SDL_Texture *tx_cell_select; 
inline SDL_Texture *tx_apple; 
inline SDL_Texture *tx_knife; 
inline SDL_Texture *tx_notebook; 
inline SDL_Texture *tx_mp3player; 
inline SDL_Texture *tx_cell_bg; 

// constants
const int SCREEN_WIDTH  = 1200;
const int SCREEN_HEIGHT = 900;



class RenderWindow {
private:
	SDL_Window *win;
	SDL_Renderer *ren;

public:
	RenderWindow();
	void cleanup();
	void loadAllTextures();
	void clear();
	void show();
	void render(SDL_Texture *texture, int x, int y, int w, int h);
};



enum Justify {NONE = 0, HCENTER = 1, VCENTER = 2};


