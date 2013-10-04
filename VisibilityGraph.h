/*
 * VisibilityGraph.h
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#ifndef VISIBILITYGRAPH_H_
#define VISIBILITYGRAPH_H_

#include "obstacles.h"
#include "point.h"
#include <vector>
#include "boostHelper.h"
#include "line.h"

struct key_tag {};
struct value_tag {};
//Using multi_index_container to store <Point,Associated Edges*>
typedef std::pair< int, Line* > vertex_edge;
typedef boost::multi_index_container<
		vertex_edge,
    boost::multi_index::indexed_by<
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< key_tag >,
          boost::multi_index::member< vertex_edge, int, &vertex_edge::first > >,
      boost::multi_index::ordered_non_unique< boost::multi_index::tag< value_tag >,
          boost::multi_index::member< vertex_edge, Line*, &vertex_edge::second > >
> >  vertexWithItsEdge;

typedef vertexWithItsEdge::index<key_tag>::type  key_index_vEdge;
typedef vertexWithItsEdge::index<value_tag>::type value_index_vEdge;

class VisibilityGraph {

private:
	vector<Point*> nodes;
	vector<Line*> obsSides;
	vector<Line*> edges;
	vector<Obstacle*> obstacles;

public:
	vertexWithItsEdge vertexEgde;
	VisibilityGraph();
	VisibilityGraph(vector<Obstacle*> o);
	virtual ~VisibilityGraph();
	void print();

};

#endif /* VISIBILITYGRAPH_H_ */
