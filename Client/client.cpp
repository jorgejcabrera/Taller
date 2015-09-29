/*
 * Server.cpp
 *
 *  Created on: 28 de set. de 2015
 *      Author: jorge
 */

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

//el cliente necesita saber el puerto del servidor
int main(){
	int client, server;
	int portNum = 8080;
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];
	char *ip = "127.0.0.1";

	struct sockaddr_in server_addr;

	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);
	if(client < 0){
		cout << "Error creating socket..."<<endl;
		exit(1);
	}

	cout << "Client Socket created..."<< endl;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);

	//Conectar al servidor
	if(connect(client, (struct sockaddr*)&server_addr,sizeof(server_addr)) == 0 ){
		cout << "Connecting to server..."<< endl;
	}
	recv(client, buffer, bufsize, 0);
	cout << "Connection confirmed"<<endl;
	cout << "Enter # to end the connection"<<endl;

	do{
		cout << "Client: ";
		do{
			cin >> buffer;
			send(client, buffer, bufsize, 0);
			if(*buffer == '#'){
				send(client, buffer, bufsize, 0);
				*buffer = '*';
				isExit = true;
			}
		}while (*buffer != '*');

		cout << "Server: ";
		do{
			recv(client, buffer, bufsize, 0);
			cout << buffer << " ";
			if(*buffer == '#'){
				*buffer = '*';
				isExit = true;
			}
		} while ( *buffer != '*');
	
		cout << endl;
	}while (!isExit);

	cout << "Connection terminated..." << endl;
	cout << "Goodbye" << endl;

	close(client);
	return 0;

}
