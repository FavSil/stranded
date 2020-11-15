#ifndef GLOBALS
#define GLOBALS

#include <string>
#include <iostream>
#include <SDL.h>
#include "randomNumber.h"

using namespace std;

class Globals{
public:
//lazy foo level start
	static const int LEVEL_WIDTH = 1280;
	static const int LEVEL_HEIGHT = 960;
	 //Tile constants
	static const int TILE_WIDTH = 80;
	static const int TILE_HEIGHT = 80;
	static const int TOTAL_TILES = 192;
	static const int TOTAL_TILE_SPRITES = 12;

	//The different tile sprites
	static const int TILE_RED = 0;
	static const int TILE_GREEN = 1;
	static const int TILE_BLUE = 2;
	static const int TILE_CENTER = 3;
	static const int TILE_TOP = 4;
	static const int TILE_TOPRIGHT = 5;
	static const int TILE_RIGHT = 6;
	static const int TILE_BOTTOMRIGHT = 7;
	static const int TILE_BOTTOM = 8;
	static const int TILE_BOTTOMLEFT = 9;
	static const int TILE_LEFT = 10;
	static const int TILE_TOPLEFT = 11;




	//math helpers
	static const float PI;
	static const int tileHeight;
	static const int tileWidth;
	//useful for me as a dev
	static bool debugging;

	//sdl related
	static int ScreenWidth, ScreenHeight, ScreenScale;
	static SDL_Renderer* renderer;

	//clips off header. e.g "clip: 50 114 44 49" turns into "50 114 44 49"
	static string clipOffDataHeader(string data);

	//camera
	static SDL_Rect camera;
	// static LTexture gTileTexture;
	// static SDL_Rect gTileClips[];
};

#endif