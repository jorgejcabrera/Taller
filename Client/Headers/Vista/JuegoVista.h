/*
 * JuegoVista.h
 *
 *  Created on: 1 de set. de 2015
 *      Author: jorge
 */

#ifndef HEADERS_VISTA_JUEGOVISTA_H_
#define HEADERS_VISTA_JUEGOVISTA_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../../Headers/Modelo/GameSettings.h"
#include "../../Headers/Modelo/ResourceCounter.h"
#include "../../Headers/Modelo/PicassoHelper.h"
#include "../../Headers/Control/UtilsController.h"
#include "../../Headers/Modelo/DefaultSettings.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include "TileVista.h"
#include "EntidadEstaticaVista.h"
#include "EntidadSemiEstaticaVista.h"
#include "EntidadDinamicaVista.h"
#include "../Utils/Logger.h"
#include "MenuVista.h"
#include "MiniMapVista.h"
#include "LoginVista.h"

using namespace std;

class JuegoVista {
private:
	GameSettings* gameSettings;
	PicassoHelper* picassoHelper;
	MenuVista* menuVista;
	MiniMapVista* miniMapVista;
	LoginVista* loginVista;
	/*
	* offset correspondiente al desplazamiento por el offset
	* */
	pair<int,int> offset;
	/*
	* colección de recursos a ser consumidos cuando la entidad llegue a la posicion donde esta el recurso
	* */
	map<pair<int,int>,int> resoursesToConsume;
	/*
	* entidades del mapa
	* */
	list<TileVista*> tiles;
	/*
	* colores de los clientes
	* */
	map<string,colour> coloursOfClients;
	map<int, EntidadEstaticaVista*> buildings;
	map<int, EntidadSemiEstaticaVista*> semiEstaticos;
	map<int, EntidadDinamicaVista*> personajes;
	map<int, EntidadDinamicaVista*> misPersonajes;
	/*
	* métodos para renderizar el juego
	* */
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
	void drawDinamicEntity(EntidadDinamicaVista* entity,int runCycles,bool isMyEntity);
	void drawSemiStaticsEntities(int runCycles);
	void drawMenu();
	void drawMiniMap();
	void drawFog();
	void drawResources(ResourceCounter* resourceCounter);
	/*
	* devuelve la información de la entidad en una colección
	* */
	map<string,string> getEntityAttributes(EntidadPartidaVista* entidad);

public:
	JuegoVista();
	/*
	* metodo que se encarga de dibujar mapa y todas las entidades
	* */
	void render(int ciclos, ResourceCounter* resourceCounter);
	/*
	* agrega un recurso que será consumido cuando la entidad ocupe el correspondiente tile
	* */
	void addResourceToConsume(int id);
	/*
	* si hay algún recurso para consumir en la posicion de la entidad pasada como parametro devuelve el id del
	* recurso, caso contrario devuelve 0
	* */
	int consumeResource(EntidadDinamicaVista* entidad);
	/*
	* borra el recurso o el edificio correspondiente al id pasado como parametro
	* */
	void deleteStaticEntityById(int id);
	/*
	* borra las entidades dinamicas que se quedaron sin vida
	* */
	void deleteDinamicEntityById(int id);
	/*
	*?
	* */
	void createView();
	void updateOffset(int offsetX,int offsetY);
	void setResources(int alimento, int madera, int oro);
	void addTile(string surface, int x, int y);
	void addBuilding(int id, string type, int x, int y,string owner);
	void addSemiEstaticEntity(int id, string type, int x, int y, string owner);
	void addDinamicEntity(int id, string type, int x, int y, bool imTheOwner, int active, string owner,int health,int strength,float precision);
	pair<int,int>* getOffset();
	map<int,EntidadDinamicaVista*>* getMyEntities();
	map<int,EntidadDinamicaVista*>* getPersonajes();
	EntidadDinamicaVista* getEntityById(int id);
	MenuVista* getMenuVista();
	/*
	* ?
	* */
	void setVisibleTile(int x,int y);
	/*
	* ?
	* */
	bool isEntitySeen(pair<int,int>* entityPos, int lenght);
	/*
	* devuelve en una colección toda la información de la entidad ubicada en 
	* la posición pasada como parámetro
	* */
	map<string,string> getEntityAt(pair<int,int> position);
	/*
	* devuelve en una colección toda la información de la entidad dinámica ubicada
	* en la posición pasada como parámetro
	* */
	map<string,string> getDinamicEntityAt(pair<int,int> position);
	/*
	* QUE HACE ESTE METODO? 
	* */
	void setFoggedTiles();
	/*
	* ?
	* */
	bool isEnemyEntityVisible(pair< int, int> pos);
	/*
	* genero la ventana donde el usuario ingresa el userName
	* */
	string renderUserInputView(string initialMessage);
	/*
	* Muestro el mensaje: "Esperando mas clientes" o "Ya se alcanzo el limite de usuarios conectados"
	* */
	void renderFinishLogin(string finalMessage);
	/*
	* ?
	* */
	void setColour(string owner,int colour);
	/*
	 * Renderiza la vista actual y el mensaje pasado por parametro
	 */
	void renderFinalMessage(string finalMessage);
	/*
	 * Borro las entidades del cliente porque se desconecto
	 */
	void deleteEntitiesOfClient(string clientName);
	/*
	 * Dado el enum del color, devuelvo el path de la imagen de la bandera correspondiente
	 */
	string getPathFlagImage(colour colorClient);
	/*
	 * Convierte el enumaro colo a un string
	 */
	string convertColourToString(colour colorClient);
	~JuegoVista();
};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
