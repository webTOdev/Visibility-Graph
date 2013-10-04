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
#include "VisibilityGraph.h"

void drawObs(Obstacle* obs,Point* ori);
int main() {

	vector<Obstacle*> obsList;
	Obstacle* obs=createObstacle("polygon((40 140,40 300,100 280,120 200,100 140,40 140))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((200 40,280 40,320 200,180 190,200 40))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((30 330,180 350,120 450,30 330))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((400 320,450 320,450 450,480 470,480 320,520 320,500 520,400 530,400 320))");
	obsList.push_back(obs);

	Point* ori=new Point(10,100);
	VisibilityGraph* vg = new VisibilityGraph(obsList,ori);
	vg->visibleVertices(obsList,ori);

	drawLine(10,100,1000,100);
	for(int i=0;i<obsList.size();i++){
		obsList[i]->print();
		drawObs(obsList[i],ori);
	}

	showPolygon();
	return 0;
}

void drawObs(Obstacle* o,Point* ori){

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
		    drawCircle((*it)->x,(*it)->y);
		    drawText((*it)->x,(*it)->y,(*it)->id);
		    //Draw Lines for angle sorting
		    drawLine((*it)->x,(*it)->y,ori->x,ori->y);
		}

		 double *iterator = ps;
		 cimg_forX(points,i) { points(i,0) = *(iterator++); points(i,1) = *(iterator++); }
		 drawPolygon(points);

}

