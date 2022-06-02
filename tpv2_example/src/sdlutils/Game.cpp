#include "Game.h"
#include "../utils/Collisions.h"

Client::Client(const char* ip, const char* port, std::string n, int np){
	nick = n;
	socket = Socket(ip,port);
	MyPlayerID = (host_t)np;
}

void Client::login()
{
    LogMessage em(nick);
    em.type = LogMessage::LOGIN;

    socket.send(em, socket);
}

void Client::logout()
{
    LogMessage em(nick);
    em.type = LogMessage::LOGOUT;

    socket.send(em, socket);
}

void Client::net_thread()
{
    while(true)
    {
        //Recibir Mensajes de red
        //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
        Message message;
		char buffer[Message::MESSAGE_SIZE];
        socket.recv(message,buffer);
		if(!playing && message.type == Message::MessageType::CONFIRMATION){
			 playing = true;
		}
      
      

		if(playing){
			if (message.type == Message::MessageType::PLAYERPOS){
				Object player; player.from_bin(buffer);
			}
			else if (message.type == Message::MessageType::SHOT){
				Object player; player.from_bin(buffer);
			}
			else if (message.type == Message::MessageType::PlAYERKILLED){
				PlayerKilled player; player.from_bin(buffer);
			}
			else if(message.type == Message::MessageType::LOGOUT){
				playing = false;
				break;
			}
		}
    }
}

void Client::startGame(){
    // Initialise the SDLGame singleton
	SDLUtils::init("SDLGame Demo!", WIDTH, HEIGHT,
			"resources/config/sdlutilsdemo.resources.json");

    sdl = SDLUtils::instance();

    //show the cursor
	sdl->showCursor();

	// store the 'renderer' in a local variable, just for convenience
	renderer = sdl->renderer();

	// we can take textures from the predefined ones, and we can create a custom one as well
	player = new Player(this, &sdl->images().at("fighter"),10,10, 10, WIDTH, HEIGHT);

	ih = InputHandler::instance();

    
}

void Client::game_thread(){
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
		//player2->update();

		checkCollision();
		
		//UPDATE----------------------------------------------------------
		for (auto bullet =MyBullets.begin(); bullet != MyBullets.end(); bullet++){
        	(*bullet)->update();
			std::pair<int,int> currentPos = (*bullet)->GetPosition();
		
        	if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
				MyDeadBullets.push_back((*bullet));
        }

		//ELIMINAR----------------------------------------------------
    	while (!MyDeadBullets.empty()) {
      	  	MyBullets.remove(MyDeadBullets.back());
       	 	delete MyDeadBullets.back();
       		MyDeadBullets.pop_back();
   		} 


		for (auto bullet =EnemyBullets.begin(); bullet != EnemyBullets.end(); bullet++){
        	(*bullet)->update();
			std::pair<int,int> currentPos = (*bullet)->GetPosition();
		
        	if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
				EnemyDeadBullets.push_back((*bullet));
        }

		//ELIMINAR----------------------------------------------------
    	while (!EnemyDeadBullets.empty()) {
      	  	EnemyBullets.remove(EnemyDeadBullets.back());
       	 	delete EnemyDeadBullets.back();
       		EnemyDeadBullets.pop_back();
   		} 
		//RENDER---------------------------------------------------
		for(Bala* bullet : MyBullets) bullet->render();
		for(Bala* bullet : EnemyBullets) bullet->render();

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

void Client::crearBala(pair<int,int> currentPos, double rot){
    MyBullets.push_back(new Bala(&sdl->images().at("fire"), currentPos.first, currentPos.second, SPEED, WIDTH, HEIGHT, rot));	
}

void Client::crearBalaEnemiga(pair<int,int> pos, double rot){

    EnemyBullets.push_back(new Bala(&sdl->images().at("fire"), pos.first, pos.second, SPEED, WIDTH, HEIGHT, rot));
	
}


void Client::checkCollision(){
	for (auto bullet =EnemyBullets.begin(); bullet != EnemyBullets.end(); bullet++){
        Bala* b = (*bullet);		
			if (Collisions::collidesWithRotation(
			b->getPosition2(), b->getW(), b->getH(), b->getRot(),
			player->getPosition2(), player->getW(), player->getH(), player->getRot())) {
				MyDeadBullets.push_back((*bullet));
				exit_ = true;

				//mensaje de que he perdido -----------------------------
				std::cout<< "ganó jugador B";
			}
			
		}
			
    }
	
}


// void ChatClient::input_thread()
// {
//     while (true)
//     {
//         // Leer stdin con std::getline
//         // Enviar al servidor usando socket
//         std::string msg;
//         std::getline(std::cin, msg);
//         if (msg == "q" || msg == "Q" ) {
//             logout();
//             break;
//         }
//         ChatMessage chatMsg(nick, msg);
//         chatMsg.type = ChatMessage::MessageType::MESSAGE;
//         socket.send(chatMsg, socket);
//     }
// }

// void ChatClient::net_thread()
// {
//     while(true)
//     {
//         //Recibir Mensajes de red
//         //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
//         ChatMessage chatMsg;
//         socket.recv(chatMsg);
//         if(chatMsg.type == ChatMessage::MessageType::LOGOUT)break;
//         std::cout << chatMsg.nick << ": " << chatMsg.message << "\n";
//     }
// }