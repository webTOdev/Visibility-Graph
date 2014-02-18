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
#include "dijkstra.h"
#include <time.h>

clock_t startTime;
void findShortestPath(VisibilityGraph* vg,double sourceX,double sourceY,double destX,double destY);
void drawObs(Obstacle* obs,Point* ori);
void drawVisEdges(vector<Line*> visEdges);


int mainst(void)
{

	CImg<double> points(6,2);
    // polygons
    std::vector<polygon> polygons;
    linestring_2d ls;
    tPolygon poly;
    std::vector<tPolygon> polys;

    vector<Obstacle*> obsList;
    	Obstacle* obs=createObstacle("polygon((40 140,40 300,100 280,120 200,100 140,40 140))");
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((200 40,280 40,320 200,180 190,200 40))");
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((30 330,180 350,120 450,30 330))");
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((400 320,520 320,500 520,400 530,400 320))");
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((40 20,40 20))");//For data point
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((440 20,440 20))");//For data point
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);

    	obs=createObstacle("polygon((600 600,600 600))");//For data point
    	obsList.push_back(obs);
    	polys.push_back(obs->poly);


    	for(int i=0;i<obsList.size();i++){
    			//obsList[i]->print();
    			drawObs(obsList[i],NULL);

    		}

       // display polygons
    std::cout << "generated polygons:" << std::endl;

    BOOST_FOREACH(tPolygon const& p, polys){
       std::cout << bg::wkt<tPolygon>(p) << std::endl;

    }
    // create the rtree using default constructor
    bgi::rtree< value, bgi::rstar<16, 4> > rtree;

    // fill the spatial index
    for ( unsigned i = 0 ; i < polys.size() ; ++i )
    {
        // calculate polygon bounding box
        box b = bg::return_envelope<box>(polys[i]);
        // insert new value
        rtree.insert(std::make_pair(b, i));
    }

    // find values intersecting some area defined by a box
    box query_box(point(40, 40), point(600, 600));
    std::vector<value> result_s;
    rtree.query(bgi::intersects(query_box), std::back_inserter(result_s));

    // find 5 nearest values to a point
    std::vector<value> result_n;
    rtree.query(bgi::nearest(point(0, 0), 5), std::back_inserter(result_n));

    // display results
    std::cout << "spatial query box:" << std::endl;
    std::cout << bg::wkt<box>(query_box) << std::endl;
    std::cout << "spatial query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_s)
        std::cout << bg::wkt<tPolygon>(polys[v.second]) << std::endl;

    std::cout << "knn query point:" << std::endl;
    std::cout << bg::wkt<point>(point(80, 80)) << std::endl;
    std::cout << "knn query result:" << std::endl;
    BOOST_FOREACH(value const& v, result_n)
        std::cout << bg::wkt<tPolygon>(polys[v.second]) << std::endl;

 //   displayImage();
    return 0;
}


int main() {

	startTime = clock();
	vector<Obstacle*> obsList;
	Obstacle* obs=createObstacle("polygon((40 140,40 300,100 280,120 200,100 140,40 140))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((200 40,280 40,320 200,180 190,200 40))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((30 330,180 350,120 450,30 330))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((400 320,520 320,500 520,400 530,400 320))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((40 20,40 20))");//For data point
	obsList.push_back(obs);

	obs=createObstacle("polygon((440 20,440 20))");//For data point
	obsList.push_back(obs);

	obs=createObstacle("polygon((600 600,600 600))");//For data point
	obsList.push_back(obs);


	/*Obstacle* obs=createObstacle("polygon((200 20,250 20,250 200,200 200,200 20))");
	obsList.push_back(obs);

	obs=createObstacle("polygon((100 150,150 150,150 50,100 50,100 150))");
	obsList.push_back(obs);
	*/

	VisibilityGraph* visGraph = new VisibilityGraph(obsList);
	visGraph->print();
	//Not used now it will be used if we need to draw angular lines
	Point* ori=new Point(440,120);
	VisibilityGraphController* vg = new VisibilityGraphController(visGraph);
	vector<Line*> visEdges=vg->constructVisGraph();
	drawVisEdges(visEdges);

	for(int i=0;i<obsList.size();i++){
		//obsList[i]->print();
		drawObs(obsList[i],ori);

	}

	vector<Line*> obsSide=visGraph->obsSides;
	for(int  i=0;i<obsSide.size();i++){
		Line* l= obsSide[i];
		drawText(((l->a->x)+(l->b->x))/2,  ((l->a->y)+(l->b->y))/2,l->id,WHITE);
		//drawEdge(l,WHITE);
	}


	findShortestPath(visGraph,40,20,600,600);
	/* Code you want timed here */
	printf("Time elapsed: %f s\n", ((double)clock() - startTime) / CLOCKS_PER_SEC);

	//obs=createObstacle("polygon((650 400,720 400,720 550,650 400))");//For Obs
	obs=createObstacle("polygon((250 400,320 400,320 500,250 400))");//For Obs
	Obstacle* o = visGraph->addObstacle(obs);
	vector<Point*> obsVertices = o->getVertices();
    vg->setVisGraph(visGraph);

    std::cout<<"Before erasing intersecting lines with new obstacle "<<visGraph->edges.size()<<std::endl;
    //Remove Intersecting edges of this obstacle
	for(int i=0;i<visGraph->edges.size();i++){
		Line* l = visGraph->edges[i];
		if(vg->findEdgeAndObsIntersects(l,o)){
			drawEdge(l,WHITE);
			visGraph->removeEdgeFromVisGraph(l);
		}
	}

	std::cout<<"After erasing intersecting lines with new obstacle "<<visGraph->edges.size()<<std::endl;

	//Insert new edges from the new obstacle
	for (int i=0;i<obsVertices.size();i++) {
		Point* point = obsVertices[i];
		vector<Line*> temp = vg->visibleVertices(point);
		visGraph->insertEdgeInVisGraph(temp);
		for (int i = 0; i < temp.size(); i++) {
			drawEdge(temp[i], RED);
		}
	}
	//drawCircle(650,700,3,RED);
	drawObs(o,ori);



	std::cout<<"After inserting visible lines with new obstacle "<<visGraph->edges.size()<<std::endl;

	//drawVisEdges(visGraph->edges);
	displayImage();

	return 0;
}



void drawVisEdges(vector<Line*> visEdges){

	for(int i=0;i<visEdges.size();i++){
		drawEdge(visEdges[i],BLUE);
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
		    drawCircle((*it)->x,(*it)->y,1.5,WHITE);
		    drawText((*it)->x,(*it)->y,(*it)->id,RED);
		    //Draw Lines for angle sorting
		   // drawLine((*it)->x,(*it)->y,ori->x,ori->y);
		}

		 double *iterator = ps;
		 cimg_forX(points,i) { points(i,0) = *(iterator++); points(i,1) = *(iterator++); }
		 drawPolygon(points);

}

void findShortestPath(VisibilityGraph* vg, double sourceX, double sourceY,
		double destX, double destY) {
	int numOfPoints = vg->nodes.size();
	int numOfEdges = vg->edges.size();
	int sourcePointId = searchPointByCoord(vg->nodes, sourceX, sourceY)->id;
	int destPointId = searchPointByCoord(vg->nodes, destX, destY)->id;
	printf("\nFinding shortest path from %d -> %d\n", sourcePointId, destPointId,numOfEdges,numOfPoints);
	Point* start;
	Point* goal;
	initiateDijkstra(numOfPoints, numOfEdges, false, sourcePointId,
			destPointId);
	int *shortestPath = getShortestPath();
	int i = 0;
	//Print the Shortest Path
	printf("The Shortest Path is :");
	while (shortestPath[i] != -1) {
		printf("%d ", shortestPath[i]);

		if (shortestPath[i + 1] != -1) {
			start = getPointById(vg->nodes, shortestPath[i]);
			goal = getPointById(vg->nodes, shortestPath[i + 1]);
			// Visualize:
			drawCircle(start->x, start->y, 2, GREEN);
			drawCircle(goal->x, goal->y, 2, GREEN);
			drawLine(start->x, start->y, goal->x, goal->y, GREEN);
		} else {
			goal = getPointById(vg->nodes, destPointId);
			writeText((goal->x - 5), (goal->y + 15), "Dest", GREEN);
		}

		if (i == 0) {
			writeText((start->x - 5), (start->y + 15), "Source", GREEN);
		}

		i++;
	}
}

