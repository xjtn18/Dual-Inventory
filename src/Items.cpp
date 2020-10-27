#include "Items.h"
#include "debug.h"
#include "mySDL.h"


std::string Item::getName(){
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
	log("ate apple", true);
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
	log("jotted something down in your notebook");
}



// KNIFE 
void Knife::interact(){
	log("flipped knife", true);
}



// MP3 PLAYER
void MP3Player::interact(){
	if (!Mix_Playing(0)){
		Mix_FadeInChannel(0, audio_song, 0, 500);
	} else if (Mix_Paused(0)){
		Mix_Resume(0);
	} else {
		Mix_Pause(0);
	}
}


