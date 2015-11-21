/*
 * PicassoHelper.h
 *
 *  Created on: 6/9/2015
 *      Author: jorlando
 */

#ifndef MODELO_PICASSOHELPER_H_
#define MODELO_PICASSOHELPER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "DefaultSettings.h"

using namespace std;

class PicassoHelper {
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	TTF_Font* font;
	PicassoHelper();
	int widthView ;
	int highView;
	static PicassoHelper* instance;
	map<string,SDL_Texture*> mapByImagePath;
	void renderTexture(SDL_Texture *tex, int x, int y, int w, int h);
	SDL_Texture* loadTexture(const string &file);

public:
	void createContext();
	~PicassoHelper();
	void exitError(const string &message);
	void renderView();
	void clearView();
	void renderObject(const string &file, int x, int y, int w, int h);
	void renderText(int x, int y, int w, int h, string text,Uint8 r, Uint8 g, Uint8 b);
	static PicassoHelper* GetInstance();
	void renderBackgroud();
};

#endif /* MODELO_PICASSOHELPER_H_ */
