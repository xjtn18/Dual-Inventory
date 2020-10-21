#pragma once
#include "debug.h"
#include <string>

// item texture declarations


class Item {
// Abstract base "item" class to fill the inventory
protected:
	std::string name = "why";
	bool consumable = false; // boolean that states whether this item is a one-time use

public:
	virtual std::string getName();
	bool isConsumable();
	virtual void interact();
	virtual ~Item(){};
};



class Apple : public Item {
public:
	Apple(){
		name = "apple";
		log(this->name);
		consumable = true;
	};
	std::string getName();
	void interact();
};



class Notebook : public Item {
	std::vector<std::string> notes;

public:
	Notebook(){
		name = "notebook";
		consumable = false;
	};
	void interact();
	void write();
	void read();
};



class Knife : public Item {
public:
	Knife(){	
		name = "knife";
		consumable = false;
	};
	void interact();
};


class MP3Player : public Item {
public:
	MP3Player(){	
		name = "mp3player";
		consumable = false;
	};
	void interact();
};



