/*
 * testpostprocess.cpp
 *
 *  Created on: Jan 28, 2022
 *      Author: pjarnot
 */
#include "include/debug.h"
#include "include/postprocess.h"
#include "include/gbsc.h"
#include "include/alphabet.h"

#include "assert.h"

#include <iostream>
#include <sstream>
#include <limits>


using namespace std;
using namespace postprocess;
using namespace alphabet;


void test_maxgap_split_homopolymer() {
	string sequence = "QQQQQQQQQQQASFQQQQQQQQQQQQQQQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 29);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 2);
	for (size_t i=0; i<cycles.size(); i++)
	{
		graph::Cycle c = cycles[i];

		if (i == 0) {
			assert(c.getBegin() == 1);
			assert(c.getEnd() == 11);
		}

		if (i == 1) {
			assert(c.getBegin() == 15);
			assert(c.getEnd() == 29);
		}
	}
}


void test_maxgap_remove_homopolymer() {
	string sequence = "QQQQASDQQQQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 11);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 0);
}


void test_maxgap_skip_homopolymer() {
	string sequence = "QQQQASDQQQQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 11);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 4, 3);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 11);
	}
}


void test_maxgap_split_str() {
	string sequence = "QAQAQAQAQAQASDFQAQAQAQAQAQAQAQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 8, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 30);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	for (size_t i=0; i<cycles.size(); i++)
	{
		graph::Cycle c = cycles[i];

		if (i == 0) {
			assert(c.getBegin() == 1);
			assert(c.getEnd() == 12);
		}

		if (i == 1) {
			assert(c.getBegin() == 16);
			assert(c.getEnd() == 30);
		}
	}
}


void test_maxgap_remove_str() {
	string sequence = "QAQAQASDFQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 8, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 15);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 0);
}


void test_maxgap_skip_str() {
	string sequence = "QAQAQAQSDQAQAQAQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 8, false, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 16);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 16);
	}
}


void test_maxgap_split_orphan_node() {
	string sequence = "QAKQANQAWQAEQAHSDFQARQAIQAMQAVQAC";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, true, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 32);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 2);
	for (size_t i=0; i<cycles.size(); i++)
	{
		graph::Cycle c = cycles[i];

		if (i == 0) {
			assert(c.getBegin() == 1);
			assert(c.getEnd() == 14);
		}

		if (i == 1) {
			assert(c.getBegin() == 19);
			assert(c.getEnd() == 32);
		}
	}
}


void test_maxgap_remove_orphan_node() {
	string sequence = "QARQASDFQAEQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, true, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 13);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 2, 3);

	assert(cycles.size() == 0);
}


void test_maxgap_skip_orphan_node() {
	string sequence = "QAWQARQASDFQAEQAIQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, true, &a);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 19);
	}

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, 3, 3);

	assert(cycles.size() == 1);
	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 19);
	}
}


void test_filter_homopolymers_polyq() {
	string sequence = "QQQQQQQQQQQQQQ";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.filterHomopolymers(cycles, true);

	assert(cycles.size() == 0);
}


void test_filter_homopolymers_strs() {
	string sequence = "QAQAQAQAQAQAQAQAQAQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.filterHomopolymers(cycles, true);

	assert(cycles.size() == 1);
}


void test_min_node_count_remove() {
	string sequence = "QAQAQAQAQAQAQAQAQAQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.minMaxNodeCount(cycles, 3, std::numeric_limits<int>::max());

	assert(cycles.size() == 0);
}


void test_min_node_count_stay() {
	string sequence = "SDASDASDASDASDASDASDASDASDASDASDASDA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.minMaxNodeCount(cycles, 3, std::numeric_limits<int>::max());

	assert(cycles.size() == 1);
}


void test_max_node_count_remove() {
	string sequence = "SDASDASDASDASDASDASDASDASDASDASDASDA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.minMaxNodeCount(cycles, 0, 2);

	assert(cycles.size() == 0);
}


void test_max_node_count_stay() {
	string sequence = "QAQAQAQAQAQAQAQAQAQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	assert(cycles.size() == 1);

	Postprocess pp;
	pp.minMaxNodeCount(cycles, 0, 2);

	assert(cycles.size() == 1);
}



int main(int argc, char** argv)
{
    cout << "Test postprocess" << endl;
    test_maxgap_split_homopolymer();
    test_maxgap_remove_homopolymer();
    test_maxgap_skip_homopolymer();
    test_maxgap_split_str();
    test_maxgap_remove_str();
    test_maxgap_skip_str();
    test_maxgap_split_orphan_node();
    test_maxgap_remove_orphan_node();
    test_maxgap_skip_orphan_node();

    test_filter_homopolymers_polyq();
    test_filter_homopolymers_strs();

    test_min_node_count_remove();
    test_min_node_count_stay();

    test_max_node_count_remove();
    test_max_node_count_stay();

	cout << "Test postprocess passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}



