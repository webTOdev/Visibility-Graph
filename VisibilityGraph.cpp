/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "VisibilityGraph.h"

namespace std {

VisibilityGraph::VisibilityGraph() {
	// TODO Auto-generated constructor stub

}
VisibilityGraph::VisibilityGraph(vector<Obstacle*> obstacleList,Point* p){
	obstacleList=obstacleList;
	p=p;
}

VisibilityGraph::~VisibilityGraph() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
VisibilityGraph::vector<Line*> visibleVertices(vector<Obstacle*> obstacleList,Point* p){
	vector<Line*> visiblePoints;
	return visiblePoints;

}
