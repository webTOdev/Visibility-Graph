/*
 * VisibilityGraph.h
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPH_H_
#define VISIBILITYGRAPH_H_

#include "obstacles.h"
#include "point.h".h"
#include <vector>
namespace std {

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

} /* namespace std */
#endif /* VISIBILITYGRAPH_H_ */
