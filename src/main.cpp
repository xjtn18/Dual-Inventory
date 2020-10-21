#include "mySDL.h"
#include "debug.h"
#include "Items.h"
#include "Inventory.h"


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 460;



void drawInventory(SDL_Renderer *ren, SDL_Texture *cell, uint active_size){
	const std::string basePath = getResourcePath();

	int cell_w = 100;
	int cell_h = 100;

	for (uint i = 0; i < active_size; ++i) {
		int x = SCREEN_WIDTH/2 - (cell_w * active_size/2) + (cell_w * i);
		int y = SCREEN_HEIGHT/2 - cell_h/2; 							//vertical middle of screen
		renderTexture(ren, cell, x, y, cell_w, cell_h);
	}

	//SDL_Delay(3000);
}



Inventory* createInventory(int dim_count, char** dims){
	Inventory* I;

	if (dim_count == 0){
		I = new Inventory(4,9);
	} else if (dim_count == 2){
		I = new Inventory(std::atoi(dims[1]), std::atoi(dims[2]));
	} else {
		log("Error: bad inventory dimensions", true, 5);
		return nullptr;
	}

	I->add(new Apple());
	I->add(new Apple());
	I->add(new Notebook());

	return I;
}




int main(int argc, char **argv){
	argc--; //disregard exe name

	// start SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError("IMG_Init");
		SDL_Quit();
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		logSDLError("create window");
		SDL_Quit();
		return 1;
	}



	// make renderer
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		logSDLError("create renderer");
		SDL_Quit();
		return 1;
	}



	// get resource path
	const std::string basePath = getResourcePath();
	
	// get background
	SDL_Texture *bg = loadTexture(basePath + "bg.png", ren);

	SDL_Texture *cell = loadTexture(basePath + "InventoryCell.png", ren);


	// initialize inventory
	Inventory* I = createInventory(argc, argv);
	if (I == nullptr){
		return 1;
	}


	// Main app loop
	SDL_Event e;
	bool quit = false;

	while (!quit){
		// get user input
		while (SDL_PollEvent(&e)){

			if (e.type == SDL_QUIT){
				quit = true;
			}

			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
		}

		SDL_RenderClear(ren); // Clear the screen

		// draw background
		renderTexture(ren, bg, 0, 0);

		//draw active inventory
		drawInventory(ren, cell, I->getActiveSize());

		SDL_RenderPresent(ren); // Update the screen
	}


	SDL_DestroyTexture(bg);
	SDL_DestroyTexture(cell);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit(); // quit SDL_Image
	SDL_Quit();
	return 0;
}

