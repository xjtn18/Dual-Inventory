#include "debug.h"
#include "Items.h"
#include "Inventory.h"
#include "mySDL.h"
#include <typeindex>
#include <map>


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 460;

// get resource path
const std::string basePath = getResourcePath();

// load textures
SDL_Texture *tx_bg; 
SDL_Texture *tx_cell; 
SDL_Texture *tx_cell_select; 
SDL_Texture *tx_apple; 
SDL_Texture *tx_knife; 
SDL_Texture *tx_notebook; 
SDL_Texture *tx_mp3player; 


const std::map<std::string, SDL_Texture*> mapItemTexture = {
	{"apple", tx_apple},
	{"notebook", tx_notebook},
	{"knife", tx_knife},
	{"mp3player", tx_mp3player}
};


void drawInventory(SDL_Renderer *ren, Inventory* I){
	uint active_size = I->getActiveSize();
	uint other_size = I->getOtherSize();

	int cell_w = 100;
	int cell_h = 100;
	int item_w = 50;
	int item_h = 50;
	int select_scalar = 10;

	for (uint i = 0; i < active_size; ++i) {
		int x = SCREEN_WIDTH/2 - (cell_w * active_size/2) + (cell_w * i);
		int y = SCREEN_HEIGHT/2 - cell_h/2; 							//vertical middle of screen

		// render cells and items
		renderTexture(ren, tx_cell, x, y, cell_w, cell_h);
	}

	for (uint i = 0; i < active_size; ++i) {
		int x = SCREEN_WIDTH/2 - (cell_w * active_size/2) + (cell_w * i);
		int y = SCREEN_HEIGHT/2 - cell_h/2; 							//vertical middle of screen
		if (i == I->getSelectorPos()){
			renderTexture(ren, tx_cell_select, x - select_scalar/2, y - select_scalar/2, cell_w + select_scalar, cell_h + select_scalar);
		}

/*
		Item* it = I->mCurrBuffer->selectedItem();
		if (it != nullptr){
			std::cout << it->isConsumable() << std::endl;
			std::cout << it->getName() << std::endl;
			SDL_Texture *item_tex = mapItemTexture.at(it->getName());
			log("here");
			if (item_tex == nullptr){
				log("UHHH");
			}
			renderTexture(ren, item_tex, x + cell_w/2 - item_w/2, y + cell_h/2 - item_h/2, item_w, item_h);
		}
*/
	}

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
	std::cout << I->getActiveSize() << std::endl;
	std::cout << I->getOtherSize() << std::endl;
	I->add(new Notebook());
	std::cout << I->getActiveSize() << std::endl;
	std::cout << I->getOtherSize() << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	std::cout << "WHAT IS STD LENGTH ERROR????" << std::endl;
	Item *item = I->getCurrentItem();
	log("yay!");
	log("UXI!");
	I->interact();
	if (item)
		log("yay!");

	std::cout << item->getName() << std::endl;
	log("whew");
	SDL_Delay(8000);
	//log("out of create inventory");

	return I;
}



void programLoop(int argc, char** argv, SDL_Renderer *ren){
	// initialize inventory
	Inventory* I = createInventory(argc, argv);


	SDL_Event e;
	bool quit = false;

	while (!quit){
		// get user input
		while (SDL_PollEvent(&e)){

			if (e.type == SDL_QUIT){
				quit = true;
			}

			// handle keyboard input
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}

				// directions
				if (e.key.keysym.sym == SDLK_LEFT){
					I->selectorMove(LEFT);
				}
				if (e.key.keysym.sym == SDLK_RIGHT){
					I->selectorMove(RIGHT);
				}
				if (e.key.keysym.sym == SDLK_UP){
					I->selectorMove(UP);
				}
				if (e.key.keysym.sym == SDLK_DOWN){
					I->selectorMove(DOWN);
				}
			}
		}

		SDL_RenderClear(ren); // Clear the screen

		// draw background
		renderTexture(ren, tx_bg, 0, 0);

		//draw active inventory
		drawInventory(ren, I);

		SDL_RenderPresent(ren); // Update the screen
	}

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

	SDL_Window *win = SDL_CreateWindow("Dual Inventory Demo", 300, 400, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

	// set textures
	tx_bg = loadTexture(basePath + "bg.png", ren);
	tx_cell = loadTexture(basePath + "InventoryCell.png", ren);
	tx_cell_select = loadTexture(basePath + "InventoryCellSelect.png", ren);
	tx_apple = loadTexture(basePath + "apple.png", ren);
	tx_knife = loadTexture(basePath + "knife.png", ren);
	tx_notebook = loadTexture(basePath + "notebook.png", ren);
	tx_mp3player = loadTexture(basePath + "mp3player.png", ren);

	// call main program loop
	programLoop(argc, argv, ren);


	SDL_DestroyTexture(tx_bg);
	SDL_DestroyTexture(tx_cell);
	//TODO: destroy the rest of the texture before exiting
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit(); // quit SDL_Image
	SDL_Quit();
	return 0;
}

