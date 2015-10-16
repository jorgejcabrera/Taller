#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

void SocketUtils::setSocket(int socket){
    this->socket = socket;
}

bool SocketUtils::writeMessage(Message* message){


	//escribimos en el socket el tamaño en bytes del mensaje
	int *size = new int;
	*size =message->getSize();
	char* buff= new char[4];
	memset(&buff, 0, 4);

	buff[0]=message->getSize();
	cout << "MENSAJE: "<<message->toString()<<endl;

	int wroteBytes = write(this->socket,buff, 4);
	if ( wroteBytes < 0){
		cout <<"ERROR writing to SocketUtils, size: " <<*size << " wroteBytes "<<wroteBytes<< " Socket "<< this->socket<< " buff "<<buff<<endl;
		return false;
	}

	char* serializedMessage = message->serializeToArray();
	//escribimos el mensaje
	wroteBytes = write(this->socket, serializedMessage, *size);
	cout << "wroteBytes "<<wroteBytes<<endl;
	if( wroteBytes < 0) cout <<"ERROR writing to SocketUtils, size " <<*size << " mensaje "<<serializedMessage<< endl;
	return wroteBytes < 0;
}

Message* SocketUtils::readMessage(){
	//cout << "socket "<< this->socket<< " LISTO"<< endl;
	msg_game msg;
	Message* message = new Message();
	//obtenemos la cantidad de bytes a leer
	int *size;

	int readBytes = 0;
	while(readBytes==0){
		size = new int;
		readBytes = read(this->socket,size,1);
	}

	if (readBytes < 0 ){
		cout << "Error reading socket "<< readBytes<< " *size "<< *size<< " size "<<size <<endl;
		return NULL;
	}
	char* buffer = new char[*size]();

	//Hasta que no leo el total de bytes no paro.
	size_t bytesReceived = 0;
	while ( bytesReceived < *size){
		int partialReadBytes = read(this->socket, buffer, *size);
		if (partialReadBytes <= 0) break;
		bytesReceived += partialReadBytes;
	}

	//TODO manejar los casos de error --> cuando no podemos parsear el mensaje del buffer

	msg.ParseFromArray(buffer,*size);

	message->setContent(msg);
	delete[] buffer;
	return message;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
