/*
 * model.h
 *
 *  Created on: Jun 26, 2022
 *      Author: pjarnot
 */

#ifndef CONTENT_INCLUDE_MODEL_H_
#define CONTENT_INCLUDE_MODEL_H_

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "include/graph.h"
#include "include/fasta.h"


namespace model {

struct model_search_result_t {
	std::string header;
	std::string sequence;
	std::string model;
	float score;
};


struct model_node_t {
	std::string label;
	int weight;
};


struct model_edge_t {
	model_node_t from;
	model_node_t to;
	int weight;
};


struct model_graph_t {
	std::vector<model_edge_t> edges;
};


class Model {
public:
	void load(std::vector<fasta::Cluster>);

	void serialize(std::ostream);
	void deserialize(std::istream);

	std::string toString();

	std::vector<graph::Edge> getEdges();
	float calculateScore(fasta::Sequence);

	std::vector<model_search_result_t> search(std::istream ist);

	bool isEqual(Model);

private:
	model_graph_t modelGraph;

};

}


#endif /* CONTENT_INCLUDE_MODEL_H_ */
