/*
 * LoginVista.cpp
 *
 *  Created on: 1 de nov. de 2015
 *      Author: jorlando
 */


#include "../../Headers/Vista/LoginVista.h"

LoginVista::LoginVista() {
	pathImage = "../../Taller/Images/Menu/Menu3.jpg";
}


LoginVista::~LoginVista() {
}


string LoginVista::askInfoUser(string initialMessage){
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
		PicassoHelper::GetInstance()->clearView();
		PicassoHelper::GetInstance()->renderBackgroud();
		PicassoHelper::GetInstance()->renderText(250,450,initialMessage.size()*10,30,initialMessage,0,0,0);
		PicassoHelper::GetInstance()->renderText(400,500,infoUser.size()*15,40,infoUser,0,0,0);
		PicassoHelper::GetInstance()->renderView();
	}
	//Disable text input
	SDL_StopTextInput();
	return infoUser;
}

void LoginVista::renderFinishLogin(string finalMessage){
	PicassoHelper::GetInstance()->clearView();
	PicassoHelper::GetInstance()->renderBackgroud();
	PicassoHelper::GetInstance()->renderText(250,450,finalMessage.size()*10,30,finalMessage,0,0,0);
	PicassoHelper::GetInstance()->renderView();
}
