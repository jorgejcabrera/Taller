#include "../../../Headers/Utils/Socket/Socket.h"

Socket::Socket(int sockfd) {
    this->socket = sockfd;
}

int Socket::socketSend(const char * buf, size_t length){
    int bytes_enviados = 0;

    //MSG_NOSIGNAL is important to avoid sign pipe and continue execution
    bytes_enviados = send(socket, buf, length, MSG_NOSIGNAL);

    return bytes_enviados;
}

int Socket::recvMsgSize(size_t size_length){
	std::string size;
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

int Socket::recvMsg(std::string & msg, size_t length){
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

int Socket::getSocket(){
	return socket;
}

Socket::~Socket() {
}
