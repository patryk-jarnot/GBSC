/*
 * postprocess.cpp
 *
 *  Created on: Jan 28, 2022
 *      Author: pjarnot
 */

#include "include/postprocess.h"
#include "include/debug.h"

#include "unistd.h"

#include <set>
#include <limits>
#include <iostream>

using namespace std;
using namespace graph;
using namespace postprocess;


void create_mask(vector<edge_position_t> iedgePositions, vector<int8_t> &ostrsMask) {
	for (edge_position_t ep : iedgePositions) {
		for (int i=ep.begin; i < (ep.end+2); i++) {
			ostrsMask[i]++;
		}
	}
}


void smashCycle(Cycle c, vector<int8_t> strsMask, int imaxGapAllowed, int iscoreThreshold, vector<Cycle> &retval) {
	int regionBegin = -1;
	int gapSize = 0;
	bool splitted = false;
	for (size_t i=1; i<strsMask.size(); i++) {
		if (strsMask[i] == 0) {
			gapSize++;
		}
		else {
			gapSize = 0;
			splitted = false;
			if (regionBegin == -1) {
				regionBegin = i;
			}
		}

		if (gapSize > imaxGapAllowed && !splitted) {
			Cycle newCycle;

			for (Edge e : c.getGraph().getEdges()) {
				Edge newEdge(e.getNodeFrom(), e.getNodeTo());
				for (edge_position_t ep : e.getPositions()) {
					if (ep.begin >= regionBegin-1 && ep.end <= (int)i) {
						newEdge.addPos(ep);
					}
				}
				if (newEdge.getPositions().size() >= (size_t)iscoreThreshold) {
					newCycle.addEdge(newEdge);
				}
			}

			if (newCycle.getGraph().getEdges().size() > 0) {
				retval.push_back(newCycle);
			}

			splitted = true;
			regionBegin = -1;
		}
	}
}


int getEndPositionOfCycle(vector<Edge> &edges) {
	int endPos = 0;
	for (Edge edge : edges) {
		for (edge_position_t ep : edge.getPositions()) {
			if (endPos < ep.end) {
				endPos = ep.end;
			}
		}
	}
	return endPos;
}


vector<Cycle> Postprocess::remove_long_gaps(vector<Cycle> &icycles, int imaxGapAllowed, int iscoreThreshold) {
	if (imaxGapAllowed < 0) {
		return icycles;
	}
	vector<Cycle> retval;

	for (Cycle c : icycles) {
		vector<Edge> edges = c.getGraph().getEdges();
		int endPos = getEndPositionOfCycle(edges);
		const int PADDING = 4;
		vector<int8_t> strsMask(endPos + PADDING + imaxGapAllowed, 0);

		for (size_t i=0; i<edges.size(); i++) {
			create_mask(edges[i].getPositions(), strsMask);
		}
		smashCycle(c, strsMask, imaxGapAllowed, iscoreThreshold, retval);
	}

	return retval;
}


void Postprocess::filterHomopolymers(std::vector<graph::Cycle> &icycles, bool ifilterHomopolymers) {
	if (!ifilterHomopolymers)
		return ;

	for (size_t i=0; i<icycles.size(); i++) {
		std::set<char> residues;
		for (char ch : icycles[i].to_string()) {
			if (ch != '-' && ch != '_') {
				residues.insert(ch);
			}
		}
		if (residues.size() == 1) {
			icycles.erase(icycles.begin() + i);
			i--;
		}
	}
}


void Postprocess::minMaxNodeCount(std::vector<graph::Cycle> &icycles, int iminNodeCount, int imaxNodeCount) {
	if (iminNodeCount <= 0 && imaxNodeCount == std::numeric_limits<int>::max())
		return ;

	for (size_t i=0; i<icycles.size(); i++) {
		Cycle c = icycles[i];
		std::set<string> nodes;
		for (Edge e : c.getGraph().getEdges()) {
			if (e.getNodeFrom().getContent() != "") {
				nodes.insert(e.getNodeFrom().getContent());
			}
			if (e.getNodeTo().getContent() != "") {
				nodes.insert(e.getNodeTo().getContent());
			}
		}
		if (!((int)nodes.size() >= iminNodeCount && (int)nodes.size() <= imaxNodeCount)) {
			icycles.erase(icycles.begin() + i);
			i--;
		}
	}
}


void Postprocess::minStrLengthByNodeCount(std::vector<graph::Cycle> &icycles, int iweightThreshold) {

	for (size_t i=0; i<icycles.size(); i++) {
		Cycle c = icycles[i];

		int length = c.getEnd() - c.getBegin() + 1;
		//int nodeCount = c.getGraph().getNodeCount();
		int nodeCount = c.getGraph().getAminoacids().size();
//		if (nodeCount == 1) {
			//nodeCount++;
//		}

		if (((float)nodeCount * (iweightThreshold + 1) / length > 1) ||
				((nodeCount == 1) && (length < iweightThreshold + 2))) {
			icycles.erase(icycles.begin() + i);
			i--;
		}
	}
}




