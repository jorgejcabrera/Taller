/*
 * Server.cpp
 *
 *  Created on: 4 de oct. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Server.h"

Server::Server(int port, GameController* myController) {
	this->port = port;
	this->serverSocket = 0;
	this->gController = myController;
	this->readQueue = new SocketQueue();
	this->lastReportedServer = time(0);
	this->gameSettings = GameSettings::GetInstance();
	this->gameRunning=false;
	this->isAlive = true;
}

bool Server::acceptingNewClients(){
	//TODO setear el limite en algun lado, no tiene que estar hardcodeado
	return (this->clients.size()<2);
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
				newClient->writeMessagesInQueue(GameSettings::GetInstance()->getWindowMessage());

				//Mando la informacion que está en el YAML
				newClient->writeMessagesInQueue(GameSettings::GetInstance()->getConfMessages());

				//Mando los tiles para dibujarlos en la vista
				newClient->writeMessagesInQueue(this->gController->getTilesMessages());

				//Le mando a todos los clientes el color del cliente. Lo hago antes de mandar las entidades para saber el color de la bandera
				this->sendColours(newClient);

				//Mando las entidades que tiene el mapa
				newClient->writeMessagesInQueue(gController->getEntitiesMessages());

				//Mando los protagonistas hasta el momento
				newClient->writeMessagesInQueue(getProtagonistasMessages());

				//Mando los recursos del mapa
				newClient->writeMessagesInQueue(this->gController->getJuego()->getMap()->getResourcesMessages());

				//Mano offset inicial
				newClient->writeMessagesInQueue(newClient->getInitialOffsetAsMessage());

				newClient->connect();
			}
		}
	}
	return 0;
}

void Server::notifyGameInitToClients(){
	Message* messageStart = new Message();
	messageStart->startGame();
	list<Client*> activeClients = getActiveClients();
	for(list<Client*>::iterator clientIterator = activeClients.begin(); clientIterator != activeClients.end(); ++clientIterator){
		(*clientIterator)->writeMessagesInQueue(messageStart);
	}
}

list<Message*> Server::getProtagonistasMessages(){
	list<Message*> listaDeProtagonistas;
	map<int,EntidadDinamica*>* protagonistas = this->gController->getJuego()->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it = protagonistas->begin(); it != protagonistas->end();++it){
		//0 : conectado, -1 Desconectado
		int clientConnected = this->clients.at((*it).second->getOwner())->getStatus();
		Message* msg = it->second->getMessage();
		msg->setClientConnected(clientConnected);
		listaDeProtagonistas.push_back(msg);
	}
	return listaDeProtagonistas;
}

void Server::processReceivedMessages(){
	this->readQueue->lockQueue();
	//TODO revisar, hoy no usamos la lista idEntitiesUpdated porque notificamos lo que se este "moviendo"
	this->idEntitiesUpdated.clear();
	while( !this->readQueue->isEmpty() ){
		Message* messageUpdate = this->readQueue->pullTailWithoutLock();
		bool msgProcessed = this->checkForPingMsg(messageUpdate);
		if(!msgProcessed){
			msgProcessed = this->checkForExitMsg(messageUpdate);
		}
		if(!msgProcessed){
			msgProcessed = this->checkForAttackMsg(messageUpdate);
		}
		if(!msgProcessed){
			msgProcessed = this->checkForCreateMsg(messageUpdate);
		}
		if(!msgProcessed){
			msgProcessed = this->checkForUpdMsg(messageUpdate);
		}
		if(!msgProcessed){
			msgProcessed = this->checkForBuildingMsg(messageUpdate);
		}

		if(!msgProcessed){
			stringstream ss;
			ss << "No se que hacer con el mensaje : "<< messageUpdate->toString();
			Logger::get()->logInfo("Server","processReceivedMessages",ss.str());
		}
	}
	this->readQueue->unlockQueue();
}

bool Server::checkForPingMsg(Message* msg){
	if( msg->getTipo() == "ping" ){
		this->clients.at(msg->getName())->reporting();
		return true;
	}
	return false;
}

bool Server::checkForExitMsg(Message* msg){
	stringstream ss;
	if( msg->getTipo() == "exit" ){
		//TODO destruir el cliente que se esta desconectando
		ss.str("");
		ss << "Client " << msg->getName() << " was disconected";
		Logger::get()->logInfo("Server","processReceivedMessages", ss.str());
		this->clients.at(msg->getName())->disconect();
		return true;
	}
	return false;
}

bool Server::checkForAttackMsg(Message* msg){
	EntidadDinamica* entityToUpd = this->gController->getJuego()->getDinamicEntityById(msg->getId());	
	if( this->gameRunning && msg->getTipo() == "attack" ){		
		//si la entidad ya tenia un target empieza a atacar
		if( entityToUpd->getTarget() != 0 ){
			entityToUpd->prepareToInteract(true);
		//la entidad empieza a dirigirse a la posicion del target
		}else{
			int target = msg->getTarget();
			pair<int,int> targetPosition = this->gController->getJuego()->getEntityById(target)->getPosition();
			this->gController->getJuego()->setPlaceToGo(entityToUpd->getId(), targetPosition.first, targetPosition.second);
			this->gController->getJuego()->getEntityById(entityToUpd->getId())->setTarget(target);
			this->idEntitiesUpdated.push_back(entityToUpd->getId());
		}
		return true;
	
	}else if( this->gameRunning && msg->getTipo() == "pursuit" ){
		int target = msg->getTarget();
		pair<int,int> targetPosition = this->gController->getJuego()->getEntityById(target)->getPosition();
		this->gController->getJuego()->setPlaceToGo(entityToUpd->getId(), targetPosition.first, targetPosition.second);
		this->gController->getJuego()->getEntityById(entityToUpd->getId())->setTarget(target);
		this->idEntitiesUpdated.push_back(entityToUpd->getId());
		entityToUpd->prepareToInteract(false);
		return true;
	}
	return false;
}

bool Server::checkForCreateMsg(Message* msg){
	if( this->gameRunning && msg->getTipo() == "create" ){
		this->gController->getJuego()->createNewEntitie(msg->getOwner(),msg->getName(), msg->getId());
		return true;
	}
	return false;
}

bool Server::checkForUpdMsg(Message* msg){
	if( this->gameRunning && msg->getTipo() == "update" ){
		int idUpdate = msg->getId();
		this->gController->getJuego()->setPlaceToGo(idUpdate, msg->getPositionX(), msg->getPositionY());
		this->gController->getJuego()->getEntityById(idUpdate)->setTarget(0);
		this->idEntitiesUpdated.push_back(idUpdate);
		return true;
	}
	return false;
}

bool Server::checkForBuildingMsg(Message* msg){
	if( this->gameRunning && ( msg->getTipo() == "building" ||  msg->getTipo() == "build" ) ){
		int idBuilder = msg->getId();
		int x = 0;
		int y = 0;
		int idTarget = 0;
		if(  msg->getTipo() == "building" ){
			//Creo una entidad
			x = msg->getPositionX() + this->gameSettings->getConfigAttributeOfEntityAsInt(msg->getName(), "ancho_base");
			y = msg->getPositionY() + this->gameSettings->getConfigAttributeOfEntityAsInt(msg->getName(), "alto_base");
			idTarget = this->gController->getJuego()->buildEntity(msg->getName(), msg->getPositionX(), msg->getPositionY(), msg->getOwner());
		}else{
			// ayudo a construir una entidad ya creada
			EntidadPartida* target = this->gController->getJuego()->getEntityById(msg->getTarget());
			x = target->getPosition().first;
			y = target->getPosition().second;
			idTarget = target->getId();
		}
		this->gController->getJuego()->setPlaceToGo(idBuilder, x, y);
		EntidadDinamica* entityToUpd = this->gController->getJuego()->getDinamicEntityById(msg->getId());
		entityToUpd->prepareToInteract(true);
		entityToUpd->setTarget(idTarget);
		return true;
	}
	return false;
}

void Server::notifyClients(){
	this->sendDinamicEntitesChanges();
	this->sendFallenEntites();
	this->sendNewEntities();
	this->sendNewsResourses();
	this->gController->getJuego()->cleanNewEntities();
	this->pingMessage();
}

void Server::sendDinamicEntitesChanges(){
	map<int,EntidadDinamica*>* protagonistas = this->gController->getJuego()->getDinamicEntities();
	for(map<int,EntidadDinamica*>::iterator it=protagonistas->begin(); it!=protagonistas->end();++it){
		if ( it->second->hasToNotify() ){
			Message* messageUpdate = new Message(it->second->getId(),"update");
			messageUpdate->setPosition(it->second->getPosition());
			messageUpdate->setHealth(it->second->getHealth());
			messageUpdate->setPrecision(it->second->getPrecision());
			messageUpdate->setStrength(it->second->getStrength());

			list<Client*> activeClients = getActiveClients();
			for(list<Client*>::iterator clientIterator = activeClients.begin(); clientIterator != activeClients.end(); ++clientIterator){
				(*clientIterator)->writeMessagesInQueue(messageUpdate);
			}
		}
	}
}

void Server::sendNewEntities(){
	list<EntidadPartida*>* newEntities = this->gController->getJuego()->getNewEntitiesToNotify();
	for(list<EntidadPartida*>::iterator it = newEntities->begin(); it != newEntities->end();++it){
		if((*it)->getHealth()>0){
			Message* newEntity = new Message((*it)->getId(),  DefaultSettings::getTypeEntity((*it)->getName()));
			newEntity->setName((*it)->getName());
			newEntity->setPosition((*it)->getPosition());
			newEntity->setOwner((*it)->getOwner());
			newEntity->setHealth((*it)->getHealth());
			newEntity->setBuilding((*it)->isConstructionCompleted());
			Logger::get()->logDebug("Server", "sendNewEntities", newEntity->toString());


			list<Client*> activeClients = getActiveClients();
			for(list<Client*>::iterator clientIterator=activeClients.begin(); clientIterator!=activeClients.end(); ++clientIterator){
				if((*clientIterator)->getUserName()!=(*it)->getOwner() || this->gameRunning){
					//no notifico al dueño del personaje porque ya lo recibio, salvo que la partida ya este corriendo
					(*clientIterator)->writeMessagesInQueue(newEntity);
				}
			}

		}
	}
}

void Server::sendNewsResourses(){

}

void Server::sendFallenEntites(){
	list<EntidadPartida> fallenEntities = this->gController->getJuego()->getFallenEntities();
	for(list<EntidadPartida>::iterator itFallenEntities = fallenEntities.begin(); itFallenEntities != fallenEntities.end(); ++itFallenEntities ){
		if(itFallenEntities->getName() == "flag"){
			this->gController->getJuego()->transferEntitiesToUser(itFallenEntities->getOwner(), itFallenEntities->getAttacker());
		}
		Message* msgfallenEntity = new Message();
		msgfallenEntity->setId((*itFallenEntities).getId());
		msgfallenEntity->setType("deleteEntity");
		list<Client*> activeClients = getActiveClients();
		for(list<Client*>::iterator clientIterator = activeClients.begin(); clientIterator != activeClients.end(); ++clientIterator){
			(*clientIterator)->writeMessagesInQueue(msgfallenEntity);
		}
	}
}

void Server::sendNewStaticEntites(){
	//TODO hacerlo ;)
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

			//Cuando el cliente se desconecta mando un solo mensaje
			Message* messageDisconnect = new Message();
			messageDisconnect->clientDisconect((*clientIterator)->getUserName());
			for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
				(*clientIt)->writeMessagesInQueue(messageDisconnect);
			}

			list<int> entitiesToDisconect = gController->getEntitiesOfClient((*clientIterator)->getUserName());
			for(list<int>::iterator it=entitiesToDisconect.begin(); it!=entitiesToDisconect.end();++it){
				this->gController->getJuego()->deleteEntity(*it);
			}
		}else if(this->gController->checkIfClientLostGame((*clientIterator)->getUserName())){
			Message* messageClientLost = new Message();
			messageClientLost->clientLost((*clientIterator)->getUserName());
			for(list<Client*>::iterator clientIt=activeClients.begin(); clientIt!=activeClients.end(); ++clientIt){
					(*clientIt)->writeMessagesInQueue(messageClientLost);
			}
			//TODO revisar como hacer cuando el tipo de juego es captura de bandera porque ahi pasan las entidades de dueño
			list<int> entitiesToDisconect = gController->getEntitiesOfClient((*clientIterator)->getUserName());
			for(list<int>::iterator it=entitiesToDisconect.begin(); it!=entitiesToDisconect.end();++it){
				this->gController->getJuego()->deleteEntity(*it);
			}
			this->gController->delay(1000);
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
	//Cada vez que se conecta un cliente agrego el centro civico, los aldeanos y demas personajes de aucerdo a la partida
	pair<int,int> offsetClient = this->gController->createEntitiesForClient(newClient->getUserName(), this->clients.size());
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

void Server::sendColours(Client* client) {
	client->setColour(this->clients.size());
	Message* msg = new Message();
	msg->colourOfClient(client->getUserName(), client->getColour());
	client->writeMessagesInQueue(msg);
	//Le mando a los clientes anteriores el color del nuevo cliente
	list<Client*> activeClients = this->getActiveClients();
	for (list<Client*>::iterator it = activeClients.begin() ; it != activeClients.end() ; it++ ) {
			(*it)->writeMessagesInQueue(msg);
	}
	//Le mando al cliente nuevo el color de todos los clientes anteriores
	for (map<string,Client*>::iterator it = clients.begin() ; it != clients.end() ; it++ ) {
		Message* msgOldClient = new Message();
		msgOldClient->colourOfClient(it->second->getUserName(), it->second->getColour());
		client->writeMessagesInQueue(msgOldClient);
	}
}

Server::~Server() {
	for(map<string,Client*>::iterator it=this->clients.begin(); it != this->clients.end(); ++it){
		it->second->~Client();
	}
	//this->gameSettings = NULL;
	//this->gController = NULL;
	readQueue->~SocketQueue();
	//delete(this->readQueue);
	close(this->serverSocket);
}
