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
#include "../../Headers/Modelo/Mixer.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <list>
#include "TileVista.h"
#include "EntidadEstaticaVista.h"
#include "EntidadSemiEstaticaVista.h"
#include "EntidadDinamicaVista.h"
#include "EntidadPartidaVista.h"
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
	ResourceCounter* resourceCounter;
	/*
	* offset correspondiente al desplazamiento por el offset
	* */
	pair<int,int> offset;
	/*
	* colores de los clientes
	* */
	map<string,colour> coloursOfClients;
	/*
	* entidades del mapa
	* */
	list<TileVista*> tiles;
	map<int, EntidadEstaticaVista*> buildings;
	map<int, EntidadSemiEstaticaVista*> semiEstaticos;
	map<int, EntidadDinamicaVista*> personajes;
	/*
	* métodos para renderizar el juego
	* */
	void drawIsometricMap();
	void drawStaticEntities(int runCycles);
	void drawDinamicEntities(int runCycles);
	void drawSemiStaticsEntities(int runCycles);
	void drawMenu();
	void drawMiniMap();
	void drawFog();
	/*
	* Dibujo la entidad que estoy queriendo construir
	* */
	void drawEntityForBuild();
	void drawResources(ResourceCounter* resourceCounter);
	/*
	 * Lista de pares x,y donde tengo que construir el edificio, lo tengo para mostrarlo diferente en la vista
	 */
	list<pair< int,int > > tilesForBuilding;
	bool availablePosForBuilding;
	string entityForBuild;

public:
	JuegoVista();
	/*
	* metodo que se encarga de dibujar mapa y todas las entidades
	* */
	void render(int ciclos, ResourceCounter* resourceCounter, string userName);
	void deleteEntityById(int id);
	/*
	* devuelve la información de la entidad en una colección
	* */
	map<string,string> getEntityAttributes(EntidadPartidaVista* entidad);
	/*
	*?
	* */
	void createView();
	void updateOffset(int offsetX,int offsetY);
	void addTile(string surface, int x, int y);
	void addStaticEntity(int id, string type, int x, int y,string owner,int health, bool completed);
	void addSemiEstaticEntity(int id, string type, int x, int y, string owner,int health, bool completed);
	void addDinamicEntity(int id, string type, int x, int y, int active, string owner,int health,int strength,float precision);
	pair<int,int>* getOffset();
	map<int,EntidadDinamicaVista*>* getPersonajes();
	map<int, EntidadDinamicaVista*>* getDinamicEntities();
	EntidadDinamicaVista* getDinamicEntityById(int id);
	EntidadPartidaVista* getEntityById(int id);
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
	* QUE HACE ESTE METODO? 
	* */
	void setFoggedTiles(string userName);
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
	void setResourceCounter(ResourceCounter* resourceCounter);
	ResourceCounter* getResourceCounter();
	/*
	* Dadas las coordenadas x, y las agrego a la lista de tiles donde quiero construir el edificio
	* */
	void addTileForBuilding(int x, int y);
	/*
	 * Limpia la lista de tiles para ubicar el edificio, porque antes de mandar una tanda de tiles tengo que limpiar la lista
	 */
	void clearTilesForBuilding();
	/*
	* Aparte de llamar a  clearTilesForBuilding borra el nombre de la entidad a construir, solo se ejecuta una vez que se hizo click eligiendo la posicion donde construir
	* */
	void clearAllDataForBuilding();
	/*
	 * Devuelvo si las posiciones para el edificio están disponibles
	 */
	bool isAvailablePosForBuild();
	/*
	 * Seteo la entidad que estoy tratando de construir
	 */
	void setEntityForBuild(string entityName);
	/*
	 * preparo un map mediante la lista recibida, para pasarselo al menuVista y que luego lo renderize
	 */
	void entitiesToRenderInMenu(list<EntidadPartidaVista*> entities);
	/*
	* obtengo el booleando que indica si la posicion esta disponible para construir el edificio
	* */
	bool isAvailablePosForBuilding();
	~JuegoVista();
};

#endif /* SOURCE_VISTA_JUEGOVISTA_H_ */
