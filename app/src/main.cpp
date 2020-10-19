#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "res_path.h"
#include "debug.h"


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;


void logSDLError(const std::string &msg){
	std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}




SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *tex = nullptr;
	SDL_Surface *png = IMG_Load(file.c_str());
	if (png != nullptr){
		tex = SDL_CreateTextureFromSurface(ren, png);
		SDL_FreeSurface(png);
		if (tex == nullptr){
			logSDLError("create texture");
		}
	} else {
		logSDLError("create bitmap");
	}

	return tex;
}



void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}




int main(int argc, char **argv){
	// start SDL
	log("welcome to SDL");

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		logSDLError("create window");
		SDL_Quit();
		return 1;
	}

	SDL_Delay(3000);


	// make renderer
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		logSDLError("create renderer");
		SDL_Quit();
		return 1;
	}



	// get png
	const std::string basePath = getResourcePath("app");
	log(basePath);
	SDL_Texture *bg = loadTexture(basePath + "bg.png", ren);
	
	if (bg == nullptr){
		logSDLError("load tex");
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 1;
	}


	for (int i = 0; i < 3; ++i){
		//First clear the renderer
		SDL_RenderClear(ren);

		int bW, bH;
		SDL_QueryTexture(bg, NULL, NULL, &bW, &bH);
		renderTexture(bg, ren, 0, 0);

		//Update the screen
		SDL_RenderPresent(ren);
		//Take a quick break after all that hard work
		SDL_Delay(1000);
	}


	SDL_DestroyTexture(bg);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}

