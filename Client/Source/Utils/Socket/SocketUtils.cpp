#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

void SocketUtils::setSocket(int socket){
    this->socket = socket;
}

bool SocketUtils::writeMessage(char* message,int size){
	//escribimos en el scoket la cantidad de bytes del mensaje
	int wroteBytes = write(this->socket,(int*)size, 4);
	if ( wroteBytes < 0){
		cout <<"ERROR writing to SocketUtils" << endl;
		return false;
	}

	//escribimos el mensaje
	wroteBytes = write(this->socket, message, size);
	if( wroteBytes < 0) cout <<"ERROR writing to SocketUtils" << endl;
	return wroteBytes < 0;
}

Message* SocketUtils::readMessage(){

	//obtenemos la cantidad de bytes a leer
	int* size = new int;
	int readBytes = read(this->socket, size,4);
	if (readBytes < 0 ){
		cout << "Error reading socket"<<endl;
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
	msg_game msg;
	msg.ParseFromArray(buffer,*size);
	Message* message = new Message();
	message->setContent(msg);
	delete[] buffer;
	return message;
}


int SocketUtils::recvMsgSize(size_t size_length){
	string size;
	if (recvMsg(size, size_length) <= 0) return -1;

	uint32_t nro;
	char * ptr_nro = (char *)&nro;
	const char * size_content = size.c_str();
	//1 on 1 byte-copy
	for (unsigned i = 0; i < size_length; i++){
		ptr_nro[i] = size_content[i];
	}
	//Big endian to my pcs byte-ordering
	return ntohl(nro);
}

int SocketUtils::recvMsg(string & msg, size_t length){
    char * c_msg = new char[length + 1]();

    int r = recv(this->socket, c_msg, sizeof(char) * length,  MSG_WAITALL);
    // recv can return less than the desired data!
    if (r < (int) (sizeof(char) * length)) {
    	return -1;
    }
    msg.clear();
    msg.append(c_msg, length);
    delete[] c_msg;
    return r;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
