#include "Inventory.h"


// default constructor (declaring)
Inventory::Inventory() {}


Inventory::Inventory(uint active_size, uint other_size) // a is active space size, o is other space size
	: active_space(ItemBuffer(active_size, 10)), other_space(ItemBuffer(other_size, 3)),
		mCurrBuffer(&active_space), mOppBuffer(&other_space) {}


Inventory& Inventory::operator=(const Inventory& rhs){
	active_space = rhs.active_space;
	other_space = rhs.other_space;
	mCurrBuffer = &active_space;
	mOppBuffer = &other_space;
	return *this;
}


Inventory::~Inventory() {} 


uint Inventory::getActiveSize(){
	return active_space.getSize();
}

uint Inventory::getOtherSize(){
	return other_space.getSize();
}



void Inventory::add(Item* new_item){
	// adds an item to the first open slot in the inventory
	if (!new_item){
		log("no such item", true);
	}
	bool placed = false;
	active_space.add(new_item, placed); // check if open slot in active inventory first
	other_space.add(new_item, placed); // then check if open slot in side inventory
	if (!placed) // no open slots anywhere
		log("Can't pickup. Inventory full", true);
}





void Inventory::itemSwap(){
	// swap item in one slot with an item in another
	if (mItemSwap_StartBuffer == nullptr){
		mItemSwap_StartBuffer = mCurrBuffer;
		mCurrBuffer->setSwapHoldIndex();
	} else {
		Item* tmp = mCurrBuffer->selectedItem();
		mCurrBuffer->at(mCurrBuffer->getSelectorPos()) = mItemSwap_StartBuffer->at(mItemSwap_StartBuffer->getSwapHoldIndex());
		mItemSwap_StartBuffer->at(mItemSwap_StartBuffer->getSwapHoldIndex()) = tmp;
		mItemSwap_StartBuffer = nullptr;
	}
}


void Inventory::swapItemBuffer(){
	// transition an item into the other inventory space (active <-> side)
	if (mCurrBuffer->selectedItem() == nullptr){
		log("no item here", true);
		return;
	}
	try {
		uint empty_idx = mOppBuffer->firstEmpty();
		mOppBuffer->at(empty_idx) = mCurrBuffer->selectedItem();
		mCurrBuffer->drop();
	} catch (ItemBufferFullError& e) {
		log("Buffer full; can't swap", true);
	}
}



void Inventory::interact(){
	Item* item = mCurrBuffer->selectedItem();
	if (item != nullptr){
		item->interact();
		if (item->isConsumable()){
			this->drop();
		}
	} else {
		log("no item here", true);
	}
}

void Inventory::drop(){
	// remove an item from the inventory
	// currently deletes memory (if object would still exist, then this would need to be changed
	mCurrBuffer->drop();
}

void Inventory::selectorMove(Direction dir){
	mCurrBuffer->selectorMove(dir);
}


void Inventory::changeBuffer(){
	ItemBuffer* tmp = mCurrBuffer;
	mCurrBuffer = mOppBuffer;
	mOppBuffer = tmp;
}


