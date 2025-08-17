#include <string>
#include <vector>
#include <set>

#include "include/graph.h"
#include "include/alphabet.h"

class Gbsc
{
private:
    std::vector<graph::Node> foundNodes;
    std::vector<graph::Edge> foundEdges;


//	void processNode(const std::vector<std::string> &ikMers, std::vector<graph::Node> *ionodes, size_t i);
	void processNode(const std::string & ikmer, std::vector<graph::Node> &ionodes, const size_t &i);
//	void processEdge(const std::vector<std::string> &ikMers, std::vector<graph::Edge> *ioedges, size_t i);
	void processEdge(graph::Edge &iedgeKey, std::vector<graph::Edge> &ioedges, const size_t &i);
	void handleStrsFromNodes(std::vector<graph::Node> *ionodes, int iweightThreshold, int ilifetime);
	void handleStrsFromEdges(std::vector<graph::Edge> *ioedges, int iweightThreshold, int ilifetime);

    void findEdgesAndNodes(std::vector<std::string> ikMers,
			int iweightThreshold, int ilifetime);

	template<typename T>
	void addRemainingItems(std::vector<T> *ioitems,
				std::vector<T> *iofoundItems, int iwightThreshold);

	std::set<int> createSetOfEdgePositions();

    void removeNodesExistsInEdges(std::set<int> iedgesPos,
    		int iweightThreshold);
    std::vector<graph::Cycle> mergeEdges(int ilifetime);

	std::vector<graph::Cycle> mergeOverlappingNodes(int ilifetime);

	void addPreviousEdges(graph::Cycle *icycle, int ilifetime);

	bool overlapOfLineSegments(int l1_beg, int l1_end, int l2_beg, int l2_end);

    void appendCyclesFromNodes(std::vector<graph::Cycle> isubgraphs);

    bool nodesInLifetimeScope(int inode1Begin, int inode1End, int inode2Begin, int inode2End, int ilifetime);

protected:

public:
	Gbsc() {}
	virtual ~Gbsc() {}

	std::vector<graph::Cycle> findSubgraphs(std::string isequence, int iweightThreshold, int ilifetime, bool includeNodes, alphabet::Alphabet*);
	void clean();
};

