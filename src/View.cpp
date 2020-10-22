#include "View.h"


namespace render {

	void drawInventory(SDL_Renderer *ren, Inventory* I){
		uint active_size = I->getActiveSize();
		uint other_size = I->getOtherSize();

		int cell_w = 100;
		int cell_h = 100;
		int item_w = 50;
		int item_h = 50;
		int select_scalar = 10;

		// cannot declare this globally as is; it will be statically bound to the unallocated texture pointers :C
		std::map <std::string, SDL_Texture*> mapItemTexture = {
			{"apple", tx_apple},
			{"notebook", tx_notebook},
			{"knife", tx_knife},
			{"mp3player", tx_mp3player}
		};

		for (uint i = 0; i < active_size; ++i) {
			int x = SCREEN_WIDTH/2 - (cell_w * active_size/2) + (cell_w * i);
			int y = SCREEN_HEIGHT/2 - cell_h/2; 			//vertical center

			// render cells and items
			renderTexture(ren, tx_cell, x, y, cell_w, cell_h);
		}



		for (uint i = 0; i < active_size; ++i) {
			int x = SCREEN_WIDTH/2 - (cell_w * active_size/2) + (cell_w * i);
			int y = SCREEN_HEIGHT/2 - cell_h/2;
			if (i == I->mCurrBuffer->getSelectorPos()){
				renderTexture(ren, tx_cell_select, x - select_scalar/2, y - select_scalar/2, cell_w + select_scalar, cell_h + select_scalar);
			}

			Item* item = I->mCurrBuffer->get(i);
			if (item != nullptr){
				//auto it = mapItemTexture.find("apple"); if (it != mapItemTexture.end()) log("its there!");
				//it = mapItemTexture.find(n); if (it != mapItemTexture.end()) log("its there!");
				SDL_Texture *item_tex = mapItemTexture[item->getName()];
				if (item_tex == nullptr){
					log("bad texture map index");
				}
				renderTexture(ren, item_tex, x + cell_w/2 - item_w/2, y + cell_h/2 - item_h/2, item_w, item_h);
			}
		}

	}
}
