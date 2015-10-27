/*
 * Juego.cpp
 *
 *  Created on: 30 de ago. de 2015
 *      Author: jorge
 */

#include "../../Headers/Modelo/Juego.h"

using namespace std;

Juego::Juego() {
	gameSettings = GameSettings::GetInstance();
	this->juegoFinalizado = false;
	this->mapa = new Mapa();
	this->currentAge = gameSettings->getAgeOfEmpires();
	this->resourseManager = new ResourceManager(this->mapa);
}

void Juego::agregarProtagonista(string owner){
	//TODO revisar que le ponemos en tipo
	pair<int,int> positionOfProtagonista = this->mapa->getAvailablePosition();
	cout << "Posicion del protagonista: X: "<< positionOfProtagonista.first << " Y: " <<positionOfProtagonista.second << endl;
	EntidadDinamica *protagonista = new EntidadDinamica(gameSettings->getTipoProtagonista(),
				gameSettings->getVelocidadPersonaje(),
				positionOfProtagonista.first,
				positionOfProtagonista.second,
				gameSettings->getProtagonistaPixelDimension(),
				gameSettings->getProtagonistaPixelDimension());

	protagonista->setOwner(owner);
	protagonista->setInitialScreenPosition(gameSettings->getPosXProtagonista(),gameSettings->getPosYProtagonista());
	protagonista->setRangeVisibility(gameSettings->getRangeVisibility());
	this->protagonistas.insert(make_pair(protagonista->getId(),protagonista));
	//defino una lista con los nuevos protagonistas para que se enteren los clientes anterores
	this->newProtagonistas.push_back(protagonista);
	//cout << "creo un personaje en: "<< owner<< " "<< positionOfProtagonista.first << " y: " << positionOfProtagonista.second << endl;
}

Mapa* Juego::getMap(){
	return this->mapa;
}

map<int,EntidadDinamica*> Juego::getProtagonistas(){
	return this->protagonistas;
}

list<EntidadDinamica*>* Juego::getNewProtagonistasToNotify(){
	return &this->newProtagonistas;
}

void Juego::cleanNewProtagonistas(){
	this->newProtagonistas.clear();
}

pair<int,int>* Juego::getPositionOfProtagonistaById(int idBuscado){
	return this->protagonistas.at(idBuscado)->getPosition();
}

void Juego::actualizarProtagonistas(){
	for(map<int,EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
		(*it).second->trasladarse();
	}
}

string Juego::getCurrentAge(){
	return this->currentAge;
}


void Juego::setDestinoProtagonista(int idProtagonista, int x,int y){
	/*TODO: seteo solo las coordenadas fisicas, antes seteaba las de pantalla tambien,
	 * revisar si esto no rompe nada ya que las coordenadas de pantalla deberian setearse solo en la vista*/
	EntidadDinamica *protagonistaToUpdate = this->protagonistas.at(idProtagonista);

	PathFinder* pathF = new PathFinder(protagonistaToUpdate->getPosition()->first,
									  protagonistaToUpdate->getPosition()->second,
									  x,y,this->mapa,this->resourseManager);

	//calculo el camino minimo para llegar a destino
	list<pair<int,int> >* caminoMinimo = pathF->buscarCamino();
	stringstream ss;
	for(list<pair<int,int> >::iterator it = caminoMinimo->begin();it != caminoMinimo->end();++it){
		ss.str("");
		ss<<(*it).first<<","<<(*it).second;
		Logger::get()->logDebug("Juego","setDestinoProtagonista",ss.str());
	}
	delete pathF;
	protagonistaToUpdate->setCamino(caminoMinimo);

	protagonistaToUpdate->nextPosition();

	//TODO aca le tiene que pasar la screen position en isometricas
	//protagonistaToUpdate->setScreenPosition(x,y);
}

void Juego::terminarJuego(){
	this->juegoFinalizado = true;
}
bool Juego::getStatusPartida(){
	return this->juegoFinalizado;
}

pair<int,int> Juego::getIsometricPosition(EntidadPartida* entidad){
	//TODO: esto no deberia estar solo en la vista?

	pair<int,int> isometricPosition;
	//hacemos coincidir el vertice superior izquierdo de la entidad con el tile
	isometricPosition.first = (entidad->getPosition()->first - entidad->getPosition()->second) * gameSettings->getTileSize() + gameSettings->getScreenWidth() / 2;
	isometricPosition.second = (entidad->getPosition()->first + entidad->getPosition()->second) * gameSettings->getTileSize() / 2  ;

	//ahora hay que centrar la entidad con el tile
	isometricPosition.first = isometricPosition.first - (entidad->getWidth() - 1)  *  gameSettings->getTileSize();
	isometricPosition.second = isometricPosition.second - (entidad->getLength() - 1) *  gameSettings->getTileSize() / 2;
	return isometricPosition;
}

Juego::~Juego() {
	for(map<int,EntidadDinamica*>::iterator it=this->protagonistas.begin(); it!=this->protagonistas.end(); ++it){
			delete(it->second);
	}
	delete(this->mapa);
	this->mapa = NULL;
	this->gameSettings=NULL;
}
