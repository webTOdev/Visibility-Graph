/*
 * obstacles.h
 *
 *  Created on: Oct 1, 2013
 *      Author: nut
 */

#ifndef OBSTACLES_H_
#define OBSTACLES_H_

#include "boostHelper.h"
#include "iostream"
#include "vector"
#include "geometry.h"
#include "string"
#include "point.h"

using namespace std;

class Obstacles : public Geometry
{
 public:
	vector<segment> edges;
	vector<Point*> vertices;
	tPolygon hull;
	int id;

	Obstacles();
	Obstacles(string polyStr);

	void setCo(Point* v);
	void setEdges(segment s);

	virtual void print();
	virtual double value();
};





#endif /* OBSTACLES_H_ */
