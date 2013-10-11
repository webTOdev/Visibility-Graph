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
void initializePoints(int row_col,Line *segs[],Point *pointList[]);
void printVisibilityOfPoints(int numOfPoints,Point *pointList[]);
Point* searchPoint(int numOfPoints,Point *pointList[],Point* p );
double distance( Point * a, Point * b );
void createSourceAndDestinationPoint(int index,Point *pointList[],double s_x1,double s_y1,double d_x2,double d_y2);
Point* searchPointByCoord(vector<Point*> pointList,double px,double py);
Point* getPointById(vector<Point*> pointList, int id);

#endif /* POINTHANDLER_H_ */
