/*
 * obstacles.cpp
 *
 *  Created on: Oct 1, 2013
 *      Author: nut
 */

#include "obstacles.h"

tPoint start;

void Obstacle::setCo(Point*  p){

	vertices.push_back(p);

}


void Obstacle::setEdges(Line* line){

	edges.push_back(line);

}

Point* Obstacle::searchPoint(double x1,double y1){
	for(int i=0;i<vertices.size();i++){
		if(vertices[i]->x==x1 && vertices[i]->y==y1)
			return vertices[i];
	}
	return NULL;
}

vector<Line*> Obstacle::getEdges(){
	return edges;

}

vector<Point*> Obstacle::getVertices(){
	return vertices;
}

Obstacle::Obstacle(){

}

Obstacle::Obstacle(string polyStr){
	polyString=polyStr;
	bg::read_wkt(polyStr,poly);
	bg::correct(poly);
	//bg::convex_hull(poly, hull);
	//std::cout << "hull: " << dsv(hull) << std::endl;
	// Change ID
	static int id_counter = 0;
	id = id_counter++;



}

void Obstacle::print(){
	//std::cout << "Obstacle Polygon: " << dsv(poly) << "  ID: "<< id <<" polyString: "<<polyString<< std::endl;
	std::cout << "Obstacle Polygon: " << polyString<< "  ID: "<< id << std::endl;

}
double Obstacle::value(){
	double area = bg::area(poly);
	return area;
}
