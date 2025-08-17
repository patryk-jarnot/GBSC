/*
 * identify.cpp
 *
 *  Created on: Nov 9, 2021
 *      Author: pjarnot
 */
#include "include/debug.h"
#include "include/identify.h"
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

using namespace identify;
using namespace postprocess;
using namespace alphabet;
using namespace std;


Identify::Identify(Options *iopt, std::istream *iinput, std::ostream *ioutput) :
		opt(iopt), input(iinput), output(ioutput) {

}

Identify::~Identify() {

}


void Identify::scanFasta() {
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

		output::print_lcr_identification(output, *s, cycles, opt->getIdentifyOutputFormat(), opt->isPrintProtsWithLcrsOnly());
	}
}


int scanFasta_thread(ostream *output, fasta::Sequence &s, int iweightThreshold, int ilifetime, IdentifyOutputFormat ioutputfmt, bool iprintStrOnly, bool iincludeOrphanNodes, int imaxGapLen, int iminNodeCount, int imaxNodeCount, bool iisFilterHomopolymers, Alphabet *ialphabet) {
	Gbsc gbsc;
	if (s.sequence.length() == 0) {
		return -1;
	}
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(s.sequence, iweightThreshold, ilifetime, iincludeOrphanNodes, ialphabet);

	Postprocess pp;
	cycles = pp.remove_long_gaps(cycles, imaxGapLen, iweightThreshold);
	pp.filterHomopolymers(cycles, iisFilterHomopolymers);
	pp.minMaxNodeCount(cycles, iminNodeCount, imaxNodeCount);
	pp.minStrLengthByNodeCount(cycles, iweightThreshold);

	output::print_lcr_identification(output, s, cycles, ioutputfmt, iprintStrOnly);
	return 0;
}


void Identify::scanFastaThreads(int ithreadCount) {
	fasta::FastaReader fr(input);

	ThreadPool tp(ithreadCount);
	Alphabet alphabetReduction;
	alphabetReduction.setAlphabet(opt->getAlphabetReduction());
	while (fr.hasNextSequence()) {
		while (tp.getTasksCount() > (20 * ithreadCount)) std::this_thread::sleep_for(std::chrono::microseconds(500));
		auto s = fr.readNextSequence();
        std::future<int> x = tp.enqueue(scanFasta_thread, output, *s, opt->getWeightThreshold(), opt->getLifetime(), opt->getIdentifyOutputFormat(), opt->isPrintProtsWithLcrsOnly(), opt->isIncludeOrphanNodes(), opt->getMaxGapLength(), opt->getMinNodeCount(), opt->getMaxNodeCount(), opt->isFilterHomopolymers(), &alphabetReduction);
	}
}



