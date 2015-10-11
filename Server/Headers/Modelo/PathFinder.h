/*
 * PathFinder.h
 *
 *  Created on: Oct 2, 2015
 *      Author: juan
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include <list>
#include <iostream>
#include "Mapa.h"
#include "../Modelo/GameSettings.h"

using namespace std;

struct candidato {
  int posX;
  int posY;
  int dist;
  int origenX;
  int origenY;
  bool recorrido;

  bool operator==(const candidato& otro) const{
	  if( (posX == otro.posX) && (posY == otro.posY) && (recorrido == otro.recorrido))
		  return true;
	  else return false;
  }

} ;

class PathFinder {

private:
	int dManhattan(int x,int y);
	void setInicio();
	void setDestino();
	GameSettings* gameSettings;

	candidato inicio;
	candidato destino;
	Mapa* map;
	list<candidato>* candidatos;
	bool candidatoExiste(candidato unCandidato);
	pair<int,int> getClosestAvailable(int x,int y);
	candidato getMinimoNoRecorrido();
	candidato getCandidato(int x,int y);
	bool positionAvailable(int x,int y);
	candidato getAdyacente(int oX,int oY,int x,int y);
	void getCandidatosAdyacentes(candidato actual);
	void getTodosLosAdyacentes(candidato actual);

	int destinoX;
	int destinoY;
	int posX;
	int posY;
public:
	PathFinder(int x,int y,int dX,int dY,Mapa* map);
	list<pair<int,int> >* buscarCamino();
	virtual ~PathFinder();
};

#endif /* PATHFINDER_H_ */
