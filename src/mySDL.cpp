#include "mySDL.h"
#include "debug.h"

std::string getResourcePath(const std::string &subDir){
	//We need to choose the path separator properly based on which
	//platform we're running on, since Windows uses a different
	//separator than most systems
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	//This will hold the base resource path: Lessons/res/
	//We give it static lifetime so that we'll only need to call
	//SDL_GetBasePath once to get the executable path
	static std::string baseRes;
	if (baseRes.empty()){
		//SDL_GetBasePath will return NULL if something went wrong in retrieving the path
		char *basePath = SDL_GetBasePath();
		//printf("%s\n", basePath);
		if (basePath){
			baseRes = basePath;
			SDL_free(basePath);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = baseRes.rfind("bin");
		baseRes = baseRes.substr(0, pos) + "res" + PATH_SEP;
	}
	//If we want a specific subdirectory path in the resource directory
	//append it to the base path. This would be something like Lessons/res/Lesson0
	return subDir.empty() ? baseRes : baseRes + subDir + PATH_SEP;
}



void logSDLError(const std::string &msg){
	std::cerr << msg << " error: " << SDL_GetError() << std::endl;
}



SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
	SDL_Texture *tex = IMG_LoadTexture(ren, file.c_str());
	if (!tex) {logSDLError("load texture");}

	return tex;
}


void loadSound(const std::string &file, Mix_Chunk*& chunk, int volume){
	chunk = Mix_LoadWAV((basePath + "audio\\" + file).c_str());
	if (!chunk) {std::cout << "load texture" << Mix_GetError() << std::endl; return;}
	Mix_VolumeChunk(chunk, volume);
}



void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y, int w, int h){
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}



void renderTexture(SDL_Renderer *ren, SDL_Texture *tex, int x, int y){
	//Setup the destination rectangle to be at the position we want
	//Query the texture to get its width and height to use
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	renderTexture(ren, tex, x, y, w, h);
}

int center(int big_xy, int little_xy){
	return big_xy / 2 - little_xy / 2;
}




RenderWindow::RenderWindow(){

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	int ENTIRE_SCREEN_W = DM.w;
	int ENTIRE_SCREEN_H = DM.h;

	// create window
	this->win = SDL_CreateWindow("Dual Inventory Demo", center(DM.w, SCREEN_WIDTH), center(DM.h, SCREEN_HEIGHT), SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		logSDLError("create window");
	}

	// give window icon
	SDL_Surface *icon = IMG_Load((basePath + "icon.png").c_str());
	SDL_SetWindowIcon(win, icon);

	// make renderer
	this->ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		logSDLError("create renderer");
	}
}


void RenderWindow::render(SDL_Texture *texture, int x, int y, int w, int h){
	renderTexture(this->ren, texture, x, y, w, h);
}


void RenderWindow::clear(){
	SDL_RenderClear(this->ren); // Clear the screen
}

void RenderWindow::show(){
	SDL_RenderPresent(this->ren); // Update the screen
}

void RenderWindow::loadAllTextures(){
	tx_bg = loadTexture(basePath + "bg.png", ren);
	tx_cell = loadTexture(basePath + "InventoryCell.png", ren);
	tx_cell_select = loadTexture(basePath + "InventoryCellSelect.png", ren);
	tx_apple = loadTexture(basePath + "apple.png", ren);
	tx_knife = loadTexture(basePath + "knife.png", ren);
	tx_notebook = loadTexture(basePath + "notebook.png", ren);
	tx_mp3player = loadTexture(basePath + "mp3player.png", ren);
	tx_cell_bg = loadTexture(basePath + "cell_bg.png", ren);
}

void RenderWindow::cleanup(){
	SDL_DestroyTexture(tx_bg);
	SDL_DestroyTexture(tx_cell);
	SDL_DestroyTexture(tx_cell_select);
	SDL_DestroyTexture(tx_apple);
	SDL_DestroyTexture(tx_knife);
	SDL_DestroyTexture(tx_notebook);
	SDL_DestroyTexture(tx_mp3player);
	SDL_DestroyTexture(tx_cell_bg);

	SDL_DestroyRenderer(this->ren);
	SDL_DestroyWindow(this->win);
}



void play(Mix_Chunk *sample, int channel){
	Mix_PlayChannel(channel, sample, 0);
}


void loop(Mix_Chunk *sample, int channel){
	Mix_PlayChannel(channel, sample, -1);
}

