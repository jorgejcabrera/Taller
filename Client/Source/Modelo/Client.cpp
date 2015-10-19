/*
 * Client.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Client.h"

Client::Client(string ip, int port, GameController *gControllerNew) {
	this->ip = ip;
	this->port = port;
	this->sockfd = socket(PF_INET, SOCK_STREAM, 0);			//create socket
	this->status = DISCONECTED;								//desconected
	this->gController = gControllerNew;
}

//TODO habilitar el socket que escribe al servidor
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
		return ERROR;
	}
	if ( (error = connect(this->sockfd,(struct sockaddr *)&s_addr, sizeof(s_addr))) < 0){
		ss.str("");
		ss << "Error connecting to server ." << gai_strerror(error);
		Logger::get()->logError("Client","connectToServer",ss.str());
		this->status = DISCONECTED;
		return ERROR;
	}else{
		cout << "Conexion con el servidor "<< inet_ntoa(s_addr.sin_addr)<<endl;
		this->status = CONECTED; // conectado :)
	}

	//INITIALIZE THREAD
	this->readThread = new MessageSocketReader(this->sockfd);
	this->readThread->start((MessageSocketReader*) this->readThread );

	this->writeThread = new MessageSocketWriter(this->sockfd);
	this->writeThread->start((MessageSocketWriter*) this->writeThread);

	return OK;
}

void Client::sendMessage(Message *msg){
	if (this->status == CONECTED){
		this->writeThread->writeMessage(msg);
	}
}

void Client::readMessage(Message msg){

}

int Client::getStatus(){
	return this->status;
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
			//instancio el picassoHelper con el tamaño de la ventana;
			this->gController->getJuegoVista()->createView();

		}else if ( tipoMensaje == "config" ){
			saveEntitiesConfig(*it);
		}else if ( tipoMensaje == "update"){
			//TODO agregar comportamiento para mensajes de cambios de posicion
		}else if ( tipoMensaje == "tile" ){
			//Agrego al JuegoVista un nuevo tile
			this->gController->getJuegoVista()->addTile((*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());
		}else if ( tipoMensaje == "edificios"){
			//Agrego al JuegoVista un nuevo edificio/estatico
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),(*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());
		}else if ( tipoMensaje == "semiestaticos"){
			//Agrego al JuegoVista un nuevo semiestatico/molino
			this->gController->getJuegoVista()->addSemiEstatico((*it)->getId(),(*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());
		}else if ( tipoMensaje == "personajes"){
			//Agrego al JuegoVista personajes/dinamicos
			this->gController->getJuegoVista()->addPersonaje((*it)->getId(),(*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());
		}else{
			cout << "No se que hacer con el tipo: " << tipoMensaje <<endl;
		}
	}
}

void Client::saveEntitiesConfig(Message* msg){
	EntidadConfig* entidad = new EntidadConfig(msg->getNombre(),
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
}


Client::~Client() {
	shutdown(this->sockfd, 2);	//2 blocks recv and sending
	close(this->sockfd);
}

