#include "ItemBuffer.h"


ItemBuffer::ItemBuffer()
	: size(0), slots_per_row(0),
		array(nullptr), mSelectorPos(0) {}


ItemBuffer& ItemBuffer::operator=(const ItemBuffer& rhs){
	size = rhs.size;
	slots_per_row = rhs.slots_per_row;
	mSelectorPos = rhs.mSelectorPos;
	array = new Item*[rhs.size];
	for (int i = 0; i < rhs.size; ++i){
		array[i] = rhs.array[i];
	}
	return *this;
}


ItemBuffer::~ItemBuffer(){
	if (this->size)
	for (int i = 0; i < this->size; ++i){
		delete this->array[i]; // delete each item
	}
	delete[] this->array; // delete the array
}


void ItemBuffer::add(Item* new_item, bool& placed){
	if (placed) return; // if this item has already be stored somewhere
	for (int i = 0; i < this->size; ++i){
		if (this->array[i] == nullptr){
			this->array[i] = new_item;
			placed = true;
			return;
		}
	}
}


void ItemBuffer::drop(){
	this->array[mSelectorPos] = nullptr;
}


void ItemBuffer::interact(){
	Item* item = this->array[mSelectorPos];
	if (item != nullptr){
		item->interact();
		if (item->isConsumable()){
			this->drop();
		}
	} else {
		log("no item here", true, 5);
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



void ItemBuffer::show(ItemBuffer* curr_buffer){
	for (int i = 0; i < this->size; ++i){
		if (i >= this->slots_per_row && i % this->slots_per_row == 0){
			log("");
		}
		Item* e = this->array[i];
		if (e != nullptr){
			if (i == mSelectorPos && this == curr_buffer){
				std::cout << std::left << "*" << e->getName();
				std::cout.width(4);
				std::cout << std::left << "*";
			} else {
				std::cout.width(10);
				std::cout << std::left << e->getName();
			}
		} else {
			if (i == mSelectorPos && this == curr_buffer){
				std::cout.width(10);
				std::cout << std::left << "*  _  *";
			} else {
				std::cout.width(10);
				std::cout << std::left << "   _   ";
			}
		}
	}
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
	return (pos >= 0 && pos < this->size);
}


void ItemBuffer::selectorMove(Direction dir){
	if (dir == UP){
		if (inBounds(mSelectorPos - slots_per_row)){
			mSelectorPos -= slots_per_row;
		}

	} else if (dir == RIGHT){
		if (inBounds(mSelectorPos + 1)){
			mSelectorPos++;
		}

	} else if (dir == DOWN){
		if (inBounds(mSelectorPos + slots_per_row)){
			mSelectorPos += slots_per_row;
		}

	} else if (dir == LEFT){
		if (inBounds(mSelectorPos - 1)){
			mSelectorPos--;
		}
	}
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



