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

Obstacles* o;

template<typename Vertex>
void get_coordinates(Vertex const& p,Obstacles o) {
	double p1=get<0>(p);
	Point* v= new Point(get<0>(p),get<1>(p));
	o.vertices.push_back(v);
	o.setCo(v);
	std::cout << get<0>(p) << " , " << get<1>(p) << std::endl;

}
template<typename Edge>
void get_segments(Edge const& s) {
	o->setEdges(s);
	std::cout << "Segment is "<<dsv(s) << std::endl;
}

void createObstacle(string str){
	 o = new Obstacles(str);
	// And/Or I can use my function with for_each_point()

		bg::for_each_point(boost::geometry::exterior_ring(o->hull),
				get_coordinates<tPoint>);
		bg::for_each_segment(boost::geometry::exterior_ring(o->hull),
				get_segments<segment>);

}



#endif /* OBSTACLEHELPER_H_ */
