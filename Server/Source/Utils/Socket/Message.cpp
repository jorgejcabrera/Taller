/*
 * Message.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: jorge
 */

#include "../../../Headers/Utils/Socket/Message.h"

Message::Message(int entityId, string msgType){
	this->msg.set_id(entityId);
	this->msg.set_tipo(msgType);
}

Message::Message(){}

//Mensaje utilizado para mandar tiles o dimension de la ventana
/*Message::Message(string tipo, string nombreEntity, int xPosition, int yPosition, int mapaAncho, int mapaAlto){
	this->msg.set_id(0);
	this->msg.set_tipo(tipo);
	this->msg.set_nombre(nombreEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
	this->msg.set_ancho_base(mapaAncho);
	this->msg.set_alto_base(mapaAlto);
}*/

Message::Message(string tipo, string nombreEntity, int xPosition, int yPosition){
	this->msg.set_id(0);
	this->msg.set_tipo(tipo);
	this->msg.set_nombre(nombreEntity);
	this->msg.set_x(xPosition);
	this->msg.set_y(yPosition);
}

//Mensaje Utilizado para notificar el nombre de usuario
Message::Message(string nombre){
	this->msg.set_id(0);
	this->msg.set_tipo("username");
	this->msg.set_nombre(nombre);
}

int Message::getBaseHeigth(){
	return this->msg.alto_base();
}

void Message::setBaseHeight(int baseHeigth){
	this->msg.set_alto_base(baseHeigth);
}

int Message::getBaseWidth(){
	return this->msg.ancho_base();
}

void Message::setBaseWidth(int baseWidth){
	this->msg.set_ancho_base(baseWidth);
}

string Message::getImagePath(){
	return this->msg.imagen();
}

void Message::setImagePath(string path){
	this->msg.set_imagen(path);
}

void Message::setType(string type){
	this->msg.set_tipo(type);
}

void Message::setId(int id){
	this->msg.set_id(id);
}

//Utilizo el campo FPS para mandar 0: el cliente está conectado, -1: el cliente está DESCONECTADO
void Message::setClientConnected(int client){
	this->msg.set_fps(client);
}

int Message::getClientConnected(){
	return this->msg.fps();
}

void Message::initialOffset(int x, int y){
	this->msg.set_id(0);
	this->msg.set_tipo("offset");
	this->msg.set_x(x);
	this->msg.set_y(y);
}

void Message::pingMessage(string nombre){
	this->msg.set_id(0);
	this->msg.set_tipo("ping");
	this->msg.set_nombre(nombre);
}

void Message::clientDisconect(string clientName){
	this->msg.set_id(0);
	this->msg.set_tipo("disconnect");
	this->msg.set_nombre(clientName);
}

void Message::clientLost(string clientName){
	this->msg.set_id(0);
	this->msg.set_tipo("lost");
	this->msg.set_nombre(clientName);
}

void Message::clientWin(string clientName){
	this->msg.set_id(0);
	this->msg.set_tipo("win");
	this->msg.set_nombre(clientName);
}

void Message::startGame(){
	this->msg.set_id(0);
	this->msg.set_tipo("start");
}

string Message::toString(){
	stringstream ss;
	ss << " id: " << this->msg.id();
	ss << " tipo: " << this->msg.tipo();
	ss <<  " x: " << this->msg.x();
	ss <<  " y: " << this->msg.y();
	ss <<  " nombre: " << this->msg.nombre();
	ss << " imagen: " << this->msg.imagen();
	ss << " base: " << this->msg.ancho_base();
	ss << " base: " << this->msg.alto_base();
	ss << " fps: " << this->msg.fps();
	ss << " delay: " << this->msg.delay();
	ss << " line: " << this->msg.total_frames_line();
	ss << " dimension: " << this->msg.pixels_dimension();
	ss << " owner: "<< this->msg.owner();
	return ss.str();
}

//Mas cuatro bytes que es lo que ocupa el int del tamaño
//del mensaje que se concaten, al serializar el mensaje
int Message::getSize(){
	return this->msg.ByteSize() + sizeof(int);
}

//TODO ver si hay que hacer un delete de integer_string
char* Message::serializeToArray(){
	int size = this->msg.ByteSize();
	char* buffer = new char[ size + sizeof(int) ];
	memset(buffer, 0, size + sizeof(int));

	// convert int to char*
	char integer_string[sizeof(int)];
	memset(integer_string, 0, sizeof(int));
	sprintf(integer_string,"%d",size);

	// coloco el int en el buffer
	memcpy(buffer,integer_string,sizeof(int));

	if( this->msg.SerializePartialToArray(&buffer[sizeof(int)],size)){
		return buffer;
	}else
		return NULL;
}

void Message::setContent(msg_game message){
	this->msg = message;
}

string Message::serializeAsString(){
	return this->msg.SerializeAsString();
}

string Message::getTipo(){
	return this->msg.tipo();
}

int Message::getId(){
	return this->msg.id();
}

int Message::getPositionX(){
	return this->msg.x();
}

int Message::getPositionY(){
	return this->msg.y();
}

void Message::setName(string name){
	this->msg.set_nombre(name);
}

string Message::getName(){
	return this->msg.nombre();
}

string Message::getImagen(){
	return this->msg.imagen();
}

void Message::setFps(int fps){
	this->msg.set_fps(fps);
}

int Message::getFps(){
	return this->msg.fps();
}

void Message::setDelay(int delay){
	this->msg.set_delay(delay);
}

int Message::getDelay(){
	return this->msg.delay();
}

int Message::getTotalFramesLine(){
	return this->msg.total_frames_line();
}

void Message::setTotalFramesLine(int frames){
	this->msg.set_total_frames_line(frames);
}

int Message::getPixelsDimension(){
	return this->msg.pixels_dimension();
}

void Message::setPixelsDimension(int pixels){
	this->msg.set_pixels_dimension(pixels);
}

void Message::setOwner(string userName){
	this->msg.set_owner(userName);
}

string Message::getOwner(){
	return this->msg.owner();
}

void Message::setTarget(int entityId){
	return this->msg.set_target(entityId);
}

int Message::getTarget(){
	return this->msg.target();
}

void Message::setHealth(int health){
	this->msg.set_health(health);
}

int Message::getHealth(){
	return this->msg.health();
}

void Message::setStrength(int strength){
	this->msg.set_strength(strength);
}

int Message::getStrength(){
	return this->msg.strength();
}

void Message::setPrecision(float precition){
	this->msg.set_precition(precition);
}

float Message::getPrecision(){
	return this->msg.precition();
}

void Message::setPosition(pair<int,int> position){
	this->msg.set_x(position.first);
	this->msg.set_y(position.second);
}

void Message::activeTile( int x, int y) {
	this->msg.set_x(x);
	this->msg.set_y(y);
	this->msg.set_id(0);
	this->msg.set_tipo("fog");
}

void Message::colourOfClient(string client, int colour){
	this->msg.set_x(colour);
	this->msg.set_owner(client);
	this->msg.set_id(0);
	this->msg.set_tipo("colour");
}

Message::~Message(){
	this->msg.~msg_game();
}
