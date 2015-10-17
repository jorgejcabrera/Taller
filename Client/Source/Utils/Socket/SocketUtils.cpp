#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

void SocketUtils::setSocket(int socket){
    this->socket = socket;
}

bool SocketUtils::writeMessage(Message* message){
	char* serializedMessage = message->serializeToArray();
	int wroteBytes = write(this->socket, serializedMessage,message->getSize());
	if( wroteBytes < 0) cout <<"ERROR writing to SocketUtils" << endl;
	return wroteBytes == message->getSize() - sizeof(int);
}

Message* SocketUtils::readMessage(){
	//obtenemos la cantidad de bytes a leer
	char* buff= new char[sizeof(int)];
	int readBytes = read(this->socket,buff,sizeof(int));
	if (readBytes < 0 ){
		cout << "Error reading socket"<<endl;
		return NULL;
	}
	int size = atoi(buff);
	char* buffer = new char[size]();

	//Hasta que no leo el total de bytes no paro.
	size_t bytesReceived = 0;
	while ( bytesReceived < size){
		//int partialReadBytes = read(this->socket, buffer,size);
		int partialReadBytes = read(this->socket, &buffer[bytesReceived], size - bytesReceived);
		if (partialReadBytes <= 0) break;
		bytesReceived += partialReadBytes;
	}

	//TODO manejar los casos de error --> cuando no podemos parsear el mensaje del buffer
	msg_game msg;
	msg.ParseFromArray(buffer,size);
	Message* message = new Message();
	message->setContent(msg);
	delete[] buffer;
	return message;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
