#include "Game.h"
#include "../utils/Collisions.h"

Game::Game(){

}

void Game::start(){
    // Initialise the SDLGame singleton
	SDLUtils::init("SDLGame Demo!", WIDTH, HEIGHT,
			"resources/config/sdlutilsdemo.resources.json");

    sdl = SDLUtils::instance();

    //show the cursor
	sdl->showCursor();

	// store the 'renderer' in a local variable, just for convenience
	renderer = sdl->renderer();
	
	// we can take textures from the predefined ones, and we can create a custom one as well
	player = new Player(this, &sdl->images().at("fighter"),10,10, 10, WIDTH, HEIGHT,true);
	player2 = new Player(this, &sdl->images().at("fighter"),WIDTH-150,HEIGHT/2, 10, WIDTH, HEIGHT);
	// start the music in a loop
	//sdl->musics().at("beat").play();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	ih = InputHandler::instance();

    update();
}

void Game::update(){
    while (!exit_) {
		Uint32 startTime = sdl->currRealTime();

		// update the event handler
		ih->refresh();
			
		// exit when any key is down
		if (ih->keyDownEvent() )
		{
			if(ih->isKeyDown(SDLK_q))
			exit_ = true;
		}

		// clear screen
		sdl->clearRenderer();

		player->update();
		player2->update();

		checkCollision();

		//UPDATE----------------------------------------------------------
		for (auto bullet =bullets.begin(); bullet != bullets.end(); bullet++){
        	(*bullet)->update();
			std::pair<int,int> currentPos = (*bullet)->GetPosition();
		
        	if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
				deadBullets.push_back((*bullet));
        }

		//ELIMINAR----------------------------------------------------
    	while (!deadBullets.empty()) {
      	  	bullets.remove(deadBullets.back());
       	 	delete deadBullets.back();
       		deadBullets.pop_back();
   		} 
		//RENDER---------------------------------------------------
		for(Bala* bullet : bullets) bullet->render();

		player->render();

		player2->render();
		
		// present new frame
		sdl->presentRenderer();

		Uint32 frameTime = sdl->currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	//Music::haltMusic();
}

void Game::crearBala(pair<int,int> currentPos, bool jugadorA, double rot){

    bullets.push_back(new Bala(&sdl->images().at("fire"), currentPos.first, currentPos.second, SPEED, WIDTH, HEIGHT, rot, jugadorA));
	
}

void Game::checkCollision(){
	for (auto bullet =bullets.begin(); bullet != bullets.end(); bullet++){
        Bala* b = (*bullet);
		if(b->getCreator()){
			if (Collisions::collidesWithRotation(
			b->getPosition2(), b->getW(), b->getH(), b->getRot(),
			player2->getPosition2(), player2->getW(), player2->getH(), player2->getRot())) {
				deadBullets.push_back((*bullet));
				exit_ = true;
				std::cout<< "ganó jugador A";
			}
			
		}
		else{
			if (Collisions::collidesWithRotation(
			b->getPosition2(), b->getW(), b->getH(), b->getRot(),
			player->getPosition2(), player->getW(), player->getH(), player->getRot())) {
				deadBullets.push_back((*bullet));
				exit_ = true;
				std::cout<< "ganó jugador B";
			}
			
		}
			
    }
	
}