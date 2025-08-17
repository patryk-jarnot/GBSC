/*
 * testmodel.cpp
 *
 *  Created on: Jul 4, 2022
 *      Author: pjarnot
 */

#include "include/model.h"
#include "include/fasta.h"

#include "include/debug.h"

#include "assert.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <set>


using namespace std;
using namespace model;

vector<fasta::Cluster> create_sample_clusters() {
	vector<fasta::Cluster> retval;

	vector<fasta::Sequence> sequences;
	sequences.push_back(fasta::Sequence(">header 1", "EEDDEEDDEEDDEEDDEEDDEEDDEE"));
	sequences.push_back(fasta::Sequence(">header 2", "EEDDEEDDXEEDDEEDDEEYDDEEDDEE"));

	retval.push_back(fasta::Cluster("DD-DE_DE-EE_ED-DD_EE-ED", "DD-DE_DE-EE_ED-DD_EE-ED.fasta", sequences));

	sequences = vector<fasta::Sequence>();
	sequences.push_back(fasta::Sequence(">header 1", "EEDPDEEDPDEEDPDEEDPDEEDPDEEDPDEEDPD"));

	retval.push_back(fasta::Cluster("DE-EE_DP-PD_ED-DP_EE-ED_PD-DE", "DE-EE_DP-PD_ED-DP_EE-ED_PD-DE.fasta", sequences));

	return retval;
}


unique_ptr<istream> create_sample_sequences() {
	unique_ptr<stringstream> retval(new stringstream());

	*retval << ">header 1\n";
	*retval << "AQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQ\n";
	*retval << ">header 2\n";
	*retval << "EEDPDDEEDPDDEEDPDDEEDPDDEEDPDDEEDPDDEEDPDDEEDPDDEEDPDDEEDPDD\n";
	*retval << ">header 3\n";
	*retval << "EEDDEEDDEEDDEEDDEEDDEEDDEEDDEEDDEEDDEEDDEEDDEEDD\n";

	retval->seekp(0);

	return retval;
}


void test_model_creation() {
//	vector<fasta::Cluster> clusters = create_sample_clusters();
//
//	Model model();
//	model.load(clusters);
//
//	assert(model.toString() == "DD-DE_DE-EE_DP-PD_ED-DD_ED-DP_EE-ED_PD-DE");
}


void test_model_weights() {
//	vector<fasta::Cluster> clusters = create_sample_clusters();
//
//	Model model();
//	model.load(clusters);
//
//	for (auto edge : model.getEdges()) {
//		if (edge.toString() == "DD-DE") {
//			assert(edge.getWeight() == 2);
//		}
//		else if (edge.toString() == "DE-EE") {
//			assert(edge.getWeight() == 3);
//		}
//		else if (edge.toString() == "DP-PD") {
//			assert(edge.getWeight() == 1);
//		}
//		else if (edge.toString() == "ED-DD") {
//			assert(edge.getWeight() == 2);
//		}
//		else if (edge.toString() == "ED-DP") {
//			assert(edge.getWeight() == 1);
//		}
//		else if (edge.toString() == "EE-ED") {
//			assert(edge.getWeight() == 3);
//		}
//		else if (edge.toString() == "PD-DE") {
//			assert(edge.getWeight() == 1);
//		}
//		else {
//			assert(false);
//		}
//	}
}


/**
 * As a basic approach we are looking for models which differ just in a single residue (single indel or mutation).
 *
 * Edges:
 * Insertion in our graph is equal to removal of two edges and addition of three.
 * Deletion in our graph is equal to removal of two edges and addition of one.
 * Mutation in our graph is equal to removal of three edges and addition of three.
 *
 * Nodes:
 * Insertion in our graph is equal to removal of one node and addition of two.
 * Deletion in our graph is equal to removal of one node.
 * Mutation in our graph is equal to removal of two nodes and addition of two.
 *
 * We can also set minimal number of common edges.
 * For bigger graphs, should we allow for more distinct graphs?.
 * On the other hand, bigger graphs are more grained and joining will have property of transitivity
 *
 * We can allow to remove three edges and add three edges.
 * Minimal number of common edges is 2.
 *
 * --------------[beg] CURRENT APPROACH------------------------------------------------
 * In the first version we will use score calculated as follow:
 * S = sum(ct_i * w_i) + sum(sn_i * w_i) - sum(nt_i)
 * ct - common transitions
 * nt - new transitions
 * cn - common nodes
 * nn - new nodes
 * sn = cn not in ct - shared nodes
 *
 * Also pattern length has to be used in the equation
 * or avarage distance between occurences
 * --------------[end] CURRENT APPROACH------------------------------------------------
 */
void test_model_similarity() {
//	vector<fasta::Cluster> clusters = create_sample_clusters();
//
//	Model model();
//	model.load(clusters);
//
//	fasta::Sequence sequence = fasta::Sequence(">header 1", "EEDDEEDDEEDDEEDDEEDDEEDDEE");
//	float score = model.calculateScore(sequence);
//
//	assert(score == 9999999999);  // TODO
}


/**
 * Report sequences sharing similar model.
 *
 * Searching for similar sequences will use model similarity to determine whether the sequence is similar or not.
 * It will also use iterative approach extending the model after each iteration.
 * As an input the search will take a database and query model or query cluster from which the model will be created on the fly.
 *
 */
void test_model_search() {
//	vector<fasta::Cluster> clusters = create_sample_clusters();
//
//	Model model();
//	model.load(clusters);
//	unique_ptr<istream> ist = create_sample_sequences();
//
//	vector<model_search_result_t> results = model.search(ist);
//
//	for (auto result : results) {
//		if (result.header == ">header 2") {
//			assert(true);
//		}
//		else if (result.header == ">header 3") {
//			assert(true);
//		}
//		else {
//			assert(false);
//		}
//	}
}


void test_model_serialization() {
//	vector<fasta::Cluster> clusters = create_sample_clusters();
//	iostream iost = stringstream();
//
//	Model model;
//	model.load(clusters);
//
//	model.serialize(iost);
//
//	iost.seekg(0);
//
//	Model modelSerialized;
//	modelSerialized.deserialize(iost);
//
//	assert(model.isEqual(modelSerialized));
}


int main(int argc, char** argv)
{
    cout << "Test model" << endl;
    test_model_creation();
	test_model_weights();
	test_model_similarity();
	test_model_search();
	test_model_serialization();
	cout << "Test model passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}







