/*
 * VisibilityGraph.cpp
 *
 *  Created on: Oct 4, 2013
 *      Author: nut
 */

#include "VisibilityGraph.h"
int MAX=1000;
bool lineHasPoint(tPoint p,tLinestring l);
VisibilityGraph::VisibilityGraph() {
	// TODO Auto-generated constructor stub

}

VisibilityGraph::VisibilityGraph(vector<Obstacle*> o){
	obstacles=o;
	for(int i=0;i<MAX;i++){
		pointVSEdge[i][0]=-1;
		pointVSEdge[i][1]=-1;
	}
	for(int i=0;i<o.size();i++){
		vector<Line*> es=o[i]->getEdges();
		obsSides.insert(obsSides.end(),es.begin(),es.end());
		vector<Point*> ps = o[i]->getVertices();
		nodes.insert(nodes.end(),ps.begin(),ps.end());

		for(int j=0;j<es.size();j++){
			Line* l=es[j];
			if(pointVSEdge[l->a->id][0]==-1){
				pointVSEdge[l->a->id][0]=l->b->id;
			}
			else
				pointVSEdge[l->a->id][1]=l->b->id;
			if(pointVSEdge[l->b->id][0]==-1){
				pointVSEdge[l->b->id][0]=l->a->id;
			}
			else
				pointVSEdge[l->b->id][1]=l->a->id;
		}


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

int* VisibilityGraph::getEdgesOfThisPoint(Point* p){
/*	for(int i=0;i<obstacles.size();i++){
		tPolygon polygn=obstacles[i]->poly;
		bool b = boost::geometry::overlaps(polygn, p->p);
		if(b){
			vector<Line*> ls=obstacles[i]->getEdges();
			for(int j=0;j<ls.size();j++){
				tLinestring tLine=ls[j]->line;
				lineHasPoint( p->p,tLine);
			}
		}
	}*/
	int* otherEnds=pointVSEdge[p->id];
	return otherEnds;

}

bool lineHasPoint(tPoint p,tLinestring l){
	bool has=false;
	 BOOST_FOREACH(tPoint const& pt, l){
		 if(get<0>(p)==get<0>(pt) && get<1>(p)==get<1>(pt)){
		 		has=true;
		 		continue;
		 }
	 }

	return has;

}

VisibilityGraph::~VisibilityGraph() {
	// TODO Auto-generated destructor stub
}

