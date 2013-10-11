/*
 * PointHandler.cpp
 *
 *  Created on: Sep 12, 2013
 *      Author: nut
 */

#include "pointHandler.h"

void initializePoints(int index, Line *segs[], Point *pointList[]) {

	for (int i = 0; i < index; i++) {
		segs[i]->print();
		pointList[2 * i] = segs[i]->b;
		pointList[2 * i + 1] = segs[i]->a;

	}

	/*for(int i=0;i<index*2;i++){
	 pointList[i]->print();
	 }*/
}

void createSourceAndDestinationPoint(int index, Point *pointList[], double s_x1,
		double s_y1, double d_x2, double d_y2) {
	Point * source = new Point(s_x1, s_y1);
	Point * destination = new Point(d_x2, d_y2);

	pointList[index - 2] = source;
	pointList[index - 1] = destination;
}
void printVisibilityOfPoints(int numOfPoints, Point *pointList[]) {

	for (int i = 0; i < numOfPoints; i++) {
		pointList[i]->print();
		//pointList[i]->printVisible();
	}
}

Point* searchPoint(int numOfPoints, Point *pointList[], Point* p) {

	for (int i = 0; i < numOfPoints; i++) {
		if ((pointList[i]->x == p->x) && (pointList[i]->y == p->y)) {
			return pointList[i];
		}

	}
	return NULL;
}

Point* searchPointByCoord(vector<Point*> pointList, double px, double py) {

	for (int i = 0; i < pointList.size(); i++) {
		if ((pointList[i]->x == px) && (pointList[i]->y == py)) {
			return pointList[i];
		}

	}
	return NULL;
}

Point * getPointById(vector<Point*> pointList, int id) {
	for (int i = 0; i < pointList.size(); i++) {
		if (pointList[i]->id == id) {
			return pointList[i];
		}

	}
	return NULL;
}
//-------------------------------------------------------------------------------
//  Distance Btw 2 Points
//-------------------------------------------------------------------------------
double distance(Point * a, Point * b) {
	return sqrt(pow(b->x - a->x, 2.0) + pow(b->y - a->y, 2.0));
}

