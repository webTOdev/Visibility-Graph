/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#include "VisibilityGraph.h"

VisibilityGraph::VisibilityGraph() {
	// TODO Auto-generated constructor stub

}

VisibilityGraph::VisibilityGraph(vector<Obstacle*> o){
	obstacles=o;
	for(int i=0;i<o.size();i++){
		vector<Line*> es=o[i]->getEdges();
		obsSides.insert(obsSides.end(),es.begin(),es.end());
		vector<Point*> ps = o[i]->getVertices();
		nodes.insert(nodes.end(),ps.begin(),ps.end());

	}
}

void VisibilityGraph::print(){
		std::cout<<"Total # of Obstacles :"<<obstacles.size()<<std::endl;
		std::cout<<"Total # of Obstacle Edges :"<<obsSides.size()<<std::endl;
		std::cout<<"Total # of Edges :"<<edges.size()<<std::endl;
		std::cout<<"Total # of Nodes :"<<nodes.size()<<std::endl;
		std::cout<<"Obstacles :"<<std::endl;
		/*for(int i=0;i<obstacles.size();i++){
			obstacles[i]->print();
		}*/
		std::cout<<"Edges :"<<std::endl;
		for(int j=0;j<edges.size();j++){
			edges[j]->print();
		}
		std::cout<<"Obstacle Sides :"<<std::endl;
		for(int j=0;j<obsSides.size();j++){
			obsSides[j]->print();
		}

		std::cout<<"Vertexes :"<<std::endl;
		for(int j=0;j<nodes.size();j++){
			nodes[j]->print();
		}
}

VisibilityGraph::~VisibilityGraph() {
	// TODO Auto-generated destructor stub
}

