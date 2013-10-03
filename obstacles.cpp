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

Obstacle::Obstacle(){

}

Obstacle::Obstacle(string polyStr){

	//polyStr="polygon((2.0 1.3, 2.4 1.7, 2.8 1.8, 3.4 1.2, 3.7 1.6, 3.4 2.0, 4.1 3.0, 5.3 2.6, 5.4 1.2, 4.9 0.8, 2.9 0.7, 2.0 1.3))";
	//polyStr="polygon((40 40,40 200,100 180,120 100,100 40,40 40))";
	tPolygon poly;
	bg::read_wkt(polyStr,poly);

	bg::convex_hull(poly, hull);
	//std::cout << "hull: " << dsv(hull) << std::endl;
	// Change ID
	static int id_counter = 0;
	id = id_counter++;



}

void Obstacle::print(){
	std::cout<<"Obstacle id :"<<id<<std::endl;
	std::cout<<"Vertexes :"<<std::endl;
	for(int i=0;i<vertices.size();i++){
		vertices[i]->print();
	}
	std::cout<<"Edges :"<<std::endl;
	for(int i=0;i<edges.size();i++){
			edges[i]->print();
		}

}
double Obstacle::value(){
	double area = bg::area(hull);
	return area;
}
