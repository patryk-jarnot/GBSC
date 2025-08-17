#include "include/similaritysearch.h"
#include "include/gbsc.h"
#include "include/graph.h"
#include "include/fasta.h"
#include "include/output.h"
#include "include/threadpool.h"
#include "include/postprocess.h"
#include "include/alphabet.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>

using namespace similaritysearch;
using namespace postprocess;
using namespace alphabet;
using namespace std;


Search::Search(Options *iopt, std::istream *iinput, std::ostream *ioutput) : opt(iopt), input(iinput), output(ioutput) {

}


Search::~Search() {

}


/*
 * 1. Read fasta sequence by sequence
 * 2. For each sequence
 * 3. 	identify similar graphs
 * 4. 	save similar STRs
 * 5. Assign score to similar STRs
 * 6. Sort by score
 * 7. print records
 */
void Search::scanFasta(std::istream *queryStream) {
	fasta::FastaReader queryFr(queryStream);
	fasta::FastaReader databaseFr(input);

	Gbsc gbsc;
	Postprocess pp;
	Alphabet alphabetReduction;
	alphabetReduction.setAlphabet(opt->getAlphabetReduction());
	std::vector<std::pair<fasta::Sequence, std::vector<graph::Cycle> > > input_sequences;
	while (queryFr.hasNextSequence()) {
		std::pair<fasta::Sequence, std::vector<graph::Cycle> > seq_data;
		seq_data.first = *queryFr.readNextSequence();
		if (seq_data.first.sequence.length() == 0) {
			continue;
		}
//		cout << "\nquery sequence: " << qs->sequence << "\n";
		seq_data.second = gbsc.findSubgraphs(seq_data.first.sequence, opt->getWeightThreshold(), opt->getLifetime(), opt->isIncludeOrphanNodes(), &alphabetReduction);
		seq_data.second = pp.remove_long_gaps(seq_data.second, opt->getMaxGapLength(), opt->getWeightThreshold());
		pp.filterHomopolymers(seq_data.second, opt->isFilterHomopolymers());
		pp.minMaxNodeCount(seq_data.second, opt->getMinNodeCount(), opt->getMaxNodeCount());
		pp.minStrLengthByNodeCount(seq_data.second, opt->getWeightThreshold());
		databaseFr.resetFilePointer();
		input_sequences.push_back(seq_data);
	}


	while (databaseFr.hasNextSequence()) {
		auto ds = databaseFr.readNextSequence();
		if (ds->sequence.length() == 0) {
			continue;
		}
		std::vector<graph::Cycle> databaseCycles = gbsc.findSubgraphs(ds->sequence, opt->getWeightThreshold(), opt->getLifetime(), opt->isIncludeOrphanNodes(), &alphabetReduction);
		databaseCycles = pp.remove_long_gaps(databaseCycles, opt->getMaxGapLength(), opt->getWeightThreshold());
		pp.filterHomopolymers(databaseCycles, opt->isFilterHomopolymers());
		pp.minMaxNodeCount(databaseCycles, opt->getMinNodeCount(), opt->getMaxNodeCount());
		pp.minStrLengthByNodeCount(databaseCycles, opt->getWeightThreshold());

		for (auto seq_data : input_sequences) {
			findSimilarities(seq_data.second, databaseCycles, seq_data.first, *ds);
		}
	}
	output::print_search_results(output, opt->getSearchOutputFormat(), getResults(), opt->getMaxHitCount());
}


int scanFasta_thread(Search *search, std::vector<std::pair<fasta::Sequence, std::vector<graph::Cycle> > > input_sequences, fasta::Sequence ds, int iweightThreshold, int ilifetime, bool iincludeOrphanNodes, int imaxGapLen, int iminNodeCount, int imaxNodeCount, bool iisFilterHomopolymers, Alphabet *ialphabetReduction) {
	Gbsc gbsc;
	Postprocess pp;

	std::vector<graph::Cycle> databaseCycles = gbsc.findSubgraphs(ds.sequence, iweightThreshold, ilifetime, iincludeOrphanNodes, ialphabetReduction);
	databaseCycles = pp.remove_long_gaps(databaseCycles, imaxGapLen, iweightThreshold);
	pp.filterHomopolymers(databaseCycles, iisFilterHomopolymers);
	pp.minMaxNodeCount(databaseCycles, iminNodeCount, imaxNodeCount);
	pp.minStrLengthByNodeCount(databaseCycles, iweightThreshold);

//	search->findSimilarities(queryCycles, databaseCycles, qs, ds);
	for (auto seq_data : input_sequences) {
		search->findSimilarities(seq_data.second, databaseCycles, seq_data.first, ds);
	}
	return 0;
}


void Search::scanFastaThreads(std::istream *queryStream, int ithreadCount) {
	fasta::FastaReader queryFr(queryStream);
	fasta::FastaReader databaseFr(input);

	Gbsc gbsc;
	Postprocess pp;
	Alphabet alphabetReduction;
	alphabetReduction.setAlphabet(opt->getAlphabetReduction());
	std::vector<std::pair<fasta::Sequence, std::vector<graph::Cycle> > > input_sequences;
	while (queryFr.hasNextSequence()) {
		std::pair<fasta::Sequence, std::vector<graph::Cycle> > seq_data;
		seq_data.first = *queryFr.readNextSequence();
		if (seq_data.first.sequence.length() == 0) {
			continue;
		}
		seq_data.second = gbsc.findSubgraphs(seq_data.first.sequence, opt->getWeightThreshold(), opt->getLifetime(), opt->isIncludeOrphanNodes(), &alphabetReduction);
		seq_data.second = pp.remove_long_gaps(seq_data.second, opt->getMaxGapLength(), opt->getWeightThreshold());
		pp.filterHomopolymers(seq_data.second, opt->isFilterHomopolymers());
		pp.minMaxNodeCount(seq_data.second, opt->getMinNodeCount(), opt->getMaxNodeCount());
		pp.minStrLengthByNodeCount(seq_data.second, opt->getWeightThreshold());
		databaseFr.resetFilePointer();
		input_sequences.push_back(seq_data);
	}


	ThreadPool tp(ithreadCount);
	while (databaseFr.hasNextSequence()) {
		while (tp.getTasksCount() > (20 * ithreadCount)) std::this_thread::sleep_for(std::chrono::microseconds(500));
		auto ds = databaseFr.readNextSequence();
		if (ds->sequence.length() == 0) {
			continue;
		}

		std::future<int> x = tp.enqueue(scanFasta_thread, this, input_sequences, *ds, opt->getWeightThreshold(), opt->getLifetime(), opt->isIncludeOrphanNodes(), opt->getMaxGapLength(), opt->getMinNodeCount(), opt->getMaxNodeCount(), opt->isFilterHomopolymers(), &alphabetReduction);
	}
	output::print_search_results(output, opt->getSearchOutputFormat(), getResults(), opt->getMaxHitCount());
}

float calculate_score(graph::Cycle &queryCycle, graph::Cycle &hitCycle) {
	int qlen = queryCycle.getEnd() - queryCycle.getBegin();
	int hlen = hitCycle.getEnd() - hitCycle.getBegin();

	int total_q_weight = 0;
	int total_weight_score = 0;
	for (graph::Edge q : queryCycle.getGraph().getEdges()) {
		int q_weight = q.getWeight();
		int h_weight = hitCycle.getGraph().getEdgeWeight(q);
		int weight_distance = abs(q_weight - h_weight);

		total_weight_score += q_weight - weight_distance;
		total_q_weight += q_weight;
	}

	int len_distance = abs(qlen - hlen);
	int len_score = qlen - len_distance;


	return (float)(total_weight_score + len_score) / (total_q_weight + qlen);
}

void Search::findSimilarities(std::vector<graph::Cycle> queryCycles, std::vector<graph::Cycle> databaseCycles, fasta::Sequence querySequence, fasta::Sequence hitSequence) {
	for (auto qc : queryCycles) {
		search_result_query_t searchResultQuery;
		searchResultQuery.queryHeader = querySequence.header + "|" + std::to_string(qc.getBegin()) + "|" + std::to_string(qc.getEnd()) + "|" + qc.to_string();
		searchResultQuery.querySequence = querySequence.sequence.substr(qc.getBegin()-1, qc.getEnd() - qc.getBegin()+1);
		searchResultQuery.begin = qc.getBegin();
		searchResultQuery.end = qc.getEnd();
		searchResultQuery.queryCycle = qc;

		for (auto dc : databaseCycles) {

			// is graph structure the same?
			if (qc.getGraph().to_string().compare(dc.getGraph().to_string()) == 0) {
				search_result_hit_t searchResultHit;

//				searchResultHit.hitHeader = hitSequence.header;
				searchResultHit.hitHeader = hitSequence.header + "|" + std::to_string(dc.getBegin()) + "|" + std::to_string(dc.getEnd()) + "|" + dc.to_string();
				searchResultHit.hitSequence = hitSequence.sequence.substr(dc.getBegin()-1, dc.getEnd() - dc.getBegin()+1);
				searchResultHit.begin = dc.getBegin();
				searchResultHit.end = dc.getEnd();
				searchResultHit.hitCycle = dc;

//				int qlen = qc.getEnd() - qc.getBegin();
//				int hlen = dc.getEnd() - dc.getBegin();
//				searchResultHit.score = abs(qlen - hlen);
				searchResultHit.score = calculate_score(qc, dc);

				searchResultQuery.hits.push_back(searchResultHit);
			}
		}
		if (searchResultQuery.hits.size() > 0) {
//			results.push_back(searchResultQuery);
			std::lock_guard<std::mutex> guard(results_mutex);

			if (results.find(searchResultQuery.queryHeader) == results.end()) {
				results[searchResultQuery.queryHeader] = searchResultQuery;
			}
			else {
				for (auto hit : searchResultQuery.hits) {
					results[searchResultQuery.queryHeader].hits.push_back(hit);
				}
			}
		}
	}
}


