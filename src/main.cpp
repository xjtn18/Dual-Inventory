#define SDL_MAIN_HANDLED

#include "Inventory.h"
#include "View.h"
#include <stdlib.h>
#include <time.h>



Inventory* setupInventory(int dim_count, char** dims){
	// init inventory using CL args; fills with arbitrary starting items
	Inventory* I;

	if (dim_count == 0){
		I = new Inventory(5,10);
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



void programLoop(int argc, char** argv, RenderWindow window){
	// initialize inventory
	Inventory* I = setupInventory(argc, argv);
	if (I == nullptr){
		return;
	}

	SDL_Event e;
	bool quit = false;

	uint hang_selector_move_up = 0;
	uint hang_selector_move_down = 0;
	uint hang_selector_move_right = 0;
	uint hang_selector_move_left = 0;


	while (!quit){
		// get user input
		while (SDL_PollEvent(&e)){

			if (hang_selector_move_up > 0){
				if (hang_selector_move_up++ >= 2) // work in progress
					hang_selector_move_up = 0;
			}
			if (hang_selector_move_down > 0){
				if (hang_selector_move_down++ >= 2) // work in progress
					hang_selector_move_down = 0;
			}
			if (hang_selector_move_right > 0){
				if (hang_selector_move_right++ >= 2) // work in progress
					hang_selector_move_right = 0;
			}
			if (hang_selector_move_left > 0){
				if (hang_selector_move_left++ >= 2) // work in progress
					hang_selector_move_left = 0;
			}

			if (e.type == SDL_QUIT){
				quit = true;
			}

			// handle keyboard input
			if (e.type == SDL_KEYDOWN) {

				// directions
				if (e.key.keysym.sym == SDLK_LEFT && !hang_selector_move_left){
					I->selectorMove(LEFT);
					hang_selector_move_left = 1;
				}

				if (e.key.keysym.sym == SDLK_RIGHT && !hang_selector_move_right){
					I->selectorMove(RIGHT);
					hang_selector_move_right = 1;
				}

				if (e.key.keysym.sym == SDLK_UP && !hang_selector_move_up){
					I->selectorMove(UP);
					hang_selector_move_up = 1;
				}

				if (e.key.keysym.sym == SDLK_DOWN && !hang_selector_move_down){
					I->selectorMove(DOWN);
					hang_selector_move_down = 1;
				}

				
				// commands
				if (e.key.keysym.sym == SDLK_e){
					I->interact();
				}

				if (e.key.keysym.sym == SDLK_d){
					I->drop();
				}

				if (e.key.keysym.sym == SDLK_m){
					I->itemSwap();
				}


				if (e.key.keysym.sym == SDLK_g){
					int random = rand() % 4; // TODO: define total items
					if (random == 0){
						I->add(new Apple());
					} else if (random == 1){
						I->add(new Knife());
					} else if (random == 2){
						I->add(new Notebook());
					} else if (random == 3){
						I->add(new MP3Player());
					}
				}

				if (e.key.keysym.sym == SDLK_b){
					I->changeBuffer();
				}

				if (e.key.keysym.sym == SDLK_y){
					I->swapItemBuffer();
				}

				if (e.key.keysym.sym == SDLK_ESCAPE){
					quit = true;
				}
			}
		}


		window.clear();

		// draw background image
		window.render(tx_bg, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

		//draw inventory
		I->draw(window);

		window.show();
	}

}




int main(int argc, char **argv){
	argc--; //disregard binary name

	// Call this first since we are using our custom main function instead of SDL_Main (due to '#define SDL_MAIN_HANDLED' at the top)
	SDL_SetMainReady();
	// start SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	
	// initialize SDL_IMAGE
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
		logSDLError("IMG_Init");
		SDL_Quit();
		return 1;
	}

	//Initialize SDL_mixer 
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		return 1;
	}


	srand(time(NULL)); // set the random seed

	loadSound("song.wav", audio_song, 75);
	loadSound("error.wav", audio_error, 100);
	loadSound("ambi.wav", audio_ambi, 55);
	loadSound("grab.wav", audio_grab, 65);
	loadSound("release.wav", audio_release, 65);
	loadSound("swap.wav", audio_swap, 65);
	loadSound("move_selector.wav", audio_move_selector);

	Mix_FadeInChannel(2, audio_ambi, -1, 2000); // start ambience


	RenderWindow window;


	// load textures
	window.loadAllTextures();
	
	// call main program loop
	programLoop(argc, argv, window);


	//TODO: free all sounds
	//TODO: specifiy sizes for individual textures

	window.cleanup();

	Mix_CloseAudio();
	IMG_Quit(); // quit SDL_Image
	SDL_Quit();
	return 0;
}



