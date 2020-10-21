#pragma once
#include "debug.h"
#include <string>

class Item {
// Abstract base "item" class to fill the inventory
protected:
	std::string name;
	bool consumable; // boolean that states whether this item is a one-time use
public:
	std::string getName();
	bool isConsumable();
	virtual void interact();
	virtual ~Item(){};
};



class Apple : public Item {
public:
	Apple(){
		name = "Apple";
		consumable = true;
	};
	void interact();
};



class Notebook : public Item {
	std::vector<std::string> notes;

public:
	Notebook(){
		name = "Ntbok";
		consumable = false;
	};
	void interact();
	void write();
	void read();
};



class Knife : public Item {
public:
	Knife(){	
		name = "Knife";
		consumable = false;
	};
	void interact();
};


class MP3Player : public Item {
public:
	MP3Player(){	
		name = "MP3Pl";
		consumable = false;
	};
	void interact();
};



