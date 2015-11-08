#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

bool SocketUtils::writeMessage(Message* message){
	char* serializedMessage = message->serializeToArray();
	int wroteBytes = write(this->socket, serializedMessage,message->getSize());
	if( wroteBytes < 0) Logger::get()->logError("SocketUtils","writeMessage","Error writing to socket");
	return wroteBytes == message->getSize();
}

Message* SocketUtils::readMessage(){
	int bytesRead = 0;
	int intSize = sizeof(int);
	int bytesToRead = intSize;
	int currentBytesRead = 0;
	stringstream ss;

	//obtenemos la cantidad de bytes a leer
	char* buff = new char[sizeof(int)];
	memset(buff, 0, sizeof(int));
	while( bytesRead < intSize ){
		currentBytesRead = read(this->socket, &buff[bytesRead], bytesToRead);
		if(currentBytesRead!=0){
			bytesRead = currentBytesRead + bytesRead;
			if ( currentBytesRead < 0 ){
				ss << "Error reading message size from socket " << gai_strerror(currentBytesRead);
				Logger::get()->logError("SocketUtils","readMessage",ss.str());
				delete[] buff;
				return NULL;
			}
			bytesToRead = intSize - bytesRead;
		}
	}
	int size = atoi(buff);

	//creamos el buffer para leer el mensaje
	char* buffer = new char[size];
	memset(buffer, 0, size);
	bytesRead = 0;
	bytesToRead = size;
	while ( bytesRead < size ){
		currentBytesRead = read(this->socket, &buffer[bytesRead], bytesToRead);
		bytesRead =  currentBytesRead + bytesRead;
		if ( currentBytesRead < 0 ){
			Logger::get()->logError("SocketUtils","readMessage","Error reading from socket");
			delete[] buffer;
			delete[] buff;
			return NULL;
		}
		bytesToRead = size - bytesRead;
	}

	//TODO manejar los casos de error --> cuando no podemos parsear el mensaje del buffer
	msg_game msg;
	bool validMessage = msg.ParseFromArray(buffer,size);
	if (!validMessage){
		Logger::get()->logError("SocketUtils","readMessage","Message format read from socket is invalid");
		return NULL;
	}
	Message* message = new Message();
	message->setContent(msg);
	delete[] buffer;
	delete[] buff;
	return message;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
