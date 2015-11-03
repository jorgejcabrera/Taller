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


string LoginVista::askUserName(string initialMessage){
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	string userName = "";

	//Enable text input
	SDL_StartTextInput();

	//While application is running
	while( !quit ){
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//presione ENTER
			if( (e.type == SDL_QUIT) || (e.type==SDL_KEYDOWN && e.key.keysym.sym== 13 && userName.length()>0)){
				cout << userName<<endl;
				quit = true;
			}
			else if( e.type == SDL_KEYDOWN ){
				//borro el ultimo caracter
				if( e.key.keysym.sym == SDLK_BACKSPACE && userName.length() > 0 ){
					userName.erase(userName.end()-1);
				}
			}else if( e.type == SDL_TEXTINPUT ){
				//Append character
				userName += e.text.text;
			}
		}
		PicassoHelper::GetInstance()->clearView();
		PicassoHelper::GetInstance()->renderBackgroud();
		PicassoHelper::GetInstance()->renderText(250,450,initialMessage.size()*10,30,initialMessage,0,0,0);
		PicassoHelper::GetInstance()->renderText(400,500,userName.size()*15,40,userName,0,0,0);
		PicassoHelper::GetInstance()->renderView();
	}

	//Disable text input
	SDL_StopTextInput();
	return userName;
}
