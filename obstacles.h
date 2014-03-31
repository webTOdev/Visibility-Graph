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
#include "line.h"

using namespace std;

class Obstacle : public Geometry
{
 public:
	vector<Line*> edges;
	vector<Point*> vertices;
	tPolygon poly;
	int id;
	string polyString; //Use this string to get the obstacle

	Obstacle();
	Obstacle(string polyStr);

	void setCo(Point* v);
	void setEdges(Line* line);
	vector<Line*> getEdges();
	vector<Point*> getVertices();
	Point* searchPoint(double x1,double y1);

	virtual void print();
	virtual double value();
};





#endif /* OBSTACLES_H_ */
