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

class VisibilityGraph {

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
	void print();
	int* getOtherEndOfThisPoint(Point* p);
	int* getEdgesOfThisPoint(Point* p);

};

#endif /* VISIBILITYGRAPH_H_ */
