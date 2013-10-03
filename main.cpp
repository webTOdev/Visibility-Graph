/*
 * main.cpp
 *
 *  Created on: Oct 2, 2013
 *      Author: nut
 */
#include <iostream>
#include "obstacles.h"
#include "boostHelper.h"
#include "obstacleController.h"
#include "drawing.h"
#include "utility.h"
#include <vector>

void drawObs(Obstacle* obs);
int main() {

	vector<Obstacle*> obsList;
	Obstacle* obs=createObstacle("polygon((40 140,40 300,100 280,120 200,100 140,40 140))");
	obs->print();
	drawObs(obs);
	obsList.push_back(obs);

	obs=createObstacle("polygon((250 40,350 40,400 350,200 350,250 40))");
	obs->print();
	drawObs(obs);
	obsList.push_back(obs);



	showPolygon();
	return 0;
}

void drawObs(Obstacle* o){

	vector<Point*> vertexList=getVertices(o);
	int size= vertexList.size();
		CImg<double> points(size,2);
		double ps[size*2];
		int i=0;
		for(std::vector<Point*>::iterator it = vertexList.begin(); it < vertexList.end(); ++it) {
		    ps[i]=(*it)->x;
		    i++;
		    ps[i]=(*it)->y;
		    i++;
		}

		 double *iterator = ps;
		 cimg_forX(points,i) { points(i,0) = *(iterator++); points(i,1) = *(iterator++); }
		 drawPolygon(points);

}

