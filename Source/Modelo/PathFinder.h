/*
 * PathFinder.h
 *
 *  Created on: Oct 2, 2015
 *      Author: juan
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_


struct candidato {
  int posX;
  int posY;
  int dist;
  int origenX;
  int origenY;
  bool recorrido;

} ;

class PathFinder {

private:
	int dManhattan(int x,int y);
	int destinoX;
	int destinoY;
public:
	PathFinder(int x,int y);
	candidato getAdyacente(int oX,int oY,int x,int y);
	virtual ~PathFinder();
};

#endif /* PATHFINDER_H_ */
