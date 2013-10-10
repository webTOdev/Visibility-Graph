/*
 * obstacleHelper.h
 *
 *  Created on: Oct 2, 2013
 *      Author: nut
 */

#ifndef OBSTACLEHELPER_H_
#define OBSTACLEHELPER_H_

#include "boostHelper.h"
#include <string>
#include "obstacles.h"

Obstacle* o;

template<typename Vertex>
void get_coordinates(Vertex const& p) {

	Point* v;
	if(o->searchPoint(get<0>(p),get<1>(p))==NULL){
		v= new Point(get<0>(p),get<1>(p));
		o->setCo(v);
	}

}
template<typename Edge>
void get_segments(Edge const& s) {
	double x1=get<0,0>(s);  //get(index,dimension-x/y)
	double y1=get<0,1>(s);
	double x2=get<1,0>(s);
	double y2=get<1,1>(s);
	Point* p1= o->searchPoint(x1,y1);
	Point* p2= o->searchPoint(x2,y2);
	if(p1!=NULL && p2!=NULL){
	Line* line=new Line(p1,p2);
	o->setEdges(line);
	}
}

Obstacle* createObstacle(string str){
	 o = new Obstacle(str);

	/*	bg::for_each_point(boost::geometry::exterior_ring(o->hull),
				get_coordinates<tPoint>);

	 //set Edge
		bg::for_each_segment(boost::geometry::exterior_ring(o->hull),
				get_segments<segment>);
*/
		bg::for_each_point(o->poly,get_coordinates<tPoint>);

		 //set Edge
		bg::for_each_segment(o->poly,get_segments<segment>);



		return o;

}
vector<Point*> getVertices(Obstacle* o){
	return o->vertices;
}





#endif /* OBSTACLEHELPER_H_ */
