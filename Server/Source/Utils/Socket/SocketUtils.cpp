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
	if( wroteBytes < 0) Logger::get()->logError("SocketUtils","writeMessage"," ERROR writing to SocketUtils");
	stringstream ss;
	ss << wroteBytes << "/" << message->getSize() << " write";
	//Logger::get()->logDebug("SocketUtils","writeMessage",ss.str());
	return wroteBytes == message->getSize();
}

//TODO borrar la variable ss es para debuggear y ver los logs
Message* SocketUtils::readMessage(){
	int bytesRead = 0;
	int intSize = sizeof(int);
	int bytesToRead = intSize;
	int currentBytesRead = 0;
	stringstream ss;

	/***obtenemos la cantidad de bytes a leer***/
	char* buff = new char[sizeof(int)];
	memset(buff, 0, sizeof(int));
	while( bytesRead < intSize ){

		currentBytesRead = read(this->socket, &buff[bytesRead], bytesToRead);
		if(currentBytesRead!=0){
			ss << currentBytesRead << " bytes was read";
			Logger::get()->logDebug("SocketUtils","readMessage",ss.str());
			bytesRead = currentBytesRead + bytesRead;
			if ( currentBytesRead < 0 ){
				Logger::get()->logDebug("SocketUtils","readMessage","Error reading message size from socket");
				delete[] buff;
				return NULL;
			}
			bytesToRead = intSize - bytesRead;
		}
	}
	int size = atoi(buff);
	ss.str("");
	ss << "going to read "<< size << " message bytes";
	Logger::get()->logDebug("SocketUtils","readMessage",ss.str());

	/***creamos el buffer para leer el mensaje***/
	char* buffer = new char[size];
	memset(buffer, 0, size);
	bytesRead = 0;
	bytesToRead = size;
	while ( bytesRead < size ){
		currentBytesRead = read(this->socket, &buffer[bytesRead], bytesToRead);
		ss.str("");
		ss << currentBytesRead << " bytes was read";
		Logger::get()->logDebug("SocketUtils","readMessage",ss.str());
		bytesRead =  currentBytesRead + bytesRead;
		if ( currentBytesRead < 0 ){
			Logger::get()->logDebug("SocketUtils","readMessage","Error reading from socket");
			delete[] buffer;
			delete[] buff;
			return NULL;
		}
		bytesToRead = size - bytesRead;
	}

	//TODO manejar los casos de error --> cuando no podemos parsear el mensaje del buffer
	msg_game msg;
	msg.ParseFromArray(buffer,size);
	Message* message = new Message();
	message->setContent(msg);
	ss.str("");
	ss << "message read " << message->toString();
	Logger::get()->logDebug("SocketUtils","readMessage",ss.str());
	delete[] buffer;
	delete[] buff;
	return message;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
