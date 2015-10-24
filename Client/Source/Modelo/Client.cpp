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
		this->status = CONECTED;
	}

	//INITIALIZE THREAD
	this->readThread = new MessageSocketReader(this->sockfd);
	this->writeThread = new MessageSocketWriter(this->sockfd);
	notifyUserName();

	this->readThread->start((MessageSocketReader*) this->readThread );
	this->writeThread->start((MessageSocketWriter*) this->writeThread);
	return OK;
}

void Client::sendMessage(Message *msg){
	if (this->status == CONECTED){
		this->writeThread->writeMessage(msg);
	}
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
			cout << (*it)->toString()<<endl;
			this->gController->updatePostion((*it)->getId(),(*it)->getPositionX(),(*it)->getPositionY());
		}else if ( tipoMensaje == "tile" ){
			//Agrego al JuegoVista un nuevo tile
			this->gController->getJuegoVista()->addTile((*it)->getNombre(),(*it)->getPositionX(), (*it)->getPositionY());
		}else if ( tipoMensaje == "edificios" || tipoMensaje=="resources"){
			//Agrego al JuegoVista un nuevo edificio/estatico
			this->gController->getJuegoVista()->addBuilding((*it)->getId(),
															(*it)->getNombre(),
															(*it)->getPositionX(),
															(*it)->getPositionY());
		}else if ( tipoMensaje == "semiestaticos"){
			//Agrego al JuegoVista un nuevo semiestatico/molino
			this->gController->getJuegoVista()->addSemiEstaticEntity((*it)->getId(),
																	(*it)->getNombre(),
																	(*it)->getPositionX(),
																	(*it)->getPositionY());
		}else if ( tipoMensaje == "personajes"){
			cout << (*it)->toString()<<endl;
			//Agrego al JuegoVista personajes/dinamicos
			bool imTheOwner= ((*it)->getOwner()==this->userName);
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

void Client::sendEvents(){
	Message* newMessage = this->gController->getMessageFromEvent(this->name);
	if(newMessage){
		if(newMessage->getTipo()=="exit"){
			this->status = DISCONECTED;
		}
		this->writeThread->writeMessage(newMessage);
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
		if( (time(0)-this->lastReportedServer) > (DefaultSettings::getTimeOut()+5)){
			this->status = DISCONECTED;
			//TODO mostrar un mejor mensaje cuando pierdo conectividad
			Logger::get()->logDebug("Client","verifyServerAlive","SERVIDOR DESCONECTADO");
		}
	}
}

Client::~Client() {
	shutdown(this->sockfd, 2);	//2 blocks recv and sending
	close(this->sockfd);
}

//TODO aca mando el nombre de usuario, cambiarlo para que acepte ingresar por teclado
void Client::notifyUserName(){
	cout << "Ingrese un nombre de usuario";
	bool valid = false;
	while(!valid){
		getline (std::cin,this->userName);
		this->writeThread->writeMessageNow(new Message(this->userName));
		Message *response = this->readThread->readMessageNow();
		if(response->getNombre()=="OK"){
			valid=true;
		}else{
			cout<<"El nombre de usuario" << this->userName <<" ya está en uso, por favor ingrese otro"<<endl;
		}
	}

}

