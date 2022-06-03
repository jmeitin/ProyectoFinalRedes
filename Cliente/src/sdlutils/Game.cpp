#include "Game.h"
#include "../utils/Collisions.h"

Client::Client(const char* ip, const char* port, const char * n): socket(ip,port){
	
	nick = n;


}

Client::~Client(){
	if(player != nullptr)delete player;
	if(player2 != nullptr)delete player2;
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


void Client::login()
{
	
    LogMessage em(nick);
    em.type = Message::MessageType::LOGIN;
	
    socket.send(em, socket);
}

void Client::logout()
{
    LogMessage em(nick);
    em.type = Message::MessageType::LOGOUT;

    socket.send(em, socket);

	exit_ = true;
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
		
			PlayerMsg playerm1; playerm1.from_bin(buffer);

			MyPlayerID = playerm1.player;
			 std::cout <<  MyPlayerID <<" \n"; 

			startGame();
			
			playing = true;			
			continue;
		}
		if(playing){
			if (message.type == Message::MessageType::PLAYERPOS){
				Object playerm2; playerm2.from_bin(buffer);
				//std::cout << playerm2.posx <<" " << playerm2.posy << " " << playerm2.rot << "\n";
				//playerm2.type = Message::MessageType::PLAYERPOS;
				player2->move(playerm2.posx, playerm2.posy, playerm2.rot);
			}
			else if (message.type == Message::MessageType::SHOT){
				PlayerMsg bullet; bullet.from_bin(buffer);
				pair <int,int> aux{player2->GetPosition().first, player2->GetPosition().second};
				crearBalaEnemiga(aux, player2->getRot());
			}
			else if (message.type == Message::MessageType::PlAYERKILLED){				
				logout();
				
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
	// std::cout << (sdl == nullptr) << std::endl;
    // //show the cursor
	 sdl->showCursor();

	// // store the 'renderer' in a local variable, just for convenience
	 renderer = sdl->renderer();

	// we can take textures from the predefined ones, and we can create a custom one as well
	player = new Player(this, &sdl->images().at("fighter"),posiciones[MyPlayerID].first,posiciones[MyPlayerID].second, SPEED, WIDTH, HEIGHT);
	 int otherID = (MyPlayerID + 1) % 2	;
	player2 = new Player(this, &sdl->images().at("fighter"),posiciones[otherID].first,posiciones[otherID].second, SPEED, WIDTH, HEIGHT);
	  ih = InputHandler::instance();

    
}

void Client::game_thread(){
    while (!exit_) {
		
			if(ih != nullptr){
				ih->refresh();
				if (ih->keyDownEvent() )
				{
				if(ih->isKeyDown(SDLK_q)){
					logout();
					exit_ = true;
					}
				}
			}
		if(playing){
		
		//Uint32 startTime = sdl->currRealTime();
		
		// // update the event handler
		
			// clear screen
		sdl->clearRenderer();


		//player->update();
		if(player->update()){
			Object posMsg = Object(MyPlayerID, player->GetPosition().first, player->GetPosition().second, player->getRot());
			//std::cout << player->GetPosition().first <<" " << player->GetPosition().second << " " << player->getRot() << "\n";
			posMsg.type = Message::MessageType::PLAYERPOS;
			socket.send(posMsg, socket);

		}

	checkCollision();
		
	 updateAllBullets();
	 
	
	// 	//RENDER---------------------------------------------------
	 	for(Bala* bullet : MyBullets) bullet->render();
	 	for(Bala* bullet : EnemyBullets) bullet->render();
	freeDeadBullets();
	 	player->render();
	 	player2->render();
		
		
	// 	// present new frame
	 	sdl->presentRenderer();

		 }
	 }
	// stop the music
	//Music::haltMusic();
}

void Client::freeDeadBullets(){
	while (!MyDeadBullets.empty()) {
		MyBullets.remove(MyDeadBullets.back());
		delete MyDeadBullets.back();
		MyDeadBullets.pop_back();
	} 

	while (!EnemyDeadBullets.empty()) {
		EnemyBullets.remove(EnemyDeadBullets.back());
		delete EnemyDeadBullets.back();
		EnemyDeadBullets.pop_back();
	}

}

void Client::updateAllBullets(){

	for (auto bullet =MyBullets.begin(); bullet != MyBullets.end(); bullet++){
		(*bullet)->update();
		std::pair<int,int> currentPos = (*bullet)->GetPosition();

		if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
			MyDeadBullets.push_back((*bullet));
	}

	for (auto bullet =EnemyBullets.begin(); bullet != EnemyBullets.end(); bullet++){
		(*bullet)->update();
		std::pair<int,int> currentPos = (*bullet)->GetPosition();

		if (currentPos.first >= WIDTH || currentPos.first <= 0||currentPos.second  >= HEIGHT||currentPos.second <= 0)  //SI SE MUERE
			EnemyDeadBullets.push_back((*bullet));
	}
	
}

void Client::crearBala(pair<int,int> currentPos, float rot){
    MyBullets.push_back(new Bala(&sdl->images().at("fire"), currentPos.first, currentPos.second, SPEED, WIDTH, HEIGHT, rot));	
	PlayerMsg shot = PlayerMsg(MyPlayerID);
	shot.type = Message::MessageType::SHOT;
	socket.send(shot, socket);
}


void Client::crearBalaEnemiga(pair<int,int> pos, float rot){

    EnemyBullets.push_back(new Bala(&sdl->images().at("fire"), pos.first, pos.second, SPEED, WIDTH, HEIGHT, rot));
	
}


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
				
				//mensaje de que he perdido -----------------------------
				std::cout<< "ganó jugador B";
			}
			
		}
			
    }
	
float Client::getSDLcurrTime(){
	return sdl->currRealTime();
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