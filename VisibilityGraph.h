/*
 * VisibilityGraph.h
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPH_H_
#define VISIBILITYGRAPH_H_

#include "obstacles.h"
#include "point.h"
#include <vector>
#include "boostHelper.h"
#include "line.h"

class VisibilityGraph: public Geometry{

public:
	vector<Point*> nodes;
	vector<Line*> obsSides;
	vector<Line*> edges;
	vector<Obstacle*> obstacles;
	int pointVSPoints[1000][2];
	int pointVSEdges[1000][2];

	VisibilityGraph();
	VisibilityGraph(vector<Obstacle*> o);
	virtual ~VisibilityGraph();
	virtual void print();
	virtual double value();
	int* getOtherEndOfThisPoint(Point* p);
	int* getEdgesOfThisPoint(Point* p);
	Obstacle* addObstacle(Obstacle* o);
	void removeEdgeFromVisGraph(Line* l);
	bool edgeExists(Line* l);
	void insertEdgeInVisGraph(vector<Line*> lines);
	Line* findEdgeWithPoints(Point* a,Point* b);
	Obstacle* searchObsWithString(string polyStr){
		for(int i=0;i<obstacles.size();i++){
			if(obstacles[i]->polyString == polyStr){
				return obstacles[i];
			}
		}
	}

	vector<Line*> findEdgesWithThisPoint(Point* a);
	//Incremental Vis Graph
	void removeObstacleFromVisGraph(Obstacle* obs);
	void removeNodeFromVisGraph(Point* a);
	void removeObsSideFromVisGraph(Line* l);


	const vector<Line*>& getEdges() const {
		return edges;
	}

	void setEdges(const vector<Line*>& edges) {
		this->edges = edges;
	}
};

#endif /* VISIBILITYGRAPH_H_ */
