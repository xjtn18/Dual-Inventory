#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


std::string getResourcePath(const std::string &subDir = "");
void logSDLError(const std::string &msg);
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);
void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int w, int h);
void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y);


