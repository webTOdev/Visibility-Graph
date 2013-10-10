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
#include "VisibilityGraphController.h"
#include "VisibilityGraph.h"
#include "graphutility.h"

void drawObs(Obstacle* obs,Point* ori);
void drawVisEdges(vector<Line*> visEdges);
int main() {

	vector<Obstacle*> obsList;
	Obstacle* obs=createObstacle("polygon((40 140,40 300,100 280,120 200,100 140,40 140))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((200 40,280 40,320 200,180 190,200 40))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((30 330,180 350,120 450,30 330))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((400 320,520 320,500 520,400 530,400 320))");
	obsList.push_back(obs);

	//obs=createObstacle("polygon((40 20,40 20))");//For data point
	//obsList.push_back(obs);


	/*Obstacle* obs=createObstacle("polygon((200 20,250 20,250 200,200 200,200 20))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((100 150,150 150,150 50,100 50,100 150))");
	obsList.push_back(obs);
	*/

	VisibilityGraph* visGraph = new VisibilityGraph(obsList);
	visGraph->print();
	//Point* clockwise=true;ori=new Point(540,520);
	//Point* ori=new Point(40,20);
	//Point* ori=new Point(440,20);
	Point* ori=new Point(440,120);
	//Point* ori=new Point(140,60);//Problematic input
	//Point* ori=new Point(140,160);
	//Point* ori=new Point(10,5);
	VisibilityGraphController* vg = new VisibilityGraphController(visGraph);
	vector<Line*> visEdges=vg->constructVisGraph();
	drawVisEdges(visEdges);

	//drawLine(ori->x,ori->y,ori->x+1000,ori->y);
	for(int i=0;i<obsList.size();i++){
		//obsList[i]->print();
		drawObs(obsList[i],ori);

	}

	vector<Line*> obsSide=visGraph->obsSides;
	for(int  i=0;i<obsSide.size();i++){
		Line* l= obsSide[i];
		drawText(((l->a->x)+(l->b->x))/2,  ((l->a->y)+(l->b->y))/2,l->id,WHITE);
		//drawText(l->b->x-8,  l->b->y-15,l->id);
	}

	showPolygon();

	return 0;
}

void drawVisEdges(vector<Line*> visEdges){

	for(int i=0;i<visEdges.size();i++){
		std::cout<<"Visible Edges "<<visEdges[i]->a->id<<"->"<<visEdges[i]->b->id<<std::endl;
		drawEdge(visEdges[i]);
	}
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
		    drawText((*it)->x,(*it)->y,(*it)->id,RED);
		    //Draw Lines for angle sorting
		   // drawLine((*it)->x,(*it)->y,ori->x,ori->y);
		}

		 double *iterator = ps;
		 cimg_forX(points,i) { points(i,0) = *(iterator++); points(i,1) = *(iterator++); }
		 drawPolygon(points);

}

