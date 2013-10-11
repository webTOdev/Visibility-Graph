/*
 * PointHandler.h
 *
 *  Created on: Sep 12, 2013
 *      Author: nut
 */

#ifndef POINTHANDLER_H_
#define POINTHANDLER_H_
#include <iostream>
#include <vector>
#include "point.h"
#include <cmath>
#include <list>
#include "line.h"

using namespace std;

double distance( Point * a, Point * b );
Point* searchPointByCoord(vector<Point*> pointList,double px,double py);
Point* getPointById(vector<Point*> pointList, int id);

#endif /* POINTHANDLER_H_ */
