/*
 * graph.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#include "include/graph.h"

#include "include/debug.h"

#include "assert.h"
#include <limits>

#include <iostream>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;
using namespace graph;


GraphElement::GraphElement() : weight(0), time(0)
{

}


GraphElement::GraphElement(int iweight, int itime) : weight(iweight), time(itime)
{
}


Node::Node(std::string icontent, int iweight, int itime)
{
	content = icontent;
	weight = iweight;
	time = itime;
}


Edge::Edge(Node inodeFrom, Node inodeTo, int iweight, int itime)
{
	nodeFrom = inodeFrom;
	nodeTo = inodeTo;
	weight = iweight;
	time = itime;
}

bool Edge::compareNodes(const Edge &iedge) {
	return this->nodeFrom.getContent() == iedge.nodeFrom.getContent() &&
			this->nodeTo.getContent() == iedge.nodeTo.getContent();
}

Edge Edge::createFromNodes(Node inode) {
	Edge retval(inode, Node());
	for (int i=0; i<inode.getPosSize(); i++) {
		retval.addPos(inode.getPos(i), inode.getPos(i));
	}
	return retval;
}

Graph::Graph()
{

}

Graph::~Graph()
{

}

void Graph::addEdge(Edge iedge)
{
	auto it = std::find_if(this->edges.begin(), this->edges.end(), [iedge](Edge &x){ return x.compareNodes(iedge); });
	if (it == this->edges.end())
	{
		this->edges.push_back(iedge);
	}
	else
	{
		it->increaseWeight();
	}
}

void Graph::addEdge(Node inodeFrom, Node inodeTo)
{
	Edge edge(inodeFrom, inodeTo);

	addEdge(edge);
}

int Graph::getEdgeWeight(Edge &iedge)
{
	int value = 0;
	auto it = std::find_if(edges.begin(), edges.end(), [iedge](Edge &x){ return x.compareNodes(iedge); });

	if (it != edges.end())
	{
		value = it->getWeight();
	}
	return value;
}

//int Graph::getEdgeWeight(const std::string &inodeFrom, const std::string &inodeTo)
//{
//	Edge edge(inodeFrom, inodeTo);
//
//	return getEdgeWeight(edge);
//}

bool Graph::isGraphStructureSame(Graph *igraph) {
//	for (auto thisEdge : edges) {
//		bool foundEdge = false;
//		for (auto iEdge : igraph.edges) {
//			if (thisEdge.getNodeFrom().getContent() == iEdge.getNodeFrom().getContent() &&
//					thisEdge.getNodeTo().getContent() == iEdge.getNodeTo().getContent()) {
//				foundEdge = true;
//			}
//		}
//		if (!foundEdge) {
//			return false;
//		}
//	}
	return to_string().compare(igraph->to_string()) == 0;
}

void Graph::printGraph()
{
	cout << drawGraph();
}

void drawGraph_firstLine(stringstream &out, const vector<Node> &nodes) {
    out << "+->(" << nodes[0].getContent() << ")";
    for (size_t i=1; i<((nodes.size()+1)/2); i++) {
        out << "-->("<< nodes[i].getContent() <<")";
    }
    out << "--+" << endl;
}

void drawGraph_middleLine(stringstream &out, const vector<Node> &nodes) {
    out << "|";
    for (size_t i=0; i<(nodes.size()+1)/2; i++) {
        out << "       ";
    }
    out << " |" << endl;
}

void drawGraph_lastLine(stringstream &out, const vector<Node> &nodes) {

	if (nodes.size() == 1) {
    	out << "+--------+" << endl;
		return;
	}

    out << "+--(" << nodes[nodes.size()-1].getContent() << ")";
    if (nodes.size() > 3) {
        for (size_t i=nodes.size()-2; (i>=((nodes.size()+1)/2)); i--) {
            out << "<--("<< nodes[i].getContent() <<")";
        }
    }
    if (nodes.size() % 2 == 1) {
    	out << "<--------+" << endl;
    }
    else {
		out << "<-+" << endl;
    }
}


vector<Node> retrieveNodes(std::vector<Edge> edges) {
	vector<Node> retval;


	for (size_t i=0; i<edges.size(); i++) {
		retval.push_back(edges[i].getNodeFrom());
	}

	return retval;
}


/*
 * +->(AQ)--+
 * |        |
 * +--(QA)<-+

 * +->(AQ)-->(QQ)--+
 * |               |
 * +--(AA)<--(QA)<-+
 */
string Graph::drawGraph()
{
    stringstream out;

    vector<Node> nodes = retrieveNodes(edges);

    drawGraph_firstLine(out, nodes);
    drawGraph_middleLine(out, nodes);
    drawGraph_lastLine(out, nodes);

    return out.str();
}

std::string Graph::getAminoacids()
{
	std::string retval;

	for (auto item : edges)
	{
		for (auto aa : item.getNodeFrom().getContent()) {
			if (retval.find(aa) == std::string::npos) {
				retval += aa;
			}
		}
		for (auto aa : item.getNodeTo().getContent()) {
			if (retval.find(aa) == std::string::npos) {
				retval += aa;
			}
		}
	}

	return retval;
}

bool compareEdges(Edge iedgeLeft, Edge iedgeRight)
{
	if (iedgeLeft.getNodeFrom().getContent().compare(iedgeRight.getNodeFrom().getContent()) == 0)
	{
		return iedgeLeft.getNodeTo().getContent().compare(iedgeRight.getNodeTo().getContent()) < 0;
	}
	return iedgeLeft.getNodeFrom().getContent().compare(iedgeRight.getNodeFrom().getContent()) < 0;
}

std::string Graph::to_string() {
	std::string retval;

	sort(edges.begin(), edges.end(), compareEdges);

	for (auto item : edges)
	{
		if (retval.empty()) {
			retval += item.getNodeFrom().getContent();
		}
		else {
			retval += "_";
			retval += item.getNodeFrom().getContent();
		}
		retval += "-";
		retval += item.getNodeTo().getContent();
	}

	return retval;
}

int Graph::getBeginPosition() {
	int retval = std::numeric_limits<int>::max();
	assert(edges.size() > 0);
	if (edges.size() == 0) {
		return retval;
	}

	for (auto e : edges) {
		if (e.getBegin() < retval) {
			retval = e.getBegin();
		}
	}

	return retval;
}

int Graph::getEndPosition() {
	int retval = -1;
	assert(edges.size() > 0);
	if (edges.size() == 0) {
		return retval;
	}

	for (auto e : edges) {
		if (e.getEnd() > retval) {
			retval = e.getEnd();
		}
	}

	return retval;
}

int Graph::getNodeCount() {
	int retval = 0;
	assert(edges.size() > 0);
	if (edges.size() == 0) {
		return retval;
	}

	std::set<std::string> nodeSet;
	for (auto e : edges) {
		nodeSet.insert(e.getNodeFrom().getContent());
		nodeSet.insert(e.getNodeTo().getContent());
	}

	return nodeSet.size();
}


std::string Cycle::to_string() {
	return graph.to_string();
}

void Cycle::setGraph(Graph igraph) {
	graph = igraph;
//	begin = graph.getBeginPosition();
//	end = graph.getEndPosition();
}

