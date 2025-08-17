/*
 * graph.h
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_GRAPH_H_
#define GBSC_INCLUDE_GRAPH_H_

#include "include/debug.h"

#include <string>
#include <vector>
#include <map>

namespace graph
{
	class GraphElement
	{
	protected:
        int weight;
        int time;

	public:
        GraphElement();
        GraphElement(int iweight, int itime);

        void setWeight(int iweight) {weight = iweight;}
        void setTime(int itime) {time = itime;}

        int getWeight() {return weight;}
        int getTime() {return time;}

        void increaseWeight() {weight += 1;}
        void increaseTime() {time += 1;}
        bool reachedWeightThreshold(int iweightThreshold) {return weight >= iweightThreshold;}
        bool reachedLifetime(int ilifetime) {return time >= ilifetime;}
	};


	class Node : public GraphElement
	{
	private:
        std::string content;
        std::vector<int> pos;


	protected:
	public:
        Node(std::string icontent, int iscore, int idistance);
        Node(std::string icontent) : Node(icontent, 0, 0) {}
        Node() : Node("", 0, 0) {}

        std::string getContent() const { return content; }
        void addPos(int ipos) {pos.push_back(ipos);}

        int getBegin() {return pos[0];}
        int getEnd() {return *(pos.end()-1) + 1;}
        int getPos(int ipos) { return pos[ipos]; }
        void removePos(int ipos) { pos.erase(pos.begin() + ipos); }
        int getPosSize() { return pos.size(); }
	};

	struct edge_position_t {
		int begin;
		int end;
	};

	class Edge : public GraphElement
	{
	private:
        Node nodeFrom;
        Node nodeTo;
        std::vector<edge_position_t> pos;  // For a single edge, many positions may be assigned since it may occur in many places in a sequence

	protected:
	public:

        Edge(Node inodeFrom, Node inodeTo, int iweight, int itime);
        Edge(Node inodeFrom, Node inodeTo) : Edge(inodeFrom, inodeTo, 0, 0) {}

        Node getNodeFrom() { return nodeFrom; }
        Node getNodeTo() { return nodeTo; }
        void addPos(int begin, int end) {pos.push_back(edge_position_t{begin, end});}
        void addPos(edge_position_t iep) {pos.push_back(iep);}
        std::vector<edge_position_t> getPositions() { return pos; }

        int getBegin() {return pos[0].begin + 1;}
        int getEnd() {return (pos.end()-1)->end + 2;}
        edge_position_t getPos(int ipos) { return pos[ipos]; }
        bool compareNodes(const Edge &edge);

        static Edge createFromNodes(Node inodeFrom);
	};


	class Graph
	{
	private:
		std::vector<Edge> edges;

	protected:
	public:
		Graph();
		virtual ~Graph();

		void addEdge(Edge iedge);
		void addEdge(Node nodeFrom, Node nodeTo);
		int getEdgeWeight(Edge &iedge);
		std::vector<Edge> getEdges() { return edges; }

		bool isGraphStructureSame(Graph *igraph);

		void printGraph();
        std::string drawGraph();
		std::string getAminoacids();

		std::string to_string();

		int getBeginPosition();
		int getEndPosition();
		int getNodeCount();
	};


	class Cycle
	{
	private:
		Graph graph;

	public:
		Cycle() {}
		virtual ~Cycle() {}

		Graph getGraph() { return graph; }
		void setGraph(Graph igraph);

		int getBegin() { return graph.getBeginPosition(); }

		int getEnd() { return graph.getEndPosition(); }
		void addEdge(Edge edge) { graph.addEdge(edge); }

		std::string to_string();

	};
}

#endif /* GBSC_INCLUDE_GRAPH_H_ */
