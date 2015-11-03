/*
 * Client.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(string ip, int port, GameController *gControllerNew) {
	this->userName = "goku";
	this->ip = ip;
	this->port = port;
	this->sockfd = socket(PF_INET, SOCK_STREAM, 0);			//create socket
	this->status = DISCONECTED;								//desconected
	this->gController = gControllerNew;
	this->lastReportedClient = time(0);
	this->lastReportedServer = time(0);
	this->resourceCounter = new ResourceCounter();

}

int Client::connectToServer(){
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
	s_addr.sin_port = htons(port);							//set server's port number
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
	Logger::get()->logInfo("Client","connectToServer","Ya estoy loggeado");

	this->readThread->start((MessageSocketReader*) this->readThread );
	this->writeThread->start((MessageSocketWriter*) this->writeThread);
	Logger::get()->logInfo("Client","connectToServer","Corriendo sockets");
	return OK;
}

void Client::sendMessage(Message *msg){
	this->writeThread->writeMessage(msg);
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

		}else if ( tipoMensaje == "update"){
			//if((*it)->isNewPath()) this->gController->resetPath((*it)->getId());
			this->gController->addTileToCharacter((*it)->getId(),(*it)->getPositionX(),(*it)->getPositionY());

		}else if ( tipoMensaje == "tile" ){
			this->gController->getJuegoVista()->addTile((*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());

		}else if ( tipoMensaje == "edificios" || tipoMensaje == "resources"){
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),
															(*it)->getNombre(),
															(*it)->getPositionX(),
															(*it)->getPositionY());
		}else if ( tipoMensaje == "semiestaticos"){
			this->gController->getJuegoVista()->addSemiEstaticEntity((*it)->getId(),
																	(*it)->getNombre(),
																	(*it)->getPositionX(),
																	(*it)->getPositionY());
		}else if ( tipoMensaje == "personajes"){
			bool imTheOwner= ((*it)->getOwner() == this->userName);
			//TODO uso el FPS para mandar si está conectado o no el cliente, agregar un campo generico para eso
			this->gController->getJuegoVista()->addDinamicEntity((*it)->getId(),
																(*it)->getNombre(),
																(*it)->getPositionX(),
																(*it)->getPositionY(),
																imTheOwner,
																(*it)->getFps());
		}else if ( tipoMensaje == "disconnect"){
			disconnectPlayer((*it)->getId());

		}else if ( tipoMensaje == "reconnect"){
			EntidadDinamicaVista* personaje = this->gController->getJuegoVista()->getEntityById((*it)->getId());
			personaje->setPathImage(GameSettings::GetInstance()->getEntityConfig(personaje->getName())->getPath());

		}else if ( tipoMensaje == "ping"){
			this->lastReportedServer = time(0);								//servidor avisa que sigue arriba

		}else if (tipoMensaje == "fog"){
			this->gController->getJuegoVista()->setVisibleTile((*it)->getPositionX(),(*it)->getPositionY());

		}else if (tipoMensaje == "deleteResource"){
			this->gController->deleteEntity((*it)->getId());
			bool imTheOwner= ((*it)->getOwner() == this->userName);
			if(imTheOwner){
				if((*it)->getNombre() == "gold"){
					this->resourceCounter->recolectarOro();
				}
				if((*it)->getNombre() == "wood"){
					this->resourceCounter->recolectarMadera();
				}
				if((*it)->getNombre() == "chori"){
					this->resourceCounter->recolectarAlimento();
				}
			}

		}else if (tipoMensaje == "newResource"){
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),
															(*it)->getNombre(),
															(*it)->getPositionX(),
															(*it)->getPositionY());
			
		}else{
			//TODO me estan llegando los recursos, son 3 mensajes que no tiene tipo
			cout << "No se que hacer con el tipo: " << tipoMensaje <<endl;
			cout << (*it)->toString()<<endl;
		}
	}
}

void Client::disconnectPlayer(int id){
	//TODO cambiar el path a buscar por algo que no este hardcodeado
	//cambio el path de la imagen por otro grisado y que se note que está desconectado
	this->gController->getJuegoVista()->getEntityById(id)->
			setPathImage(GameSettings::GetInstance()->getEntityConfig("soldadoDesconectado")->getPath());
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

//TODO si el cliente esta desconectado ya no puede enviar mas mensajes
void Client::sendEvents(){
	Message* newMessage = this->gController->getMessageFromEvent(this->userName);
	if(newMessage){
		this->writeThread->writeMessage(newMessage);
		if( newMessage->getTipo() == "exit" ){
			this->status = DISCONECTED;
			this->readThread->shutDown();
			this->writeThread->shutDown();
		}
	}else if( this->status == DISCONECTED){
		Logger::get()->logError("Client","sendEvents","Client disconnect, so can't send message to server");
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
		}
	}
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
		}else{
			initialMessage = "El nombre de usuario ya esta en uso, ingrese otro.";
		}
	}
	this->lastReportedServer = time(0);
}

ResourceCounter* Client::getResourceCounter(){
	return this->resourceCounter;
}

Client::~Client() {
	shutdown(this->sockfd, 2);	//2 blocks recv and sending
	close(this->sockfd);

	this->writeThread->shutDown();
	this->writeThread->join(NULL);

	this->readThread->shutDown();
	this->readThread->join(NULL);

	this->writeThread->~MessageSocketWriter();
	this->readThread->~MessageSocketReader();

	delete writeThread;
	delete readThread;
}
