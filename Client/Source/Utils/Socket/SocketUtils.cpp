#include  "../../../Headers/Utils/Socket/SocketUtils.h"

SocketUtils::SocketUtils(int socket) {
    this->socket = socket;
}

void SocketUtils::setSocket(int socket){
    this->socket = socket;
}

int SocketUtils::writeMessage(Message *msg){
    int wroteBytes = write(this->socket, msg->getSerializeMessage(), msg->getLength());
    if( wroteBytes < 0)
    	cout <<"ERROR writing to SocketUtils" << endl;
    return wroteBytes;
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

int SocketUtils::readMessage(Message *msg)
{
	int size = msg->getLength();
	char * buffer = new char[size+1]();
	//Hasta que no leo el total de bytes no paro.
	size_t bytesReceived = 0;
	while (bytesReceived < size){
		int partialReadBytes = read(this->socket, buffer + bytesReceived, size - bytesReceived);
		if (partialReadBytes <= 0) break;
		bytesReceived += partialReadBytes;
	}
	// modifico el mensaje con recibido en el buffer
	//cout<<"SocketUtils Respuesta recibida: "<<buffer<<endl;
	msg->setBody(buffer);
	delete[] buffer;
	return bytesReceived;
}

int SocketUtils::getSocket(){
	return this->socket;
}

SocketUtils::~SocketUtils() {
}
