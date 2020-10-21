#include "mySDL.h"


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
	if (tex == nullptr){
		logSDLError("load texture");
	}

	return tex;
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


