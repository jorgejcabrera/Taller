# Taller
Taller de Programacion - 2do cuatrimestre 2015

El objetivo del trabajo práctico es la implementación de un juego de estrategia, similar al [***Age of Empires***](http://www.ageofempires.com/).

##Librerías
Para la interfaz gráfica usamos la librería [**SDL**](https://www.libsdl.org/download-2.0.php)
```	
Ubuntu/Debian/MacOs
descargamos SDL2-2.0.3
./configure
make
sudo make install
```
La configuración de cada mapa correspondiente a la partida se encuentra en un arhcivo [**YAML**](http://yaml.org/). Para el manejo de este tipo de archivos usamos [**libyaml**](http://pyyaml.org/wiki/LibYAML). La librería se puede descargar de [***aquí***](http://pyyaml.org/download/libyaml/). Una vez descompimido:
```
Ubuntu/Debian/MacOs
./configure
make
sudo make install
```
También se van a usar algunas librerías auxiliares de SDL, como [**SDL_image**](https://www.libsdl.org/projects/SDL_image/).
```
Ubuntu/Debian/MacOs
./configure
make
sudo make install
```
Para la serialización de mensajes usamos la librería [**Protocol Buffers**](https://developers.google.com/protocol-buffers/). La versión utilizada es la 2.6.1, y la podemos descargar de [***aquí***](https://developers.google.com/protocol-buffers/docs/downloads). Una vez descargada y descomprimido el .tar:
```
./configure
make
make check
sudo make install
```
La librería funciona de la siguiente manera:
```
1- creamos un archivo con extensión .proto. Por ejemplo Persona.proto :
	*message Persona {
  		required string name = 1;
  		required int32 id = 2;
  		optional string email = 3;
	}*
2- sudo ldconfig
3- corremos el compilador
	*protoc -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/Persona.proto*

	SRC_DIR: raiz en donde se encuentra el archivo que queremos compilar
	DST_DIR: directorio a donde queremos enviar los archivos generados
4- se van a autogenerar dos archivos Persona.pb.h y Persona.pb.cc
```
Para más imformación [**aquí**](https://developers.google.com/protocol-buffers/docs/cpptutorial).
Una vez instaladas todas las librerías las agregamos al IDE
```
Eclipse
	Projects -> Properties -> C/C++ Build -> Settings -> GCC C++ Linker -> Libraries -> add -> SDL2 / SDL2_image / yaml / protobuf
```

##Valgrind
Instalación
```
sudo apt-get install valgrind
```
luego, en eclipse ir a help->install new software... , poner en "Work with" el siguiente link :  
```
http://download.eclipse.org/linuxtools/update
```
enter, seleccionar linux tools (valgrind tools)  next ->finish

##FAQ
Si al correr el programa, aparece el error: "error while loading shared libraries:
libSDL2_image-2.0.so.0: cannot open shared object file: No such file or directory", en eclipse ir a:
```
Eclipse
	Run -> Run Configurations... -> Enviroment -> New Enviroment Variable. 
	Nombre de la variable: LD_LIBRARY_PATH
	Value: /usr/local/lib
```
Puede ocurrir que se nos presente el siguiente mensaje a la hora de usar el compilador de protobuf
```
Error while loading shared libraries: libprotoc.so.9
```
En tal caso ejecutamos 
```
sudo ldconfig 
```
