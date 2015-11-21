/*
 * GameController.h
 *
 *  Created on: Sep 11, 2015
 *      Author: juan
 */

#ifndef GAMECONTROLLER_H_
#define GAMECONTROLLER_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "../Vista/JuegoVista.h"
#include "../Modelo/GameSettings.h"
#include "../Modelo/DefaultSettings.h"
#include "../Modelo/EntidadConfig.h"
#include "../Modelo/Mixer.h"
#include "../Control/UtilsController.h"
#include "../Utils/Socket/Message.h"
#include <list>

enum game{
	WIN,
	LOSE,
	RUNNING,
	DISCONNECTED
};

class GameController {

private:
	UtilsController* utils;
	SDL_Event* event;
	JuegoVista* juegoVista;
	GameSettings* gameSettings;
	Mixer* mixer;

	list<EntidadPartidaVista*> entitiesSelected;
	int initialPosMouseX;
	int initialPosMouseY;
	string pressedMouseButton;
	int finalPosMouseX;
	int finalPosMouseY;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	bool gameRunning;
	string clientName;
	game gameStatus;
	/*
	* retorna la posicion cartesiana valida correspondiente al lugar donde se hizo click
	* */
	pair<int,int> getValidCartesianPosition(EntidadPartidaVista* entidad);
	/*
	* devuelve el offset coorespondiente al scroll de la pantalla
	* */
	pair<int,int> getOffset(int mouseX,int mouseY);

	/*
	* nombre de la entidad que quiero construir
	* */
	string entityToBuild;
public:
	GameController();
	/*
	* actualiza las posiciones de todas las entidades en el mapa y el offset
	* */
	void updateGame();
	/*
	* actualiza la posicion de la entidad que corresponde al id pasado como parametro
	* */
	void updatePosition(int id);
	/*
	* transforma eventos de la partida del cliente en mensajes para ser enviados alservidor
	* */
	list<Message*> getMessagesFromEvent(string userId);	/*
	* se fija las entidades que tienen seleccionado algun target, y si visualmente están preparadas para
	* pelear le envían la novedad al servidor.
	* */
	void readyToAttack(list<Message*>* messages);
	JuegoVista* getJuegoVista();
	int getRunCycles();
	int getMaxFramesPerSecond();
	void delay();
	/*
	 * Ejecuto un delay especifico
	 */
	void delay(int delayMs);
	void setGameRunning();
	bool gameIsRunning();
	/*
	* seteo el clientName porque despues lo necesito para seleccionar las entidades
	* */
	void setClientName(string name);
	/*
	* Seteo la partida como GANADA
	*/
	void winGame();
	/*
	 * Seteo la partida como PERDIDA
	 */
	void loseGame();
	/*
	 * Servidor desconectado
	 */
	void disconnectedGame();
	/*
	 * Muestra el mensaje final, si gano o perdio
	 */
	void showFinalMessage();
	/*
	 * Maneja el menu interactivo, en caso de tener seleccionado un town center o una barrack
	 */
	list<Message*> interactiveMenu(int posMouseX,int posMouseY);
	/*
	* Posiciono el edificio donde lo quiero crear
	* */
	void placeTheBuilding(string buildingName);

	/*
	 * selecciona una o varias entidades
	 */
	void selection();

	list<Message*> action();
	/*
	* obtiene la posicion del mouse y devuelve las coordenadas cartecianas
	* */
	pair <int,int> convertMousePositionToCartesianPosition();
	/*
	 * controla si el cliente tiene los recursos disponibles para crear la entidad
	 */
	bool hasResourcesRequired(string entity);
	/*
	 * Decrementa los recursos necesarios para la entidad
	 */
	void decreaseResources(string entity);
	Mixer * getMixer();
	virtual ~GameController();
};

#endif /* GAMECONTROLLER_H_ */
