/*
 * VisibilityGraphController1.h
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPHCONTROLLER_H_
#define VISIBILITYGRAPHCONTROLLER_H_

#include "obstacles.h"
#include "point.h"
#include <vector>
#include <set>
#include "boostHelper.h"
#include "graphutility.h"
#include "VisibilityGraph.h"

using namespace std;

class VisibilityGraphController {
private:
	vector<Obstacle*> obstacleList;
	VisibilityGraph* visGraph;
	Point* p;
public:
	VisibilityGraphController();
	VisibilityGraphController(vector<Obstacle*> obstacleList,Point* p);
	VisibilityGraphController(VisibilityGraph* vg);
	vector<Line*> visibleVertices(Point* ori);
	virtual ~VisibilityGraphController();
	void pointsAndAssociatedEdge(vector<Obstacle*> obsList);
};

#endif /* VISIBILITYGRAPHCONTROLLER_H_ */
