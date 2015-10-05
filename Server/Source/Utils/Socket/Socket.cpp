#include "../../../Headers/Utils/Socket/Socket.h"

Socket::Socket(int socketId) {
    this->socket = socketId;
}

int Socket::writeMessage(Message *msg){
    int wroteBytes = write(this->socket, msg->getBodyToWrite(), msg->getBodySize());
    if( wroteBytes < 0)
    	cout<<"ERROR writing to socket"<<endl;
    return wroteBytes;
}

int Socket::recvMsgSize(size_t size_length){
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

int Socket::recvMsg(string & msg, size_t length){
    char * c_msg = new char[length + 1]();

    int r = recv(socket, c_msg, sizeof(char) * length,  MSG_WAITALL);
    // recv can return less than the desired data!
    if (r < (int) (sizeof(char) * length)) {
    	return -1;
    }
    msg.clear();
    msg.append(c_msg, length);
    delete[] c_msg;
    return r;
}

int Socket::readMessage(Message *msg)
{
	int size = msg->getBodySize();
	char * buffer = new char[size+1]();
	//Hasta que no leo el total de bytes no paro.
	size_t bytesReceived = 0;
	while (bytesReceived < size){
		int partialReadBytes = read(this->socket, buffer + bytesReceived, size - bytesReceived);
		if (partialReadBytes <= 0) break;
		bytesReceived += partialReadBytes;
	}
	// modifico el mensaje con recibido en el buffer
	//cout<<"Socket Respuesta recibida: "<<buffer<<endl;
	msg->setBody(buffer);
	delete[] buffer;
	return bytesReceived;
}

int Socket::getSocket(){
	return socket;
}

Socket::~Socket() {
}
