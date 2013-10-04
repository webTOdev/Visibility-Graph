/*
 * VisibilityGraph.h
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPH_H_
#define VISIBILITYGRAPH_H_

#include "obstacles.h"
#include "point.h"
#include <vector>
#include <set>
#include "boostHelper.h"
#include "graphutility.h"

using namespace std;

class VisibilityGraph {
private:
	vector<Obstacle*> obstacleList;
	Point* p;
public:
	VisibilityGraph();
	VisibilityGraph(vector<Obstacle*> obstacleList,Point* p);
	virtual ~VisibilityGraph();
	vector<Line*> visibleVertices(vector<Obstacle*> obstacleList,Point* p);
};

#endif /* VISIBILITYGRAPH_H_ */
