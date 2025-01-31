#include "game.h"

Game::Game(){
	string resPath = getResourcePath();
	backgroundImage = loadTexture(resPath + "map.png", Globals::renderer);
	splashImage = loadTexture(resPath + "cyborgtitle.png", Globals::renderer);
	overlayImage = loadTexture(resPath + "overlay.png", Globals::renderer);
	
	splashShowing = false;
	overlayTimer = 2;


	//Setup Camera
	Globals::camera.x = 0;
	Globals::camera.y = 0;
	Globals::camera.w = Globals::ScreenWidth;
	Globals::camera.h = Globals::ScreenHeight;


	//load up sounds
	SoundManager::soundManager.loadSound("hit", resPath + "hit.wav");
	SoundManager::soundManager.loadSound("enemyHit", resPath + "Hit_Hurt9.wav");
	SoundManager::soundManager.loadSound("swing", resPath + "hit.wav");
	SoundManager::soundManager.loadSound("dash", resPath + "dash.wav");
	SoundManager::soundManager.loadSound("growl", resPath + "Randomize34.wav");
	SoundManager::soundManager.loadSound("enemyDie", resPath + "Randomize41.wav");

	song = Mix_LoadMUS(string(resPath + "strandedTheme.wav").c_str());//Song by Ryan Beveridge https://soundcloud.com/ryan-beveridge
	// if (song != NULL)
	// 	Mix_PlayMusic(song, -1);

	//holds a list of group types. this list describes the types of groups of data our frames can have!
	list<DataGroupType> dataGroupTypes;

	//so what data can a frame have?
	//collisionBoxes (although we have hardcoded the collision boxes)
	DataGroupType colBoxType;
	colBoxType.groupName = "collisionBox";
	colBoxType.dataType = DataGroupType::DATATYPE_BOX;

	//hitboxes
	DataGroupType hitBoxType;
	hitBoxType.groupName = "hitBox";
	hitBoxType.dataType = DataGroupType::DATATYPE_BOX;

	//damage
	DataGroupType dmgType;
	dmgType.groupName = "damage";
	dmgType.dataType = DataGroupType::DATATYPE_NUMBER;

	//add all of these dataTypes to the list
	dataGroupTypes.push_back(colBoxType);
	dataGroupTypes.push_back(hitBoxType);
	dataGroupTypes.push_back(dmgType);

	heroAnimSet = new AnimationSet();
	heroAnimSet->loadAnimationSet("stranded.fdset", dataGroupTypes, false, 0, true);

	globAnimSet = new AnimationSet();
	globAnimSet->loadAnimationSet("glob.fdset", dataGroupTypes, false, 0, true);
	
	batAnimSet = new AnimationSet();
	batAnimSet->loadAnimationSet("bat.fdset", dataGroupTypes, false, 0, true);

	droidAnimSet = new AnimationSet();
	droidAnimSet->loadAnimationSet("droid.fdset", dataGroupTypes, false, 0, true);

	grobAnimSet = new AnimationSet();
	grobAnimSet->loadAnimationSet("grob.fdset", dataGroupTypes, true, 0, true);

	wallAnimSet = new AnimationSet();
	wallAnimSet->loadAnimationSet("wall.fdset", dataGroupTypes);

	//build hero entity
	hero = new Hero(heroAnimSet);
	hero->invincibleTimer = 0;
	hero->x = Globals::ScreenWidth / 2;
	hero->y = Globals::ScreenHeight / 2;
	//tells keyboard input to manage hero
	heroInput.hero = hero;
	//add hero to the entity list
	Entity::entities.push_back(hero);


	//Get camera to follow hero
	camController.target = hero;

    spriteSheet = loadTexture(resPath + "maptest.png", Globals::renderer);


    loader = new TMXLoader();
    loader->loadMap("testmap", "res/S2.tmx");
    loader->printMapData("testmap");
    



	// int tileSize = 32;
	// //build all the walls for this game
	// //first. build walls on top and bottom of screen
	// for (int i = 0; i < (Globals::ScreenWidth*2) / tileSize; i++){
	// 	//fills in top row
	// 	Wall* newWall = new Wall(wallAnimSet);
	// 	newWall->x = i * tileSize + tileSize/2;
	// 	newWall->y = tileSize / 2;
	// 	walls.push_back(newWall);
	// 	Entity::entities.push_back(newWall);

	// 	//re-using pointer to create bottom row
	// 	newWall = new Wall(wallAnimSet);
	// 	newWall->x = i * tileSize + tileSize / 2;
	// 	newWall->y = (Globals::ScreenHeight *2) - tileSize / 2;
	// 	walls.push_back(newWall);
	// 	Entity::entities.push_back(newWall);
	// }
	// //now the sides
	// for (int i = 1; i < (Globals::ScreenHeight*2) / tileSize - 1; i++){
	// 	//fills in left column
	// 	Wall* newWall = new Wall(wallAnimSet);
	// 	newWall->x = tileSize / 2;
	// 	newWall->y = i*tileSize + tileSize / 2;
	// 	walls.push_back(newWall);
	// 	Entity::entities.push_back(newWall);

	// 	//re-using pointer to create right column
	// 	newWall = new Wall(wallAnimSet);
	// 	newWall->x = (Globals::ScreenWidth * 2) - tileSize / 2;
	// 	newWall->y = i*tileSize + tileSize / 2;
	// 	walls.push_back(newWall);
	// 	Entity::entities.push_back(newWall);
	// }

}

Game::~Game(){
	cleanup(backgroundImage);
	cleanup(splashImage);
	cleanup(overlayImage);

	Mix_PausedMusic();
	Mix_FreeMusic(song);

	if (scoreTexture != NULL) //if used then cleanup
		cleanup(scoreTexture);

	Entity::removeAllFromList(&Entity::entities, false);

	delete heroAnimSet;
	delete globAnimSet;
	delete grobAnimSet;
	delete wallAnimSet;
	delete batAnimSet;
	delete droidAnimSet;

	delete hero;

	//delete all of the wall entities
	Entity::removeAllFromList(&walls, true);
	Entity::removeAllFromList(&enemies, true);
}

void Game::update(){
	//enemy related
	int enemiesToBuild = 1;
	int enemiesBuilt = 0;
	float enemyBuildTimer = 5;

	bool quit = false;

	SDL_Event e;
	//setup my time controller before the game starts
	TimeController::timeController.reset();
	//game loop!
	while (!quit){
		TimeController::timeController.updateTime();

		Entity::removeInactiveEntitiesFromList(&Entity::entities, false);
		//remove/delete enemies in the enemy list who are dead/inactive
		Entity::removeInactiveEntitiesFromList(&enemies, true);

		//check for any events that might have happened
		while (SDL_PollEvent(&e)){
			//close the window
			if (e.type == SDL_QUIT)
				quit = true;
			//if keydown event
			if (e.type == SDL_KEYDOWN){
				//switch case on which button was pressed
				switch (e.key.keysym.scancode){
				case SDL_SCANCODE_ESCAPE: //esc key
					quit = true;
					break;
				case SDL_SCANCODE_SPACE:
					if (splashShowing)
						splashShowing = false;
					if (overlayTimer <= 0 && hero->hp < 1){
						//cleanup and restart the game
						enemiesToBuild = 1;
						enemiesBuilt = 0;
						enemyBuildTimer = 3;
						overlayTimer = 2;

						// Glob::globsKilled = 0;
						// Grob::grobsKilled = 0;
						if (scoreTexture != NULL){
							cleanup(scoreTexture);
							scoreTexture = NULL;
						}

						//remove all existing enemies
						for (list<Entity*>::iterator enemy = enemies.begin(); enemy != enemies.end(); enemy++){
							(*enemy)->active = false;
						}
						hero->revive();
					}
					
					break;
				default:
					break;
				}
			}
			heroInput.update(&e);
		}
		//make our overlay timer tick down
		if (hero->hp < 1 && overlayTimer > 0){
			overlayTimer -= TimeController::timeController.dT;
		}

		//update all entities
		for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++){
			//update all entities in game world at once
			(*entity)->update();
		}

		//spawn enemies
		if (hero->hp > 0 && !splashShowing){
			if (enemiesToBuild == enemiesBuilt){
				// enemiesToBuild = enemiesToBuild * 2;
				enemiesBuilt = 0;
				enemyBuildTimer = 4;
			}
			enemyBuildTimer -= TimeController::timeController.dT;
			if (enemyBuildTimer <= 0 && enemiesBuilt < enemiesToBuild && enemies.size() < 1){
				Droid *enemy = new Droid(droidAnimSet);
				//set enemies position to somewhere random within the arena's open space
				enemy->x = getRandomNumber(Globals::ScreenWidth - (2 * 32) - 32) + 32 + 16;
				enemy->y = getRandomNumber(Globals::ScreenHeight - (2 * 32) - 32) + 32 + 16;
				// enemy->invincibleTimer = 0.1;

				enemies.push_back(enemy);
				Entity::entities.push_back(enemy);

			}
			// if (enemyBuildTimer <= 0 && enemiesBuilt < enemiesToBuild && enemies.size() < 2){
			// 	Bat *enemy = new Bat(batAnimSet);
			// 	//set enemies position to somewhere random within the arena's open space
			// 	enemy->x = getRandomNumber(Globals::ScreenWidth - (2 * 32) - 32) + 32 + 16;
			// 	enemy->y = getRandomNumber(Globals::ScreenHeight - (2 * 32) - 32) + 32 + 16;
			// 	// enemy->invincibleTimer = 0.1;

			// 	enemies.push_back(enemy);
			// 	Entity::entities.push_back(enemy);

			// }
		}

		//update camera positions
		camController.update();

		//draw all entities
		draw(spriteSheet);
	}

}
void Game::draw(SDL_Texture* texture){
	//clear the screen
	SDL_SetRenderDrawColor(Globals::renderer, 145, 133, 129, SDL_ALPHA_TRANSPARENT);
	SDL_RenderClear(Globals::renderer);

   
    char tileID = 0;
    
    int tileWidth = loader->getMap("testmap")->getTileWidth();
    int tileHeight = loader->getMap("testmap")->getTileHeight();
    for (int i = 0; i < loader->getMap("testmap")->getHeight(); ++i)
    {
        for (int j = 0; j < loader->getMap("testmap")->getWidth(); ++j)
        {
            // get the tile at current position
            tileID = loader->getMap("testmap")->getTileLayer("Tile Layer 1")->getTileVector()[i][j];
            
            // only render if it is an actual tile (tileID = 0 means no tile / don't render anything here)
            if (tileID > 0)
            {
                SDL_Rect srcrect = { ((tileID - 1) % 4) * tileWidth, ((tileID - 1) / 4) * tileHeight, tileWidth, tileHeight };
                SDL_Rect dstrect = { (j * 32)-Globals::camera.x , (i * 32)-Globals::camera.y, 32, 32 };
                SDL_RenderCopy(Globals::renderer, texture, &srcrect, &dstrect);
            }
        }
    }


	if (splashShowing){
		renderTexture(splashImage, Globals::renderer, 0, 0);
	}
	else{
		//draw the background
		// renderTexture(backgroundImage, Globals::renderer, 0-Globals::camera.x, 0-Globals::camera.y);

		//sort all entities based on y(depth)
		Entity::entities.sort(Entity::EntityCompare);
		//draw all of the entities
		for (list<Entity*>::iterator entity = Entity::entities.begin(); entity != Entity::entities.end(); entity++){
			(*entity)->draw();
		}

		if (overlayTimer <= 0 && hero->hp < 1){
			// renderTexture(overlayImage, Globals::renderer, 0, 0);
			if (scoreTexture == NULL){
				//generate score text
				SDL_Color color = { 255, 255, 255, 255 };//white

				stringstream ss;
				// ss << "Enemies dispatched: " << Glob::globsKilled + Grob::grobsKilled;

				string resPath = getResourcePath();
				scoreTexture = renderText(ss.str(), resPath + "vermin_vibes_1989.ttf", color, 30, Globals::renderer);
			}
			renderTexture(scoreTexture, Globals::renderer, 20, 50);
		}
	}
	//after we're done drawing/rendering, show it to the screen
	SDL_RenderPresent(Globals::renderer);
}
