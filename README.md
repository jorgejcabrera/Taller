# Taller
Taller de Programacion - 2do cuatri 2015

El objetivo del trabajo práctico es la implementación de un juego de estrategia, similar al Age of Empires

Para la interfaz gráfica usamos la librería [**SDL**](https://www.libsdl.org/download-2.0.php)

Instalación
```	
Ubuntu/Debian/MacOs
descargamos SDL2-2.0.3
./configure
make
sudo make install
```
La configuración de cada mapa correspondiente a la partida se encuentra en un arhcivo [**YAML**](http://yaml.org/). Para el manejo de este tipo de archivos usamos [**libyaml**](http://pyyaml.org/wiki/LibYAML). La librería se puede descargar de [**aquí**](http://pyyaml.org/download/libyaml/). Una vez descompimido:
```
Ubuntu/Debian/MacOs
./configure
make
sudo make install
```

También se van a usar algunas librerías auxiliares de SDL, como [**SDL_image**](https://www.libsdl.org/projects/SDL_image/). Los pasos para la instalación son los mismos que se describieron arriba.

Luego necesitamos importar las librería en el IDE
```
Eclipse
	Projects -> Properties -> C/C++ Build -> Settings -> GCC C++ Linker -> Libraries -> add -> SDL2 / SDL2_image / yaml
```

Para el uso de socket y threads debemos incluir la librería pthread
```
Eclipse
	Projects -> Properties -> C/C++ Build -> Settings -> GCC C++ Linker -> Libraries -> add -> pthread
```


Si al correr el programa, aparece el error: "error while loading shared libraries:
libSDL2_image-2.0.so.0: cannot open shared object file: No such file or directory", en eclipse ir a:
```
Eclipse
	Run -> Run Configurations... -> Enviroment -> New Enviroment Variable. 
	Nombre de la variable: LD_LIBRARY_PATH
	Value: /usr/local/lib
```

Para la utilizacion de valgrind en eclipse, primero ejecutar por consola
```
sudo apt-get install valgrind
```

luego, en eclipse ir a help->install new software... , poner en "Work with" el siguiente link :  
```
http://download.eclipse.org/linuxtools/update
```

enter, seleccionar linux tools (valgrind tools)  next ->finish
