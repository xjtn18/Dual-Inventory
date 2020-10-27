#include "ItemBuffer.h"
#include <math.h>


// constants as of now, so can placed at the top here
namespace {
	int cell_w = 100;
	int cell_h = 100;
	int item_w = 50;
	int item_h = 50;
	int select_scalar = 10;
}



ItemBuffer::ItemBuffer()
	: size(0), slots_per_row(0),
		array(nullptr), mSelectorPos(0) {}



ItemBuffer& ItemBuffer::operator=(const ItemBuffer& rhs){
	size = rhs.size;
	slots_per_row = rhs.slots_per_row;
	mSelectorPos = rhs.mSelectorPos;
	delete[] array;												/// THIS IS NEW - may cause segfault or memleak
	array = new Item*[rhs.size];
	for (uint i = 0; i < rhs.size; ++i){
		array[i] = rhs.array[i];
	}
	return *this;
}



ItemBuffer::~ItemBuffer(){
	if (this->size)
	for (uint i = 0; i < this->size; ++i){
		delete this->array[i]; // delete each item
	}
	delete[] this->array; // delete the array
}



void ItemBuffer::add(Item* new_item, bool& placed){
	if (placed) return; // if this item has already be stored somewhere
	for (uint i = 0; i < this->size; ++i){
		if (this->array[i] == nullptr){
			this->array[i] = new_item;
			placed = true;
			return;
		}
	}
}



void ItemBuffer::drop(){
	if (this->array[mSelectorPos] == nullptr){
		play(audio_error);
	}
	this->array[mSelectorPos] = nullptr;
}



void ItemBuffer::interact(){
	Item* item = this->array[mSelectorPos];
	if (item != nullptr){
		item->interact();
		if (item->isConsumable()){
			this->drop();
		}
	} else { // no item here
		play(audio_error);
	}
}



Item*& ItemBuffer::at(uint idx){
	return this->array[idx];
}



Item* ItemBuffer::get(uint idx){
	return this->array[idx];
}



uint ItemBuffer::getSize(){
	return this->size;
}



uint ItemBuffer::firstEmpty(){
	for (uint i = 0; i < this->size; ++i){
		if (this->array[i] == nullptr){
			return i;
		}
	}
	throw ItemBufferFullError();
}



bool ItemBuffer::inBounds(int pos){
	return (pos >= 0 && pos < (int) this->size);
}



void ItemBuffer::selectorMove(Direction dir){
	if (dir == UP){
		if (inBounds(mSelectorPos - slots_per_row)){
			mSelectorPos -= slots_per_row;
		}

	} else if (dir == RIGHT){
		if (inBounds(mSelectorPos + 1) && (mSelectorPos % slots_per_row != slots_per_row - 1)){
			mSelectorPos++;
		}

	} else if (dir == DOWN){
		if (inBounds(mSelectorPos + slots_per_row)){
			mSelectorPos += slots_per_row;
		}

	} else if (dir == LEFT){
		if (inBounds(mSelectorPos - 1) && (mSelectorPos % slots_per_row != 0)){
			mSelectorPos--;
		}
	}
	//play(audio_move_selector);
}



Item*& ItemBuffer::selectedItem(){
	return this->array[mSelectorPos];
}



void ItemBuffer::setSwapHoldIndex(){
	mSwapHoldIndex = mSelectorPos;
}



uint ItemBuffer::getSwapHoldIndex(){
	return mSwapHoldIndex;
}



uint ItemBuffer::getSelectorPos(){
	return mSelectorPos;
}



void ItemBuffer::draw(RenderWindow window, int xset, int yset, Justify just, const ItemBuffer *curr_buffer){

	// cannot declare this globally as is; it will be statically bound to the unallocated texture pointers :C
	std::map <std::string, SDL_Texture*> mapItemTexture = {
		{"apple", tx_apple},
		{"notebook", tx_notebook},
		{"knife", tx_knife},
		{"mp3player", tx_mp3player}
	};

	int x, y, row_shift = 0, col_shift = 0;

	// render cells

	for (uint i = 0; i < this->size; ++i) {

		x = xset + col_shift;
		y = yset + row_shift;
		switch (just){
			case NONE:
				break;
			case HCENTER:
				x -= (cell_w * this->slots_per_row / 2);
				break;
			case VCENTER:
				y -= (cell_h * floor(this->size / this->slots_per_row) / 2);
				break;
		}

		if (i % this->slots_per_row == slots_per_row - 1) {
			row_shift += cell_h;
			col_shift = 0;
		} else {
			col_shift += cell_w;
		}

		window.render(tx_cell_bg, x, y, cell_w-2, cell_h-2);
	}

	row_shift = 0;
	col_shift = 0;
	for (uint i = 0; i < this->size; ++i) {

		x = xset + col_shift;
		y = yset + row_shift;
		switch (just){
			case NONE:
				break;
			case HCENTER:
				x -= (cell_w * this->slots_per_row / 2);
				break;
			case VCENTER:
				y -= (cell_h * floor(this->size / this->slots_per_row) / 2);
				break;
		}

		if (i % this->slots_per_row == slots_per_row - 1) {
			row_shift += cell_h;
			col_shift = 0;
		} else {
			col_shift += cell_w;
		}

		window.render(tx_cell, x, y, cell_w, cell_h);
	}



	// render selector and items
	row_shift = 0;
	col_shift = 0;
	for (uint i = 0; i < this->size; ++i) {

		x = xset + col_shift;
		y = yset + row_shift;
		switch (just){
			case NONE:
				break;
			case HCENTER:
				x -= (cell_w * this->slots_per_row / 2);
				break;
			case VCENTER:
				y -= (cell_h * floor(this->size / this->slots_per_row) / 2);
				break;
		}

		if (i % this->slots_per_row == slots_per_row - 1) {
			row_shift += cell_h;
			col_shift = 0;
		} else {
			col_shift += cell_w;
		}

		if (this == curr_buffer && i == this->getSelectorPos()){
			window.render(tx_cell_select, x - select_scalar/2, y - select_scalar/2, cell_w + select_scalar, cell_h + select_scalar);
		}

		// render items
		Item* item = this->get(i);
		if (item != nullptr){
			//auto it = mapItemTexture.find("apple"); if (it != mapItemTexture.end()) log("its there!");
			//it = mapItemTexture.find(n); if (it != mapItemTexture.end()) log("its there!");
			SDL_Texture *item_tex = mapItemTexture[item->getName()];
			if (item_tex == nullptr){
				log("bad texture map index");
				buffer("");
			}
			
			window.render(item_tex, x + cell_w/2 - item_w/2, y + cell_h/2 - item_h/2, item_w, item_h);
		}
	}
}


