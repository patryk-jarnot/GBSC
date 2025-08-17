/*
 * cluster.cpp
 *
 *  Created on: Nov 2, 2021
 *      Author: pjarnot
 */
#include "include/cluster.h"
#include "include/fasta.h"
#include "include/gbsc.h"
#include "include/output.h"
#include "include/threadpool.h"
#include "include/postprocess.h"
#include "include/alphabet.h"

#include "assert.h"
#include <vector>
#include <thread>
#include <chrono>

using namespace cluster;
using namespace postprocess;
using namespace alphabet;
using namespace std;


Cluster::Cluster(Options *iopt, std::istream *iinput, std::ostream *ioutput) :
		opt(iopt), input(iinput), output(ioutput) {

}

Cluster::~Cluster() {

}

void Cluster::scanFasta() {
	fasta::FastaReader fr(input);

	Alphabet alphabetReduction;
	alphabetReduction.setAlphabet(opt->getAlphabetReduction());
	while (fr.hasNextSequence()) {
		auto s = fr.readNextSequence();
		Gbsc gbsc;
		if (s->sequence.length() == 0) {
			continue;
		}
		std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(s->sequence, opt->getWeightThreshold(), opt->getLifetime(), opt->isIncludeOrphanNodes(), &alphabetReduction);

		Postprocess pp;
		cycles = pp.remove_long_gaps(cycles, opt->getMaxGapLength(), opt->getWeightThreshold());
		pp.filterHomopolymers(cycles, opt->isFilterHomopolymers());
		pp.minMaxNodeCount(cycles, opt->getMinNodeCount(), opt->getMaxNodeCount());
		pp.minStrLengthByNodeCount(cycles, opt->getWeightThreshold());

		if (!opt->getClustersDirPath().empty()) {
			output::save_clusters(opt->getClustersDirPath(), *s, cycles, opt->getMaxLinkedStrsGap());
		}
		else {
			cout << "WARNING: opt->getClustersDirPath().empty(): True";
		}
	}
}


int scanFasta_thread(ostream *output, fasta::Sequence &s, int iweightThreshold, int ilifetime, bool iprintStrOnly, bool iincludeOrphanNodes, string &clusterDirPath, int imaxGapLen, int iminNodeCount, int imaxNodeCount, bool iisFilterHomopolymers, int maxLinkedStrsGap, Alphabet *ialphabetReduction) {
	Gbsc gbsc;
	if (s.sequence.length() == 0) {
		return -1;
	}
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(s.sequence, iweightThreshold, ilifetime, iincludeOrphanNodes, ialphabetReduction);

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, imaxGapLen, iweightThreshold);
	pp.filterHomopolymers(cycles, iisFilterHomopolymers);
	pp.minMaxNodeCount(cycles, iminNodeCount, imaxNodeCount);
	pp.minStrLengthByNodeCount(cycles, iweightThreshold);

	if (!clusterDirPath.empty()) {
		output::save_clusters(clusterDirPath, s, cycles, maxLinkedStrsGap);
	}
	else {
		cout << "WARNING: opt->getClustersDirPath().empty(): True";
	}
	return 0;
}


void Cluster::scanFastaThreads(int ithreadCount) {
	fasta::FastaReader fr(input);
	string clusterDirPath = opt->getClustersDirPath();

	Alphabet alphabetReduction;
	alphabetReduction.setAlphabet(opt->getAlphabetReduction());
	ThreadPool tp(ithreadCount);
	while (fr.hasNextSequence()) {
		while (tp.getTasksCount() > (20 * ithreadCount)) std::this_thread::sleep_for(std::chrono::microseconds(500));
		auto s = fr.readNextSequence();
        std::future<int> x = tp.enqueue(scanFasta_thread, output, *s, opt->getWeightThreshold(), opt->getLifetime(), opt->isPrintProtsWithLcrsOnly(), opt->isIncludeOrphanNodes(), clusterDirPath, opt->getMaxGapLength(), opt->getMinNodeCount(), opt->getMaxNodeCount(), opt->isFilterHomopolymers(), opt->getMaxLinkedStrsGap(), &alphabetReduction);
	}
}

