#pragma once
#include "Items.h"
#include <SDL.h>
#include "mySDL.h"

class ItemBufferFullError : public std::exception {};


class ItemBuffer {
private:
	uint size, slots_per_row;
	Item** array;
	uint mSelectorPos;
	uint mSwapHoldIndex; // index of item we are holding to swap

public:
	ItemBuffer();
	ItemBuffer(uint init_size, uint slots_per_row) : size(init_size), slots_per_row(slots_per_row),
		array(new Item*[init_size]), mSelectorPos(0) {
			// fill buffer with nullptr to avoid accessing garbage memory
			for (uint i = 0; i < size; ++i){
				array[i] = nullptr;
			}
		};

	ItemBuffer& operator=(const ItemBuffer& rhs);
	~ItemBuffer();

	uint getSize();
	Item*& at(uint idx);
	Item* get(uint idx);
	void add(Item* new_item, bool& placed);
	void drop();
	void show(ItemBuffer* curr_buffer);
	uint firstEmpty();
	void interact();
	void selectorMove(Direction dir);
	bool inBounds(int pos);
	Item*& selectedItem();
	uint getSelectorPos();
	uint getSwapHoldIndex();
	void setSwapHoldIndex();
	void draw(RenderWindow window, int x, int y, Justify just, const ItemBuffer *curr_buffer);
};


