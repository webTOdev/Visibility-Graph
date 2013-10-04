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
	int pointVSEdge[1000][2];

	VisibilityGraph();
	VisibilityGraph(vector<Obstacle*> o);
	virtual ~VisibilityGraph();
	void print();
	int* getEdgesOfThisPoint(Point* p);

};

#endif /* VISIBILITYGRAPH_H_ */
