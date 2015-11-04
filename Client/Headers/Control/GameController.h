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
#include "../Control/UtilsController.h"
#include "../Utils/Socket/Message.h"

class GameController {

private:
	UtilsController* utils;
	SDL_Event* event;
	JuegoVista* juegoVista;
	GameSettings* gameSettings;

	int posMouseX;
	int posMouseY;
	bool salirDelJuego;
	bool reiniciar;
	int runCycles;
	int maxFramesPerSecond;
	int inicioDeCiclo;
	bool gameRunning;
	/*
	*retorna la posicion cartesiana de correspondiente a donde se hizo click, y 
	*le setea a la
	*entidad la posicion de pantalla donde debería ser dibujado.
	**/
	pair<int,int> moveCharacter(EntidadDinamicaVista* entidad);
	/*
	*devuelve el offset coorespondiente al scroll de la pantalla
	**/
	pair<int,int> getOffset(int mouseX,int mouseY);

public:
	GameController();
	
	bool reiniciarJuego();
	
	void actualizarJuego();

	void addTileToCharacter(int id,int x,int y);
	/*
	*actualiza la posicion de la entidad que corresponde al id pasado como parametro
	* */
	void updatePosition(int id);
	
	void render();
	/*
	*transforma eventos de la partida del cliente en mensajes para ser 
	*enviados alservidor
	* */
	Message* getMessageFromEvent(string userId);

	int getRunCycles();
	
	int getMaxFramesPerSecond();
	
	bool finDeJuego();
	
	virtual ~GameController();
	
	void delay();
	
	void resetPath(int id);

	JuegoVista* getJuegoVista();

	void setGameRunning();

	bool gameIsRunning();
};

#endif /* GAMECONTROLLER_H_ */
