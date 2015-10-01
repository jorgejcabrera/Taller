
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main(){
	int clientes, servidor;
	int portNum = 7891;										//acá va el puerto por el que nos vamos a comunicar
	bool salir = false;										//para mantenernos en el ciclo while del chat
	int bufsize = 10;
	char buffer[bufsize];						//son los char que vamos a mandar con las funciones send y recv

	struct sockaddr_in serverAddr;
	memset(&serverAddr,0,sizeof(serverAddr));
	socklen_t tamano;

	//init socket
	if( (clientes = socket(PF_INET, SOCK_STREAM, 0)) < 0 ){	//creamos el socket dominio: AF_INET (Protocolo TCP)
		cout << "Error al crear el socket"<<endl;
		exit(1);
	}
	cout << "Socket servidor ha sido creado..."<< endl;


	serverAddr.sin_family = AF_INET;								//asignamos a la estructura sockaddr_in un dominio, una ip y un puerto
	//serverAddr.sin_addr.s_addr = htons(INADDR_ANY);				//INADDR_ANY es asignarle automaticamente la serverAddrcion local
	serverAddr.sin_port = htons(portNum);						//sin_addr y sin_port deben convertirse a Network byte y para ello usamos htons o htonl

	//binding socket
	if(bind(clientes, (struct sockaddr*)&serverAddr,sizeof(serverAddr)) < 0){	//bind: crea la conexion con el puerto y el socket creado (clientes)
		cout << "Error en la conexion bind..."<<endl;				//clientes: es el socket a conectar, &serverAddr es una estructura donde
		exit(1);													//guardamos la ip local y el puerto, tamano de la estrucrura serverAddr
	}

	tamano = sizeof(serverAddr);
	cout << "Esperando clientes..."<<endl;

	//listing socket
	listen(clientes, 1);									//esta funcion escucha si algun cliente se quiere conectar, y el segundo parametro
															//es el numero de clientes en cola

	while((servidor = accept(clientes,(struct sockaddr*)&serverAddr,&tamano))>0){	//aceptamos la conexion retorna negativo si falla
		strcpy(buffer,"Servidor conectado\n");
		write(servidor,buffer,bufsize);
		cout<<"Conexion con el cliente EXITOSA\n";
		cout<<"Recuerde poner asterisco al final para mandar un mensaje * \n Con # termina la conexcion"<<endl;
		cout<<"Mensaje recibido: ";

		do{
			read(servidor,buffer,bufsize);		//Recibimos el mensaje buffer de tamano bufsize por el socket servidor
			cout<<buffer<<" ";
			if(*buffer == '#'){
				*buffer='*';
				salir = true;
			}
		}while(*buffer != '*');

		do{
			cout<<"\nEscriba un mensaje: ";
			do{
				cin>>buffer;
				write(servidor,buffer,bufsize+1);		//enviamos de servidor un mensaje buffer de tamano buffsize y una bandera flag
				if(*buffer == '#'){
					write(servidor,buffer,bufsize+1);
					*buffer = '*';
					salir = true;
				}
			}while(*buffer != '*');

			cout<<"Mensaje recibido: ";
			do{
				read(servidor,buffer,bufsize);
				cout<<buffer<<" ";
				if(*buffer == '#'){
					*buffer = '*';
					salir = true;
				}
			}while(*buffer != '*');

		}while(!salir);

		cout << "\nEl servidor termino la conexion con "<<inet_ntoa(serverAddr.sin_addr);
		close(servidor);
		cout<<"\nConecte nuevo cliente."<<endl;
		salir = false;
	}

	close(clientes);	//cerramos el socket
	return 0;
}
