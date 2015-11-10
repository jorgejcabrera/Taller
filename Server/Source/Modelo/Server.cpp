/*
 * Server.cpp
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Server.h"

Server::Server(int port, GameController *myController) {
	this->port = port;
	this->serverSocket = 0;
	this->gController = myController;
	this->readQueue = new SocketQueue();
	this->lastReportedServer = time(0);
	this->gameSettings = GameSettings::GetInstance();
	this->gameRunning=false;
}

int Server::initSocketServer(){
	this->serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if ( this->serverSocket < 0) {
		Logger::get()->logError("Server","initSocketServer","Error al crear el socket");
		return ERROR;
	}
	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;
	this->serverAddress.sin_addr.s_addr = htons(INADDR_ANY);
	this->serverAddress.sin_port = htons(this->port);

	//Bindeamos el socket
	if ( bind(this->serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0 ) {
		Logger::get()->logError("Server","initSocketServer","Error en la conexion bind..");
		return ERROR;
	}
	// Listen socket Clients
	if (listen(this->serverSocket, 2) < 0) {
		Logger::get()->logError("Server","initSocketServer","Error en el listen");
		return ERROR;
	}

	this->isAlive = true;
	return OK;
}

void Server::shutDown(){
	this->isAlive = false;
}

bool Server::isRunning(){
	return this->isAlive;
}

int Server::run(void * data){
	int cliente;
	socklen_t tamano = sizeof(serverAddress);
	while(this->isAlive){
		if((cliente = accept(this->serverSocket,(struct sockaddr*)&serverAddress,&tamano))>0){
			Client* newClient = new Client(cliente, this->readQueue);
			bool clientAcepted = initConnection(newClient);
			if(clientAcepted){
				//Mando la dimension de la ventana
				newClient->writeMessagesInQueue(new Message("window","window", GameSettings::GetInstance()->getScreenWidth(),GameSettings::GetInstance()->getScreenHeight(),  GameSettings::GetInstance()->getMapWidth(),  GameSettings::GetInstance()->getMapHeight()));

				//Mando la informacion que está en el YAML
				newClient->writeMessagesInQueue(GameSettings::GetInstance()->getListMessageConfiguration());

				//Mando los tiles para dibujarlos en la vista
				newClient->writeMessagesInQueue(this->gController->getTilesMessages());

				//Mando las entidades que tiene el mapa
				newClient->writeMessagesInQueue(gController->getEntitiesMessages());

				//Mando los protagonistas hasta el momento
				newClient->writeMessagesInQueue(getProtagonistasMessages());

				newClient->writeMessagesInQueue(newClient->getSeenTilesAsMessages());

				newClient->writeMessagesInQueue(newClient->getInitialOffsetAsMessage());

				//le mando a todos los clientes el color del cliente
				this->sendColour(newClient);

				newClient->connect();
			}
		}
	}
	return 0;
}

bool Server::acceptingNewClients(){
	//TODO setear el limite en algun lado, no tiene que estar hardcodeado
	return (this->clients.size()<2);
}

void Server::notifyGameInitToClients(){
	Message* messageStart = new Message();
	messageStart->startGame();
	list<Client*> activeClients= getActiveClients();
	for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
		(*clientIterator)->writeMessagesInQueue(messageStart);
	}
}

list<Message*> Server::getProtagonistasMessages(){
	list<Message*> listaDeProtagonistas;
	map<int,EntidadDinamica*>* protagonistas = this->gController->getJuego()->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it=protagonistas->begin(); it!=protagonistas->end();++it){
		string tipoEntidad = DefaultSettings::getTypeEntity((*it).second->getName());
		//0 : conectado, -1 Desconectado
		int clientConnected = this->clients.at((*it).second->getOwner())->getStatus();
		Message* protagonistaMessage = new Message((*it).second->getId(), 
													tipoEntidad, 
													(*it).second->getName(), 
													(*it).second->getPosition().first,
													(*it).second->getPosition().second,
													clientConnected);
		protagonistaMessage->setOwner((*it).second->getOwner());
		listaDeProtagonistas.push_back(protagonistaMessage);
	}
	return listaDeProtagonistas;
}

void Server::processReceivedMessages(){
	this->readQueue->lockQueue();
	//TODO revisar, hoy no usamos la lista idEntitiesUpdated porque notificamos lo que se este "moviendo"
	this->idEntitiesUpdated.clear();
	stringstream ss;
	while(!this->readQueue->isEmpty()){
		Message* messageUpdate = this->readQueue->pullTailWithoutLock();
		if( messageUpdate->getTipo() == "ping" ){
			this->clients.at(messageUpdate->getNombre())->reporting();
		}else if( messageUpdate->getTipo() == "exit" ){
			//TODO destruir el cliente que se esta desconectando
			ss.str("");
			ss << "Client " << messageUpdate->getNombre() << " was disconected";
			Logger::get()->logInfo("Server","processReceivedMessages", ss.str());
			this->clients.at(messageUpdate->getNombre())->disconect();
		
		}else if( this->gameRunning && messageUpdate->getTipo() == "attack" ){
			int idUpdate = messageUpdate->getId();
			int target = messageUpdate->getTarget();
			pair<int,int> targetPosition= this->gController->getJuego()->getDinamicEntityById(target)->getPosition();
			this->gController->getJuego()->setPlaceToGo(idUpdate, targetPosition.first, targetPosition.second);
			this->gController->getJuego()->setTargetTo(idUpdate,target);
			this->idEntitiesUpdated.push_back(idUpdate);
		
		}else if( this->gameRunning ){
			int idUpdate = messageUpdate->getId();
			this->gController->getJuego()->setPlaceToGo(idUpdate, messageUpdate->getPositionX(), messageUpdate->getPositionY());
			this->gController->getJuego()->setTargetTo(idUpdate,0);
			this->idEntitiesUpdated.push_back(idUpdate);
		}
	}
	this->readQueue->unlockQueue();
}

void Server::notifyClients(){
	map<int,EntidadDinamica*>* protagonistas = this->gController->getJuego()->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it=protagonistas->begin(); it!=protagonistas->end();++it){
		if (it->second->hasToNotify()){
			Message* messageUpdate = new Message(it->second->getId(), it->second->getPosition().first, it->second->getPosition().second);
			//messageUpdate->setAsNewPath(it->second->pathIsNew());
			list<Client*> activeClients= getActiveClients();
			for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
				(*clientIterator)->writeMessagesInQueue(messageUpdate);
			}
		}
	}
	//mando los nuevos personajes
	list<EntidadDinamica*> *nuevosProtagonistas = this->gController->getJuego()->getNewProtagonistasToNotify();
	for(list<EntidadDinamica*>::iterator it=nuevosProtagonistas->begin(); it!=nuevosProtagonistas->end();++it){
		//int clientConnected = this->clients.at((*it)->getOwner())->getStatus();
		Message* protagonistaMessage = new Message((*it)->getId(), 
													DefaultSettings::getTypeEntity((*it)->getName()),
													(*it)->getName(), 
													(*it)->getPosition().first,
													(*it)->getPosition().second,0);
		protagonistaMessage->setOwner((*it)->getOwner());
		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			if((*clientIterator)->getUserName()!=(*it)->getOwner()){
				//no notifico al dueño del personaje porque ya lo recibio
				(*clientIterator)->writeMessagesInQueue(protagonistaMessage);
			}
		}
	}
	//mando que se consumio un recurso
	ResourceManager* rm = this->gController->getJuego()->getResourceManager();
	if(rm->hasToNotify()){
		//a los ultimos 3 parametros del mensaje no les doy bola
		Message* resourceMessege = new Message(rm->getIdAEliminar(),"deleteResource",rm->getUltimoTipoConsumido(),0,0,0);
		rm->yaNotifique();
		resourceMessege->setOwner(rm->getUltimoEnConsumir());

		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			(*clientIterator)->writeMessagesInQueue(resourceMessege);
		}
	}

	//mando los nuevos recursos que se crean
	if(rm->hasNewResource()){
		pair<int,int> pos = rm->getPosNuevoRecurso();
		Message* newResourceMessege = new Message(rm->getIdNuevoRecurso(),"newResource",rm->getUltimoTipoCreado(),pos.first,pos.second,0);
		rm->newResourceSent();

		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			(*clientIterator)->writeMessagesInQueue(newResourceMessege);
		}

	}

	this->gController->getJuego()->cleanNewProtagonistas();
	pingMessage();
}

void Server::pingMessage(){
	//Si hace mas de X segundos notifico que estoy conectado
	if((time(0)-this->lastReportedServer)>=(DefaultSettings::getTimeOut()-5)){
		Message* ping = new Message();
		ping->pingMessage("server");
		list<Client*> activeClients= getActiveClients();
		for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
			(*clientIterator)->writeMessagesInQueue(ping);
		}
		this->lastReportedServer = time(0);
	}
}

void Server::verifyClientsConections(){

	list<Client*> activeClients= getActiveClients();
	for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
		if((*clientIterator)->getTimeSinceLastReport()>= (DefaultSettings::getTimeOut()*2)){
			(*clientIterator)->disconect();
			stringstream ss;
			ss<< "CLIENTE se deconecto: "<< (*clientIterator)->getUserName();
			Logger::get()->logInfo("Server","verifyClientsConections",ss.str());

			list<int> entitiesToDisconect = gController->getEntitiesOfClient((*clientIterator)->getUserName());
			for(list<int>::iterator it=entitiesToDisconect.begin(); it!=entitiesToDisconect.end();++it){
				Message* messageDisconnect = new Message();
				messageDisconnect->clientDisconect(*it);
				for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
						(*clientIt)->writeMessagesInQueue(messageDisconnect);
				}
			}
		}
		if(this->gController->checkIfClientLostGame((*clientIterator)->getUserName())){
			Message* messageClientLost = new Message();
			messageClientLost->clientLost((*clientIterator)->getUserName());
			for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
					(*clientIt)->writeMessagesInQueue(messageClientLost);
			}
			(*clientIterator)->disconect();
		}
	}

	if(!this->acceptingNewClients()){
		//Si solo queda un cliente, entonces gano
		activeClients= getActiveClients();
		if(activeClients.size()==1){

			Client* winner = activeClients.front();
			Message* messageClientWin = new Message();
			messageClientWin->clientWin(winner->getUserName());
			winner->writeMessagesInQueue(messageClientWin);
			this->gController->gameFinished();
			//TODO revisar si esto es necesario, quiero que al ultimo cliente le llegue el mensaje de que gano y que no sea que pierde la conexion
			this->gController->delay(1000);
		}else if(activeClients.size()==0){
			this->gController->gameFinished();
		}
	}
}


list<Client*> Server::getActiveClients(){
	list<Client*> activeClients;
	for(map<string,Client*>::iterator clientIterator=this->clients.begin(); clientIterator!=this->clients.end(); ++clientIterator){
		if(clientIterator->second->getStatus()==0){
			activeClients.push_back(clientIterator->second);
		}
	}
	return activeClients;
}

bool Server::initConnection(Client* newClient){
	bool validUserName=false;
	stringstream ss;
	while(!validUserName){
		string userName = newClient->readUserName();
		if(this->acceptingNewClients()){
			map<string,Client*>::iterator it = this->clients.find(userName);
			if( it != this->clients.end() ){
				//El cliente ya existia
				ss << "player " << userName << " already exists...";
				Logger::get()->logInfo("Server","readClientUserName",ss.str());
				newClient->responseUserName("FAIL");
			}else{
				//El cliente no exitia
				newClient->responseUserName("OK");
				newClient->setUserName(userName);
				validUserName=true;
				ss.str("");
				ss << "player "<< userName << " has joined the game";
				Logger::get()->logInfo("Server","readClientUserName",ss.str());
				this->createEntitiesForClient(newClient);
				newClient->startCommunication();
				return true;
			}
		}else{
			//Ya se conectaron todos los clientes
			validUserName=true;
			Logger::get()->logInfo("Server","readClientUserName","Limit of clients");
			newClient->responseUserName("NOTALLOW");
			newClient->~Client();
			return false;
		}
	}
}

void Server::createEntitiesForClient(Client* newClient){
	//Cada vez que se conecta un cliente agrego un protagonista que tiene un owner
	pair<int,int> offsetClient = this->gController->getJuego()->createEntitiesForClient(newClient->getUserName(), this->clients.size());
	newClient->setInitialOffset(offsetClient.first, offsetClient.second);
	this->clients.insert(make_pair(newClient->getUserName(),newClient));
}

//TODO : (FOG)EL SERVER LE MANDA AL CLIENTE LA NUEVA POSICION DE LA ENTIDAD, EL CLIENTE CALCULA LOS NUEVOS TILES, Y SE LOS DEVUELVE AL SERVER
void Server::setSeenTiles() {
	map<string,list<pair<int,int> > > newTilesByClient;
	map<int,EntidadDinamica*>* protagonistas =this->gController->getJuego()->getDinamicEntities();

	for(map<int,EntidadDinamica*>::iterator it=protagonistas->begin(); it!=protagonistas->end();++it){
		EntidadDinamica * entidad = (*it).second;
		pair<int,int> position = entidad->getPosition();
		int rangeEntity = entidad->getVisibilityRange();
		string owner = (*it).second->getOwner();
		for (int x = position.first - rangeEntity; x <= position.first + rangeEntity; x++) {
			if ( (x>=0) && (x < gameSettings->getMapWidth())) {
				for (int y = position.second-rangeEntity ; y <= position.second+rangeEntity ; y++) {
					if ((y>=0) && (y < this->gameSettings->getMapHeight())) {
						if((x+y >= position.first + position.second - rangeEntity) && (x+y <= position.first + position.second + rangeEntity)
						&& (x-y >= position.first - position.second - rangeEntity) && (x-y <= position.first - position.second + rangeEntity)) {
							newTilesByClient[owner].push_back(std::make_pair(x,y));
						}
					}
				}
			}
		}
	}

	for( map<string,list<pair<int,int> > >::iterator it = newTilesByClient.begin() ; it!=newTilesByClient.end() ; ++it) {
		Client* client = this->clients[(*it).first];
		if (client->getStatus() == CONECTED) {
			list<pair<int,int> > newTiles = client->setSeenTiles((*it).second);
			for (list<pair<int,int> >::iterator itNewList = newTiles.begin(); itNewList != newTiles.end(); ++itNewList) {
				Message* msg = new Message();
				msg->activeTile((*itNewList).first,(*itNewList).second);
				client->writeMessagesInQueue(msg);
			}
		}
	}
}

void Server::sendSeenTiles(string client) {
	list<pair<int,int> > seenTiles = this->clients[client]->getSeenTiles();
	for(list<pair<int,int> >::iterator it=seenTiles.begin(); it!=seenTiles.end();++it){
		Message* msg = new Message();
		msg->activeTile((*it).first,(*it).second);
		this->clients[client]->writeMessagesInQueue(msg);
	}
}

void Server::verifyWaitingClients(){
	if(this->acceptingNewClients()){
		//Espero 1 segundo hasta volver a chequear si ya estan todos conectados
		this->gController->delay(1000);
	}else if(!this->gameRunning){
		this->notifyGameInitToClients();
		this->gameRunning=true;
	}
}

void Server::sendColour(Client* client) {
	//envio el nuevo color a todos los clientes
	Message* msg = new Message();
	msg->colourOfClient(client->getUserName(), this->clients.size());
	for (map<string,Client*>::iterator it = clients.begin() ; it != clients.end() ; it++ ) {
		(*it).second->writeMessagesInQueue(msg);
	}

}

Server::~Server() {
	for(map<string,Client*>::iterator it=this->clients.begin(); it!=this->clients.end(); ++it){
		it->second->~Client();
	}
	//this->gameSettings = NULL;
	//this->gController = NULL;
	readQueue->~SocketQueue();
	//delete(this->readQueue);
	close(this->serverSocket);
}
