/*
 * Client.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(GameController *gControllerNew) {
	this->userName = "goku";
	this->status = DISCONECTED;								//desconected
	this->gController = gControllerNew;
	this->lastReportedClient = time(0);
	this->lastReportedServer = time(0);
	this->resourceCounter = new ResourceCounter();
	this->gController->getJuegoVista()->setResourceCounter(this->resourceCounter);
	this->sockfd = socket(PF_INET, SOCK_STREAM, 0);			//create socket
}

int Client::connectToServer(string ip){
	this->askPortConnection();

	this->ip = ip;
	int error;
	stringstream ss;
	if ( this->sockfd < 0) {
		ss << "Error initializing socket ." << gai_strerror(this->sockfd);
		Logger::get()->logError("Client","connectToServer",ss.str());
		return ERROR;
	}

	//CREATE SOCKET
	struct sockaddr_in s_addr;
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_family = AF_INET;							//address family internet
	s_addr.sin_port = htons(this->port);							//set server's port number
	s_addr.sin_addr.s_addr = inet_addr(this->ip.c_str());	//set server's IP

	if ( s_addr.sin_addr.s_addr < 0 ){
		ss.str("");
		ss << "IP connection error ." << gai_strerror(s_addr.sin_addr.s_addr);
		Logger::get()->logError("Client","connectToServer",ss.str());
		this->status = DISCONECTED;
		return ERROR;
	}
	if ( (error = connect(this->sockfd,(struct sockaddr *)&s_addr, sizeof(s_addr))) < 0){
		ss.str("");
		ss << "Error connecting to server ." << gai_strerror(error);
		Logger::get()->logError("Client","connectToServer",ss.str());
		this->status = DISCONECTED;
		return ERROR;
	}else{
		stringstream ss;
		ss << "Connection to server" << inet_ntoa(s_addr.sin_addr);
		Logger::get()->logInfo("Client","connectToServer",ss.str());
		this->status = CONECTED;
	}

	//INITIALIZE THREAD
	this->readThread = new MessageSocketReader(this->sockfd);
	this->writeThread = new MessageSocketWriter(this->sockfd);
	notifyUserName();

	if(this->isConected()){
		this->readThread->start((MessageSocketReader*) this->readThread );
		this->writeThread->start((MessageSocketWriter*) this->writeThread);
	}
	return OK;
}

bool Client::isConected(){
	return this->status == CONECTED;
}

void Client::processReceivedMessages(){
	list<Message*> pendingMessages = this->readThread->getMessagesToProcess();
	for(list<Message*>::iterator it = pendingMessages.begin(); it != pendingMessages.end(); ++it){
		string tipoMensaje = (*it)->getTipo();
		if( tipoMensaje == "window" ){
			GameSettings::GetInstance()->setScreenDimension((*it)->getPositionX(),(*it)->getPositionY());
			GameSettings::GetInstance()->setMapDimention((*it)->getAnchoBase(), (*it)->getAltoBase());
			this->gController->getJuegoVista()->createView();

		}else if ( tipoMensaje == "config" ){
			saveEntitiesConfig(*it);

		}else if ( tipoMensaje == "update" ){
			//TODO ojo cuando actualizemos la salud de un endificio esto no va a andar por las calses estaticas no tienen el metodo addTileTopath
			this->gController->getJuegoVista()->getDinamicEntityById((*it)->getId())->addTileToPath((*it)->getPositionX(),(*it)->getPositionY());
			EntidadPartidaVista* entity = this->gController->getJuegoVista()->getDinamicEntityById((*it)->getId());
			entity->setHealth((*it)->getHealth());
			entity->setStrength((*it)->getStrength());
			entity->setPrecision((*it)->getPrecision());

		}else if ( tipoMensaje == "tile" ){
			this->gController->getJuegoVista()->addTile((*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());

		}else if ( tipoMensaje == "edificios" || tipoMensaje == "resources"){
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),
															(*it)->getNombre(),
															(*it)->getPositionX(),
															(*it)->getPositionY(),
															(*it)->getOwner(),
															(*it)->getHealth());
		}else if ( tipoMensaje == "semiestaticos"){
			this->gController->getJuegoVista()->addSemiEstaticEntity((*it)->getId(),
																	(*it)->getNombre(),
																	(*it)->getPositionX(),
																	(*it)->getPositionY(),
																	(*it)->getOwner(),
																	(*it)->getHealth());
		}else if ( tipoMensaje == "personajes"){
			//TODO uso el FPS para mandar si está conectado o no el cliente, agregar un campo generico para eso
			stringstream ss;
			ss<< "newProtagonista... name " <<(*it)->getNombre()<< " posx: "<< (*it)->getPositionX() << "posy: "<< (*it)->getPositionY() << "posx: "<< (*it)->getPositionX() << " client = " << this->userName;
			Logger::get()->logInfo("Client","processReceivedmessages",ss.str());
			this->gController->getJuegoVista()->addDinamicEntity((*it)->getId(),
																(*it)->getNombre(),
																(*it)->getPositionX(),
																(*it)->getPositionY(),
																(*it)->getFps(),
																(*it)->getOwner(),
																(*it)->getHealth(),
																(*it)->getStrength(),
																(*it)->getPrecision());
		}else if ( tipoMensaje == "disconnect"){
			disconnectPlayer((*it)->getNombre());
		}else if ( tipoMensaje == "reconnect"){
			EntidadPartidaVista* personaje = this->gController->getJuegoVista()->getDinamicEntityById((*it)->getId());
			personaje->setPathImage(GameSettings::GetInstance()->getEntityConfig(personaje->getName())->getPath());

		}else if ( tipoMensaje == "ping"){
			this->lastReportedServer = time(0);	//servidor avisa que sigue arriba

		}else if (tipoMensaje == "fog"){
			this->gController->getJuegoVista()->setVisibleTile((*it)->getPositionX(),(*it)->getPositionY());

		}else if (tipoMensaje == "deleteResource"){
			this->gController->getJuegoVista()->addResourceToConsume((*it)->getId());
			bool imTheOwner= ((*it)->getOwner() == this->userName);
			if(imTheOwner){
				this->resourceCounter->recolectar((*it)->getNombre());
			}

		}else if (tipoMensaje == "deleteEntity"){
			this->gController->getJuegoVista()->deleteEntityById((*it)->getId());
		
		}else if (tipoMensaje == "newResource"){
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),
															(*it)->getNombre(),
															(*it)->getPositionX(),
															(*it)->getPositionY(),
															"",
															(*it)->getHealth());
		}else if (tipoMensaje == "start"){
			this->gController->setGameRunning();
		}else if (tipoMensaje == "offset"){
			this->gController->getJuegoVista()->updateOffset((*it)->getPositionX(),(*it)->getPositionY());
		}else if (tipoMensaje == "colour"){
			this->gController->getJuegoVista()->setColour((*it)->getOwner(),(*it)->getPositionX());
		}else if (tipoMensaje == "win"){
			this->gController->winGame();
			this->status = DISCONECTED;
		}else if (tipoMensaje == "lost"){
			if((*it)->getNombre() == this->userName){
				this->gController->loseGame();
				this->status = DISCONECTED;
			}else{
				//Si el que perdio es otro, borro sus entidades
				//TODO revisar que pasa si el juego es captura de bandera
				disconnectPlayer((*it)->getNombre());
			}
		}else{
			cout << "No se que hacer con el tipo: " << tipoMensaje <<endl;
			cout << (*it)->toString()<<endl;
		}
	}
}

//TODO borrar este metodo
void Client::disconnectPlayer(string userName){
	this->gController->getJuegoVista()->deleteEntitiesOfClient(userName);
}

void Client::saveEntitiesConfig(Message* msg){
	EntidadConfig* entidad = new EntidadConfig(	msg->getNombre(),
												msg->getImagen(),
												msg->getAnchoBase(),
												msg->getAltoBase(),
												msg->getFps(),
												msg->getDelay(),
												msg->getTotalFramesLine(),
												msg->getPixelsDimension());
	GameSettings::GetInstance()->addEntityConfig(entidad);
}

void Client::sendEvents(){
	list<Message*> messages = this->gController->getMessagesFromEvent(this->userName);
	if(messages.empty()){
		if( this->status == DISCONECTED){
				Logger::get()->logError("Client","sendEvents","Client disconnect, so can't send message to server");
		}

	} else {
		for(list<Message*>::iterator it = messages.begin() ; it != messages.end() ; ++it) {
			this->writeThread->writeMessage((*it));
			if( (*it)->getTipo() == "exit" ){
				this->status = DISCONECTED;
				this->readThread->shutDown();
				this->writeThread->shutDown();
			}
		}
	}
	pingMessage();
}

void Client::pingMessage(){
	//Si hace mas de X segundos notifico que estoy conectado
	if((time(0)-this->lastReportedClient)>=DefaultSettings::getTimeOut()){
			Message* ping = new Message();
			ping->pingMessage(this->userName);
			this->writeThread->writeMessage(ping);
			this->lastReportedClient = time(0);
		}
}

void Client::verifyServerAlive(){
	if(isConected()){
		if( (time(0)-this->lastReportedServer) > (DefaultSettings::getTimeOut()*2)){
			this->status = DISCONECTED;
			Logger::get()->logError("Client","verifyServerAlive","Problemas con el servidor. Conexion cerrada.");
			gController->disconnectedGame();
		}
	}
}

void Client::askPortConnection(){
	this->gController->getJuegoVista()->createView();
	bool valid = false;
	string initialMessage = "Ingrese el puerto de conexion";
	string portStr = this->gController->getJuegoVista()->renderUserInputView(initialMessage);
	this->port = atoi(portStr.c_str());
}


void Client::notifyUserName(){
	this->gController->getJuegoVista()->createView();
	bool valid = false;
	string initialMessage = "Ingrese el nombre de usuario";
	while(!valid){
		this->userName = this->gController->getJuegoVista()->renderUserInputView(initialMessage);
		this->writeThread->writeMessageNow(new Message(this->userName));
		Message* response = this->readThread->readMessageNow();
		if(response->getNombre()=="OK"){
			valid=true;
			this->lastReportedServer = time(0);
			initialMessage = "Esperando cantidad minima de jugadores";
			this->gController->setClientName(this->userName);
			this->gController->getJuegoVista()->renderFinishLogin(initialMessage);
		}else if(response->getNombre()=="NOTALLOW"){
			this->status = DISCONECTED;
			valid=true;
			initialMessage = "La partida ya inicio, no se puede conectar ahora";
			this->gController->getJuegoVista()->renderFinishLogin(initialMessage);
		}else{
			initialMessage = "El nombre de usuario ya esta en uso, ingrese otro.";
		}
	}
}

ResourceCounter* Client::getResourceCounter(){
	return this->resourceCounter;
}

string Client::getUserName(){
	return this->userName;
}

Client::~Client() {
	shutdown(this->sockfd, 2);	//2 blocks recv and sending
	close(this->sockfd);

	this->writeThread->shutDown();
	this->writeThread->join(NULL);

	this->readThread->shutDown();
	this->readThread->join(NULL);

//	this->writeThread->~MessageSocketWriter();
//	this->readThread->~MessageSocketReader();

	delete writeThread;
	delete readThread;
}
