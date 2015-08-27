# Taller
Taller de Programacion - 2do cuatri 2015

El objetivo del trabajo práctico es la implementación de un juego de estrategia, similar al Age of Empires

Para la interfaz gráfica usamos la librería [**SDL**](https://www.libsdl.org/)

Instalación
```	
Ubuntu/Debian
sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
```
Luego necesitamos importar la librería en el IDE
```
Eclipse
Projects -> Properties -> C/C++ Build -> Settings -> GCC C++ Linker -> Libraries -> add -> SDL
```

La configuración de cada mapa correspondiente a la partida se encuentra en un arhcivo [YAML](http://yaml.org/). Para el manejo de este tipo de archivos usamos [**libyaml**](http://pyyaml.org/wiki/LibYAML). La librería se puede descargar de [aquí](http://pyyaml.org/download/libyaml/yaml-0.1.5.tar.gz.). Una vez descompimido:
```
Ubuntu/Debian
./configure
make
sudp make install
```