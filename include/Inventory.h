#pragma once
#include "debug.h"
#include "ItemBuffer.h"



class Inventory {
// This class stores 2 spaces:
// 		1. An active inventory space
// 		2. Secondary side inventory space
// Each spaces stores pointers to and abstract Item.
// User can add, remove, swap, and use items within the inventory.
private:
	ItemBuffer active_space, other_space;
	ItemBuffer* mCurrBuffer;
	ItemBuffer* mOppBuffer;
	ItemBuffer* mItemSwap_StartBuffer = nullptr;
	

public:
	Inventory();
	Inventory(uint a, uint o);
	Inventory& operator=(const Inventory& rhs);
	~Inventory();
	uint getActiveSize();
	uint getOtherSize();
	void add(Item* new_item);
	void interact();
	void drop();
	void itemSwap();
	void swapItemBuffer();
	void changeBuffer();
	void showAll();
	void selectorMove(Direction dir);
};

