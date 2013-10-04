/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 3, 2013
 *      Author: nut
 */

#include "VisibilityGraph.h"
#include <map>

//Using multi_index_container to store sorted points
struct key_tag {};
struct value_tag {};

typedef std::pair< double, Point* > element_t;

typedef boost::multi_index_container<
    element_t,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< element_t, double, &element_t::first > >,
      boost::multi_index::ordered_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< element_t, Point*, &element_t::second > >
> >  anglesContainer;

typedef anglesContainer::index<key_tag>::type  key_index_t;
typedef anglesContainer::index<value_tag>::type value_index_t;

tLinestring createHorizontalLine(Point* p);
VisibilityGraph::VisibilityGraph() {
	// TODO Auto-generated constructor stub

}
VisibilityGraph::VisibilityGraph(vector<Obstacle*> obstacleList,Point* p){
	obstacleList=obstacleList;
	p=p;
}

VisibilityGraph::~VisibilityGraph() {
	// TODO Auto-generated destructor stub
}

vector<Line*> VisibilityGraph::visibleVertices(vector<Obstacle*> obstacleList,Point* ori){
	vector<Line*> visiblePoints;
	tLinestring centerLine = createHorizontalLine(ori); //SweepLine initialize to horizontal
	point pt=ori->p; //The point around which the SweepLine rotates
	anglesContainer angles;

	//Iterate over each of the obstacles and sort all the points
	for(int m=0;m<obstacleList.size();m++){
		Obstacle* o=obstacleList[m];
		vector<Point*> points = o->getVertices();
		for(int i=0;i<points.size();i++){
			// Calculate the angle from center line:
			double angle =vectorsAngle(ori->x,ori->y,points[i]->x,points[i]->y);
			points[i]->theta=angle;
			angles.insert( element_t( angle, points[i] ) );
		}
	}
	//Took help from  multi index facility of boost
	     std::cout << "Angle List :" << std::endl;
	     key_index_t& kindex = angles.get<key_tag>();
	     for( key_index_t::iterator k = kindex.begin(); k != kindex.end(); ++k )
	        std::cout << k->first << " ==> " << k->second->id << std::endl;

	return visiblePoints;

}

tLinestring createHorizontalLine(Point* p){

	 bg::model::linestring<tPoint> line;
	 const double c[][2] = { {p->x, p->y}, {(p->x)+1000, p->y}};
	  bg::assign_points(line, c);
	  return line;
}


