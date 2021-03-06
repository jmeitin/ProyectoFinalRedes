#include "Game.h"
#include "../utils/Collisions.h"

Client::Client(const char* ip, const char* port, const char * n): socket(ip,port){	
	nick = n;	
}

Client::~Client(){
	if(background != nullptr) delete background;
	if(player != nullptr) delete player;
	if(player2 != nullptr) delete player2;
	freeDeadBullets(); 
	while (!MyBullets.empty()) {
		delete MyBullets.back();
		MyBullets.pop_back();
   	} 
	while (!EnemyBullets.empty()) {
		delete EnemyBullets.back();
		EnemyBullets.pop_back();
   	} 	
}

void Client::login() {	
    LogMessage em(nick);
    em.type = Message::MessageType::LOGIN;
	
    socket.send(em, socket);
}

void Client::logout() {
    LogMessage em(nick);
    em.type = Message::MessageType::LOGOUT;

    socket.send(em, socket);

	exit_ = true;
}

void Client::net_thread() {
    while(true) {
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        Message message;
		char buffer[Message::MESSAGE_SIZE];
        socket.recv(message,buffer);

		if(!playing && message.type == Message::MessageType::CONFIRMATION){
		
			PlayerMsg playerm1; playerm1.from_bin(buffer);

			MyPlayerID = playerm1.player;

			startGame();
			
			playing = true;			
			continue;
		}

		if(playing){
			if (message.type == Message::MessageType::PLAYERPOS){
				Object playerm2; playerm2.from_bin(buffer);
				player2->move(playerm2.posx, playerm2.posy, playerm2.rot);
			}
			else if (message.type == Message::MessageType::SHOT){
				PlayerMsg bullet; bullet.from_bin(buffer);
				pair <int,int> aux{player2->GetPosition().first, player2->GetPosition().second};
				//INSTANCIA BALA ==> EnemyBullets
				crearBalaEnemiga(aux, player2->getRot());
			}
			else if (message.type == Message::MessageType::PlAYERKILLED){		
				std::cout << "ganaste"<< "\n"		;
				logout();
				break;
			}
			
		}
    }
}

void Client::startGame(){
    // Initialise the SDLGame singleton
	try{
	SDLUtils::init("SDLGame Demo!", WIDTH, HEIGHT,
			"../resources/config/sdlutilsdemo.resources.json");
	}
	catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught and exception of unknown type ...";
	}
	
    sdl = SDLUtils::instance();

    // show the cursor
	sdl->showCursor();

	// store the 'renderer' in a local variable, just for convenience
	renderer = sdl->renderer();

	// crear jugadores
	player = new Player(this, &sdl->images().at("fighter"),posiciones[MyPlayerID].first,posiciones[MyPlayerID].second, SPEED, WIDTH, HEIGHT);
	int otherID = (MyPlayerID + 1) % 2	;
	player2 = new Player(this, &sdl->images().at("fighter"),posiciones[otherID].first,posiciones[otherID].second, SPEED, WIDTH, HEIGHT);

	background = &sdl->images().at("background"); //FONDO ESTRELLAS
	
	ih = InputHandler::instance();    

	//sdl->musics().at("beat").play();
}

void Client::game_thread(){
	//BUCLE DE JUEGO
    while (!exit_) {
		if(ih != nullptr){
			// update the event handler
			ih->refresh();

			//SALIR DEL JUEGO
			if (ih->keyDownEvent() ) {
				if(ih->isKeyDown(SDLK_q)){
					logout();
					exit_ = true;
				}
			}
		}
		//JUGANDO
		if(playing){				
			
			// clear screen
			sdl->clearRenderer();

			//ACTUALIZAR LA POSICION/ROT DE MI JUGADOR
			if(player->update()){
				Object posMsg = Object(MyPlayerID, player->GetPosition().first, player->GetPosition().second, player->getRot());
				posMsg.type = Message::MessageType::PLAYERPOS;
				socket.send(posMsg, socket);
			}

			// EnemyDeadBullets x player
			checkCollision();
			
			updateAllBullets();

			//cuando borro mis balas, se cierra mi consola de juego
			//cuando borro las balas enemigas, cierro la consola enemiga
			//freeDeadBullets();

			// RENDER---------------------------------------------------
			SDL_Rect dest = { 0, 0, WIDTH, HEIGHT };
			background->render(dest,0); //esquina 0,0
			for(Bala* bullet : MyBullets) bullet->render();
			for(Bala* bullet : EnemyBullets) bullet->render();
	
		
		 	// present new frame
	 	
			player->render();
			player2->render();			

			sdl->presentRenderer();

		
		 }
	 }

}

void Client::updateAllBullets(){
	for (auto bullet =MyBullets.begin(); bullet != MyBullets.end(); bullet++){
		(*bullet)->update();
		std::pair<int,int> currentPos = (*bullet)->GetPosition();

		//SI SE SALE DE RANGO ==> ELIMINAR
		if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  
			MyDeadBullets.push_back((*bullet));
	}

	for (auto bullet =EnemyBullets.begin(); bullet != EnemyBullets.end(); bullet++){
		(*bullet)->update();
		std::pair<int,int> currentPos = (*bullet)->GetPosition();

		//SI SE SALE DE RANGO ==> ELIMINAR
		if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
			EnemyDeadBullets.push_back((*bullet));
	}	
}

void Client::freeDeadBullets(){
	for (auto bul : MyDeadBullets){
		MyBullets.remove(bul);
		delete bul;
	}
	MyDeadBullets.clear();
	// while (!MyDeadBullets.empty()) {
	// 	MyBullets.remove(MyDeadBullets.back());
	// 	delete MyDeadBullets.back();
	// 	MyDeadBullets.pop_back();
	// } 
	for (auto bul : EnemyDeadBullets){
		EnemyBullets.remove(bul);
		delete bul;
	}
	EnemyDeadBullets.clear();
	// while (!EnemyDeadBullets.empty()) {
	// 	EnemyBullets.remove(EnemyDeadBullets.back());
	// 	delete EnemyDeadBullets.back();
	// 	EnemyDeadBullets.pop_back();
	// }
}

void Client::crearBala(pair<int,int> currentPos, float rot){
    MyBullets.push_back(new Bala(&sdl->images().at("fire"), currentPos.first, currentPos.second, SPEED, WIDTH, HEIGHT, rot));	
	PlayerMsg shot = PlayerMsg(MyPlayerID);
	shot.type = Message::MessageType::SHOT;
	socket.send(shot, socket);
	sdl->soundEffects().at("wall_hit").play();
}

void Client::crearBalaEnemiga(pair<int,int> pos, float rot){
    EnemyBullets.push_back(new Bala(&sdl->images().at("fire"), pos.first, pos.second, SPEED, WIDTH, HEIGHT, rot));	
	sdl->soundEffects().at("wall_hit").play();
}

//COLISION BALAS ENEMIGAS x PLAYER
void Client::checkCollision(){
	for (auto bullet =EnemyBullets.begin(); bullet != EnemyBullets.end(); bullet++){
        Bala* b = (*bullet);		
			if (Collisions::collidesWithRotation(
			b->getPosition2(), b->getW(), b->getH(), b->getRot(),
			player->getPosition2(), player->getW(), player->getH(), player->getRot())) {
				MyDeadBullets.push_back((*bullet));
				playing = false;

				PlayerMsg msg = PlayerMsg(MyPlayerID);
				msg.type = Message::MessageType::PlAYERKILLED;
				socket.send(msg, socket);
				logout();
				sdl->soundEffects().at("explosion").play();
				//mensaje de que he perdido -----------------------------
				int otherID = (MyPlayerID + 1) % 2	;
				std::cout<< "gan?? jugador "<< otherID << "\n";
			}			
	}
			
}
	
float Client::getSDLcurrTime(){
	return sdl->currRealTime();
}

