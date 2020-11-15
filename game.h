#ifndef GAME
#define GAME

#include "globals.h"
#include "hero.h"
#include "wall.h"
#include "glob.h"
#include "grob.h"
#include "bat.h"
#include "droid.h"
#include "keyboardInput.h"
#include "drawing_functions.h"
#include "soundManager.h"
#include "CameraController.h"
#include "TMXLoader.h"
#include <SDL2/SDL_image.h>

class Game{
public:
	Mix_Music* song;

	AnimationSet* heroAnimSet;
	AnimationSet* globAnimSet;
	AnimationSet* grobAnimSet;
	AnimationSet* wallAnimSet;
	AnimationSet* batAnimSet;
	AnimationSet* droidAnimSet;

	SDL_Texture* backgroundImage;
	SDL_Texture* splashImage;
	SDL_Texture* overlayImage;

	SDL_Texture* scoreTexture = NULL; //for drawing strings to the screen

	Hero *hero;
	KeyboardInput heroInput;

	list<Entity*> enemies;
	list<Entity*> walls;

	bool splashShowing;
	float overlayTimer;
	CameraController camController;
	TMXLoader* loader;
	SDL_Texture* spriteSheet;
	Game();
	~Game();

	void update();
	void draw(SDL_Texture* texture);
	// void render();

};


#endif