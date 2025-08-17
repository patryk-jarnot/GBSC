/*
 * graph.h
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_SEARCH_H_
#define GBSC_INCLUDE_SEARCH_H_

#include "include/options.h"

#include <string>
#include <vector>
#include <map>
#include <mutex>

#include "graph.h"
#include "fasta.h"


namespace similaritysearch {

struct search_result_hit_t {
public:
	std::string hitHeader;
	std::string hitSequence;
	int begin;
	int end;
	graph::Cycle hitCycle;

	float score;

    bool operator< (const search_result_hit_t &other) const {
        return score < other.score;
    }
};


struct search_result_query_t {
public:
	std::string queryHeader;
	std::string querySequence;
	int begin;
	int end;
	graph::Cycle queryCycle;

	std::vector<search_result_hit_t> hits;
};


class Search {
public:
	Search(Options *iopt, std::istream *iinput, std::ostream *ioutput);
	~Search();

	void scanFasta(std::istream *queryStream);
	void scanFastaThreads(std::istream *queryStream, int ithreadCount);
	void findSimilarities(std::vector<graph::Cycle> queryCycles, std::vector<graph::Cycle> databaseCycles, fasta::Sequence querySequence, fasta::Sequence hitSequence);

	std::vector<search_result_query_t> getResults() {
		std::vector<search_result_query_t> v;
	    for( auto it = results.begin(); it != results.end(); ++it ) {
	        v.push_back( it->second );
	    }
		return v;
	}

private:
	Options *opt;
//	std::vector<search_result_query_t> results;
	std::map<std::string, search_result_query_t> results;

	std::istream *input;
	std::ostream *output;
	std::mutex results_mutex;

};

}

#endif /* GBSC_INCLUDE_SEARCH_H_ */
