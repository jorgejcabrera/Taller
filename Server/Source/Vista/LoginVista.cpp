/*
 * LoginVista.cpp
 *
 *  Created on: 1 de nov. de 2015
 *      Author: jorlando
 */

//SERVER

#include "../../Headers/Vista/LoginVista.h"

LoginVista::LoginVista() {
	this->picassoHelper = PicassoHelper::GetInstance();
	this->buttonDimension = 130;
	this->xCivic = 300;
	this->xFlag = this->xCivic + buttonDimension+ 40;
	this->xRegicide = this->xCivic + buttonDimension*2 + 80;
	this->yButtons = 180;
	this->game = "";
	this->clientNumber = 0;
}

int LoginVista::askPort(){
	string initialMessage = "Ingrese puerto de conexion";
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	string infoUser = "";

	//Enable text input
	SDL_StartTextInput();

	//While application is running
	while( !quit ){
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ){
			//presione ENTER
			if( (e.type == SDL_QUIT) || (e.type==SDL_KEYDOWN && e.key.keysym.sym== 13 && infoUser.length()>0)){
				quit = true;
			}
			else if( e.type == SDL_KEYDOWN ){
				//borro el ultimo caracter
				if( e.key.keysym.sym == SDLK_BACKSPACE && infoUser.length() > 0 ){
					infoUser.erase(infoUser.end()-1);
				}
			}else if( e.type == SDL_TEXTINPUT ){
				//Append character
				infoUser += e.text.text;
			}
		}
		this->picassoHelper->clearView();
		this->picassoHelper->renderBackgroud();
		this->picassoHelper->renderText(300,100,initialMessage.size()*15,50,initialMessage,255,255,255);
		this->picassoHelper->renderText(this->xFlag,this->yButtons,infoUser.size()*50,90,infoUser,255,255,255);
		this->picassoHelper->renderView();
	}
	//Disable text input
	SDL_StopTextInput();
	return atoi(infoUser.c_str());
}


string LoginVista::askGameType(){
	string initialMessage = "Seleccione el tipo de partida";
	string pathCivicCenter = "../../Taller/Images/Industrial_Age/Barracks-3x3.png";
	string pathFlag = "../../Taller/Images/Flags/red.png";
	string pathRegicide = "../../Taller/Images/Menu/corona.png";

	bool quit = false;
	int clickX = 0;
	int clickY = 0;
	SDL_Event event;

	this->picassoHelper->clearView();
	this->picassoHelper->renderBackgroud();
	this->picassoHelper->renderText(300,100,initialMessage.size()*15,50,initialMessage,255,255,255);

	this->picassoHelper->renderObject(pathCivicCenter, this->xCivic, this->yButtons, this->buttonDimension, this->buttonDimension);
	string message = "Centro Civico";
	this->picassoHelper->renderText(this->xCivic,this->yButtons+this->buttonDimension,message.size()*10,20,message,255,255,255);

	this->picassoHelper->renderObject(pathFlag,this->xFlag, this->yButtons, this->buttonDimension, this->buttonDimension);
	message = "Captura Bandera";
	this->picassoHelper->renderText(this->xFlag-10,this->yButtons+this->buttonDimension,message.size()*10,20,message,255,255,255);

	this->picassoHelper->renderObject(pathRegicide,this->xRegicide, this->yButtons, this->buttonDimension, this->buttonDimension);
	message = "Regicidio";
	this->picassoHelper->renderText(this->xRegicide+20,this->yButtons+this->buttonDimension,message.size()*10,20,message,255,255,255);

	this->picassoHelper->renderView();
	while( !quit ){
		while( SDL_PollEvent( &event ) != 0 ){
			if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&clickX,&clickY);
				quit = this->validateSelection(clickX, clickY);
			}
		}
	}
	return this->game;
}

int LoginVista::askClientsNumber(){
	string initialMessage = "Seleccione cantidad de clientes";
	string path2 = "../../Taller/Images/Menu/2.png";
	string path3 = "../../Taller/Images/Menu/3.png";
	string path4 = "../../Taller/Images/Menu/4.png";
	bool quit = false;
	int clickX = 0;
	int clickY = 0;
	SDL_Event event;

	this->picassoHelper->clearView();
	this->picassoHelper->renderBackgroud();
	this->picassoHelper->renderText(300,100,initialMessage.size()*15,50,initialMessage,255,255,255);

	this->picassoHelper->renderObject(path2, this->xCivic, this->yButtons, this->buttonDimension, this->buttonDimension);
	this->picassoHelper->renderObject(path3,this->xFlag, this->yButtons, this->buttonDimension, this->buttonDimension);
	this->picassoHelper->renderObject(path4,this->xRegicide, this->yButtons, this->buttonDimension, this->buttonDimension);

	this->picassoHelper->renderView();
	while( !quit ){
		while( SDL_PollEvent( &event ) != 0 ){
			if( event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
				SDL_GetMouseState(&clickX,&clickY);
				quit = this->validateSelection(clickX, clickY);
			}
		}
	}
	return this->clientNumber;
}

bool LoginVista::validateSelection(int x, int y){
	if(x>= this->xCivic && x<= this->xCivic+ this->buttonDimension && y >=this->yButtons && y<= this->yButtons+this->buttonDimension){
		this->clientNumber = 2;
		this->game = "CIVIC_CENTER";
		return true;
	}
	if(x>= this->xFlag && x<= this->xFlag+ this->buttonDimension && y >=this->yButtons && y<= this->yButtons+this->buttonDimension){
		this->clientNumber = 3;
		this->game = "CAPTURE_FLAG";
		return true;
	}
	if(x>= this->xRegicide && x<= this->xRegicide+ this->buttonDimension && y >=this->yButtons && y<= this->yButtons+this->buttonDimension){
		this->clientNumber = 4;
		this->game = "REGICIDE";
		return true;
	}
	return false;

}
void LoginVista::renderFinishLogin(string finalMessage){
	this->picassoHelper->clearView();
	this->picassoHelper->renderBackgroud();
	this->picassoHelper->renderText(250,450,finalMessage.size()*10,30,finalMessage,0,0,0);
	this->picassoHelper->renderView();
}

LoginVista::~LoginVista() {
	this->picassoHelper->~PicassoHelper();
}
