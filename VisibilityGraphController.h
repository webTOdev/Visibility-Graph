/*
 * VisibilityGraphController1.h
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPHCONTROLLER_H_
#define VISIBILITYGRAPHCONTROLLER_H_

#include "obstacles.h"
#include "point.h"
#include <vector>
#include <deque>
#include "boostHelper.h"
#include "graphutility.h"
#include "VisibilityGraph.h"
#include <iterator>
#include <iostream>

using namespace std;
//Using multi_index_container to store <angle,Point*>
struct key_tag {};
struct value_tag {};

typedef std::pair< double, Point* > double_point;
typedef boost::multi_index_container<
    double_point,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< double_point, double, &double_point::first > >,
      boost::multi_index::ordered_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< double_point, Point*, &double_point::second > >
> >  angleContainer;

typedef angleContainer::index<key_tag>::type  key_index_t;
typedef angleContainer::index<value_tag>::type value_index_t;

//Using multi_index_container to store <intersectedDistance,Point*>
typedef std::pair< double, Line* > double_line;
typedef boost::multi_index_container<
		double_line,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< double_line, double, &double_line::first > >,
      boost::multi_index::ordered_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< double_line, Line*, &double_line::second > >
> >  edgeContainer;

typedef edgeContainer::index<key_tag>::type  key_index_edge;
typedef edgeContainer::index<value_tag>::type value_index_edge;


class VisibilityGraphController {
private:
	vector<Obstacle*> obstacleList;
	VisibilityGraph* visGraph;
	Point* p;
public:
	VisibilityGraphController();
	VisibilityGraphController(vector<Obstacle*> obstacleList,Point* p);
	VisibilityGraphController(VisibilityGraph* vg);
	vector<Line*> visibleVertices(Point* ori);
	virtual ~VisibilityGraphController();
	bool isVisible(Point* w_i,Point* ori,Line* sweepLine,Point* w_i_1,int i,edgeContainer edges);
	vector<Line*> generateVisibleEdge(angleContainer angles,vector<Obstacle*> obstacleList,Point* ori,edgeContainer edges,VisibilityGraph* vg);
	edgeContainer updateEdgeList(edgeContainer edges,int* otherEnds,int* es,Point* ori,Point* w_i);
	vector<Line*> constructVisGraph();
	bool findEdgeAndObsIntersects(Line* line,Obstacle* o);
	vector<Obstacle*> getObstacles(){
		return obstacleList;
	}
	VisibilityGraph* getVisGraph(){
		return visGraph;
	}
	void setVisGraph(VisibilityGraph* vGraph){
			visGraph = vGraph;
			obstacleList=vGraph->obstacles;
		}
	VisibilityGraph* addNewObstacleForIncrementalVisGraph(VisibilityGraph* vg,Obstacle* obs);
	VisibilityGraph* removeDataPointFromVisGraph(VisibilityGraph* vGraph, Obstacle* obs);
};

#endif /* VISIBILITYGRAPHCONTROLLER_H_ */
