#include "include/debug.h"
#include "include/gbsc.h"
#include "include/sequence.h"
#include "include/alphabet.h"

#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <climits>
#include <memory>

using namespace std;



std::vector<graph::Cycle> Gbsc::findSubgraphs(std::string isequence, int iweightThreshold, int ilifetime, bool includeNodes=false, alphabet::Alphabet *ialphabet=nullptr)
{
	if (ialphabet != nullptr)
		isequence = ialphabet->reduceSequence(isequence);
    std::vector<std::string> kMers = seq::getKMers(isequence, 2);

    findEdgesAndNodes(kMers, iweightThreshold,
                            ilifetime);

    std::set<int> edgesAndNodesPos = createSetOfEdgePositions();

    removeNodesExistsInEdges(edgesAndNodesPos, iweightThreshold);

    std::vector<graph::Cycle> subgraphs = mergeEdges(ilifetime);

    if (includeNodes)
    {
        std::vector<graph::Cycle> mergedNodes = mergeOverlappingNodes(ilifetime);
        for (auto subgraph : mergedNodes)
        {
            subgraphs.push_back(subgraph);
        }
        appendCyclesFromNodes(subgraphs);
    }

    clean();
    return subgraphs;
}


void Gbsc::clean() {
	foundEdges.clear();
	foundNodes.clear();
}


void Gbsc::processNode(const std::string & ikmer, std::vector<graph::Node> &ionodes, const size_t &i) {

	auto nodeIt = find_if(ionodes.begin(), ionodes.end(), [&ikmer](const graph::Node& obj) {return obj.getContent() == ikmer;});
	if (nodeIt == ionodes.end())
	{
		graph::Node node = graph::Node(ikmer);
		ionodes.push_back(node);
		nodeIt = ionodes.end() - 1;
	}

	nodeIt->increaseWeight();
	nodeIt->setTime(0);
	nodeIt->addPos(i);
}


void Gbsc::processEdge(graph::Edge &iedgeKey, std::vector<graph::Edge> &ioedges, const size_t &i) {

	auto edgeIt = find_if(ioedges.begin(), ioedges.end(), [&iedgeKey](graph::Edge& obj) {return obj.getNodeFrom().getContent() == iedgeKey.getNodeFrom().getContent() && obj.getNodeTo().getContent() == iedgeKey.getNodeTo().getContent();});

	if (edgeIt == ioedges.end())
	{
		ioedges.push_back(iedgeKey);
		edgeIt = ioedges.end() - 1;
	}

	edgeIt->increaseWeight();
	edgeIt->setTime(0);
	edgeIt->addPos(i-1, i);
}


void Gbsc::handleStrsFromNodes(std::vector<graph::Node> *ionodes,
			int iweightThreshold, int ilifetime) {
	for (size_t i=0; i<ionodes->size(); i++)
	{
		(*ionodes)[i].increaseTime();
		if ((*ionodes)[i].reachedLifetime(ilifetime))
		{
			if ((*ionodes)[i].reachedWeightThreshold(iweightThreshold))
			{
				foundNodes.push_back((*ionodes)[i]);
			}
			ionodes->erase(ionodes->begin() + i);
		}
	}
}


void Gbsc::handleStrsFromEdges(std::vector<graph::Edge> *ioedges,
			int iweightThreshold, int ilifetime) {
	for (size_t i=0; i<ioedges->size(); i++)
	{
		(*ioedges)[i].increaseTime();
		if ((*ioedges)[i].reachedLifetime(ilifetime))
		{
			if ((*ioedges)[i].reachedWeightThreshold(iweightThreshold))
			{
				foundEdges.push_back((*ioedges)[i]);
			}
			ioedges->erase(ioedges->begin() + i);
		}
	}
}


void Gbsc::findEdgesAndNodes(std::vector<std::string> ikMers,
			int iweightThreshold, int ilifetime)
{
    std::vector<graph::Node> nodes;
    std::vector<graph::Edge> edges;

    for (size_t i=0; i<ikMers.size(); i++)
    {
		string kMer = ikMers[i];
		processNode(kMer, nodes, i);

        if (i != 0)
        {
			graph::Edge edgeKey(graph::Node(ikMers[i-1]), graph::Node(ikMers[i]), 0, 0);
			processEdge(edgeKey, edges, i);
        }

        handleStrsFromNodes(&nodes, iweightThreshold, ilifetime);
        handleStrsFromEdges(&edges, iweightThreshold, ilifetime);
    }

    addRemainingItems(&edges, &foundEdges, iweightThreshold);
    addRemainingItems(&nodes, &foundNodes, iweightThreshold);
}


template<typename T>
void Gbsc::addRemainingItems(std::vector<T> *ioitems,
    		std::vector<T> *iofoundItems, int iscoreThreshold)
{
	for (size_t i=0; i<ioitems->size(); i++)
	{
		if ((*ioitems)[i].getWeight() >= iscoreThreshold)
		{

			iofoundItems->push_back((*ioitems)[i]);
		}
	}
}


std::set<int> Gbsc::createSetOfEdgePositions()
{
	std::set<int> retval;

	for (size_t i=0; i<foundEdges.size(); i++)
	{
		for (auto positions : foundEdges[i].getPositions())
		{
			retval.insert(positions.begin);
			retval.insert(positions.end);
		}
	}

	return retval;
}


void Gbsc::removeNodesExistsInEdges(std::set<int> iedgePos,
    		int iweightThreshold)
{
    size_t n = 0;
    while (n < foundNodes.size())
    {
        int p = 0;
        while (p < foundNodes[n].getPosSize())
        {
        	auto it = find(iedgePos.begin(), iedgePos.end(), foundNodes[n].getPos(p));
        	if (it != iedgePos.end())
            {
                // foundNodes[n].pos.erase(foundNodes[n].pos.begin() + p);
                foundNodes[n].removePos(p);
            }
            else
            {
                p += 1;
            }
        }
        if (foundNodes[n].getPosSize() < iweightThreshold)
        {
            foundNodes.erase(foundNodes.begin() + n);
//        	n += 1;
        }
        else
        {
        	n += 1;
        }
    }
}


std::vector<graph::Cycle> Gbsc::mergeEdges(int ilifetime) {
	std::vector<graph::Cycle> retval;

	int POS_MAX = INT_MAX;

	unique_ptr<graph::Cycle> cycle;

	int prev_beg = -1 * POS_MAX;
	int prev_end = POS_MAX;
	for (auto t : foundEdges) {
		int beg = t.getBegin();
		int end = t.getEnd();
		if ((beg - ilifetime) > prev_beg || beg > prev_end || end < prev_beg) {
			if (cycle) {
				addPreviousEdges(cycle.get(), ilifetime);
				retval.push_back(*(cycle.get()));
			}
			cycle = unique_ptr<graph::Cycle>(new graph::Cycle());
		}
//		if (cycle->getBegin() > beg) {
//			cycle->setBegin(beg);
//		}
//		if (cycle->getEnd() < end) {
//			cycle->setEnd(end);
//		}
		cycle->addEdge(t);
		prev_beg = beg;
		prev_end = end;
	}
	if (cycle) {
		addPreviousEdges(cycle.get(), ilifetime);
		retval.push_back(*(cycle.get()));
	}
	return retval;
}


void Gbsc::addPreviousEdges(graph::Cycle *icycle, int ilifetime)
{
    for (auto edge : foundEdges)
    {
    	overlapOfLineSegments(2, 1, icycle->getBegin(), icycle->getEnd());
        if ((edge.getBegin() - ilifetime) < icycle->getBegin() && (edge.getEnd() + ilifetime) > icycle->getEnd()
                && overlapOfLineSegments(edge.getBegin(), edge.getEnd(), icycle->getBegin(), icycle->getEnd()) > ((icycle->getEnd() - icycle->getBegin()) / 2))
        {
            icycle->addEdge(edge);
        }
    }
}


bool Gbsc::overlapOfLineSegments(int l1_beg, int l1_end, int l2_beg, int l2_end)
{
    return max(0, min(l1_end, l2_end) - max(l1_beg, l2_beg));
}


void Gbsc::appendCyclesFromNodes(std::vector<graph::Cycle> isubgraphs)
{
    for (auto n : foundNodes)
    {
        graph::Cycle cycle;
        graph::Edge edge(n, graph::Node());
        cycle.addEdge(edge);
        isubgraphs.push_back(cycle);
    }
}

std::vector<graph::Cycle> Gbsc::mergeOverlappingNodes(int ilifetime)
{
	std::vector<graph::Cycle> retval;

	size_t i=0;
	while (i < foundNodes.size())
	{
		if (i < (foundNodes.size()-1) && nodesInLifetimeScope(foundNodes[i].getBegin(), foundNodes[i].getEnd(), foundNodes[i+1].getBegin(), foundNodes[i+1].getEnd(), ilifetime))
		{
			graph::Cycle cycle;
            cycle.addEdge(graph::Edge::createFromNodes(foundNodes[i]));
            cycle.addEdge(graph::Edge::createFromNodes(foundNodes[i+1]));
            int newBeg = min(foundNodes[i].getBegin(), foundNodes[i+1].getBegin());
            int newEnd = max(foundNodes[i].getEnd(), foundNodes[i+1].getEnd());
            i+=1;
            while (i < (foundNodes.size()-1) && nodesInLifetimeScope(newBeg, newEnd, foundNodes[i+1].getBegin(), foundNodes[i+1].getEnd(), ilifetime))
            {
                newBeg = min(newBeg, foundNodes[i+1].getBegin());
                newEnd = max(newEnd, foundNodes[i+1].getEnd());
				cycle.addEdge(graph::Edge::createFromNodes(foundNodes[i+1]));
                i+=1;
            }
            retval.push_back(cycle);
		}
		else
		{
			graph::Cycle cycle;
            cycle.addEdge(graph::Edge::createFromNodes(foundNodes[i]));
            retval.push_back(cycle);
		}
        i += 1;
	}

	return retval;
}

bool Gbsc::nodesInLifetimeScope(int inode1Begin, int inode1End, int inode2Begin, int inode2End, int idistanceThreshold)
{
    return abs(inode1Begin - inode2Begin) < idistanceThreshold && abs(inode1End - inode2End) < idistanceThreshold;
}


