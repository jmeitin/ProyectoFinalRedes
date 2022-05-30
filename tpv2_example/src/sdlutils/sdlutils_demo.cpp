// This file is part of the course TPV2@UCM - Samir Genaim

#include <SDL.h>

#include "sdlutils_demo.h"
#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "macros.h"
#include "SDLUtils.h"

using namespace std;

void sdlutils_basic_demo() {

	// Initialise the SDLGame singleton
	SDLUtils::init("SDLGame Demo!", 800, 600,
			"resources/config/sdlutilsdemo.resources.json");

	// reference to the SDLUtils Singleton. You could use it as a pointer as well,
	// I just prefer to use . instead of ->, it is just a matter of taste, nothing
	// else!
	//
	// you can also use the inline method sdlutils() that simply returns the value
	// of *SDLUtils::instance() --- it is defined at the end of SDLUtils.h
	//
	auto &sdl = *SDLUtils::instance();

	//show the cursor
	sdl.showCursor();

	// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer *renderer = sdl.renderer();

	
	// we can take textures from the predefined ones, and we can create a custom one as well
	Player player(&sdl.images().at("sdl_logo"),10,10);

	// start the music in a loop
	sdl.musics().at("beat").play();

	// reference to the input handler (we could use a pointer, I just . rather than ->).
	// you can also use the inline method ih() that is defined in InputHandler.h
	auto &ih = *InputHandler::instance();

	// a boolean to exit the loop
	bool exit_ = false;

	while (!exit_) {
		Uint32 startTime = sdl.currRealTime();

		// update the event handler
		ih.refresh();
			
		// exit when any key is down
		if (ih.keyDownEvent() )
		{
			if(ih.isKeyDown(SDLK_q))
			exit_ = true;
		}
			

		// clear screen
		sdl.clearRenderer();

		player.update();
		player.render();
		// render Hello SDL
		// helloSDL.render(x1, y1);
		// if (x1 + helloSDL.width() > winWidth)
		// 	helloSDL.render(x1 - winWidth, y1);
		// x1 = (x1 + 5) % winWidth;

		// render Press Any Key
		//pressAnyKey.render(x0, y0);

		// render the SDLogo
		//sdlLogo.render(1, 1);

		// present new frame
		sdl.presentRenderer();

		Uint32 frameTime = sdl.currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

	// stop the music
	Music::haltMusic();

}

