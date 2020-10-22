#define SDL_MAIN_HANDLED

#include "Inventory.h"
#include "View.h"



Inventory* createInventory(int dim_count, char** dims){
	// init inventory using CL args; fills with arbitrary starting items
	Inventory* I;

	if (dim_count == 0){
		I = new Inventory(4,9);
	} else if (dim_count == 2){
		I = new Inventory(std::atoi(dims[1]), std::atoi(dims[2]));
	} else {
		log("Error: bad inventory dimensions");
		return nullptr;
	}

	I->add(new Apple());
	I->add(new Knife());
	I->add(new Notebook());
	I->add(new MP3Player());

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

				// commands
				if (e.key.keysym.sym == SDLK_u){
					I->interact();
				}
				if (e.key.keysym.sym == SDLK_d){
					I->drop();
				}
				if (e.key.keysym.sym == SDLK_m){
					I->itemSwap();
				}

				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
		}

		SDL_RenderClear(ren); // Clear the screen

		// draw background
		renderTexture(ren, tx_bg, 0, 0);

		//draw active inventory
		render::drawInventory(ren, I);

		SDL_RenderPresent(ren); // Update the screen
	}

}



int main(int argc, char **argv){
	argc--; //disregard binary name

	// Call this first since we are using our custom main function instead of SDL_Main (due to '#define SDL_MAIN_HANDLED' at the top)
	SDL_SetMainReady();
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
	SDL_DestroyTexture(tx_cell_select);
	SDL_DestroyTexture(tx_apple);
	SDL_DestroyTexture(tx_knife);
	SDL_DestroyTexture(tx_notebook);
	SDL_DestroyTexture(tx_mp3player);
	//TODO: free entire Inventory
	//TODO: move rendering to view module

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	IMG_Quit(); // quit SDL_Image
	SDL_Quit();
	return 0;
}



