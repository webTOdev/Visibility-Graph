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

using namespace std;

class VisibilityGraphController {
private:
	vector<Obstacle*> obstacleList;
	Point* p;
public:
	VisibilityGraphController();
	VisibilityGraphController(vector<Obstacle*> obstacleList,Point* p);
	vector<Line*> visibleVertices(vector<Obstacle*> obstacleList,Point* ori);
	virtual ~VisibilityGraphController();
};

#endif /* VISIBILITYGRAPHCONTROLLER_H_ */
