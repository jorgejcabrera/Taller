#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

void SocketUtils::setSocket(int socket){
    this->socket = socket;
}

bool SocketUtils::writeMessage(Message* message){


	//escribimos en el socket el tamaño en bytes del mensaje
	int* size = new int;
	*size = message->getSize();
	int wroteBytes = write(this->socket,size, 4);
	if ( wroteBytes < 0){
		cout <<"ERROR writing to SocketUtils" << endl;
		return false;
	}

	char* serializedMessage = message->serializeToArray();
	//escribimos el mensaje
	wroteBytes = write(this->socket, serializedMessage, *size);
	if( wroteBytes < 0) cout <<"ERROR writing to SocketUtils" << endl;
	return wroteBytes < 0;
}

Message* SocketUtils::readMessage(){
	cout << "socket "<< this->socket<< " LISTO"<< endl;

	//obtenemos la cantidad de bytes a leer
	int *size = new int;
	int readBytes = read(this->socket,size,1);
	if (readBytes < 0 ){
		cout << "Error reading socket "<< readBytes<< " size "<< *size<<endl;
		return NULL;
	}
	cout << "PASE "<< endl;
	char* buffer = new char[*size]();

	//Hasta que no leo el total de bytes no paro.
	size_t bytesReceived = 0;
	while ( bytesReceived < *size){
		int partialReadBytes = read(this->socket, buffer, *size);
		if (partialReadBytes <= 0) break;
		bytesReceived += partialReadBytes;
	}

	//TODO manejar los casos de error --> cuando no podemos parsear el mensaje del buffer
	msg_game msg;
	msg.ParseFromArray(buffer,*size);
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
