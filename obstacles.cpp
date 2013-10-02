/*
 * obstacles.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: nut
 */

#include "obstacles.h"

point start;

void Obstacles::setCo(Point*  p){

	vertices.push_back(p);

}

void Obstacles::setEdges(segment s){
	edges.push_back(s);
}

Obstacles::Obstacles(){

}

Obstacles::Obstacles(string polyStr){

	polyStr="polygon((2.0 1.3, 2.4 1.7, 2.8 1.8, 3.4 1.2, 3.7 1.6, 3.4 2.0, 4.1 3.0, 5.3 2.6, 5.4 1.2, 4.9 0.8, 2.9 0.7, 2.0 1.3))";
	tPolygon poly;
	bg::read_wkt(polyStr,poly);

	bg::convex_hull(poly, hull);
	std::cout << "hull: " << dsv(hull) << std::endl;


}

void Obstacles::print(){

}
double Obstacles::value(){
	double area = bg::area(hull);
	return area;
}
