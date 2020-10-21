#include "Items.h"
#include "debug.h"


std::string Item::getName(){
	log("in getName");
	std::cout << name << std::endl;
	return this->name;
}


bool Item::isConsumable(){
	return this->consumable;
}


void Item::interact(){
	std::cout << "\nHow would you like to interact with this " << this->name << "?" << std::endl;
}


// APPLE 
void Apple::interact(){
	log("ate apple", true, 5);
}


std::string Apple::getName(){
	log("in getName");
	std::cout << name << std::endl;
	return this->name;
}


// NOTEBOOK
void Notebook::write(){
	log("\nWrite new entry here: ", false);
	std::string input;
	std::getline(std::cin, input);
	this->notes.push_back(input);
}


void Notebook::read(){
	std::string n;
	log("");
	if (notes.size() == 0){
		log("Notebook empty");
	}
	for (uint i = 0; i < notes.size(); ++i){
		n = notes[i];
		std::cout << "Entry " << i + 1 << ": ";
		log(n);
		log("");
	}
	buffer("\n:press Enter to continue:");
}


void Notebook::interact(){
	Item::interact();
	log("");
	log("w : write");
	log("r : read");
	log("c : cancel");
	log("");
	std::string input;
	std::getline(std::cin, input);
	if (input == "w"){
		this->write();
	} else if (input == "r"){
		this->read();
	} else if (input == "c"){
		return;
	} else {
		log("no sure what that does", true, 5);
	}
}




// KNIFE 
void Knife::interact(){
	log("flipped knife", true, 5);
}



// MP3 PLAYER
void MP3Player::interact(){
	log("played mp3 player", true, 5);
}

