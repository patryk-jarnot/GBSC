/*
 * kmer.cpp
 *
 *  Created on: Jun 26, 2022
 *      Author: pjarnot
 */

#include "include/kmer.h"

#include <set>
#include <iostream>

using namespace std;
using namespace kmer;

std::map<std::string, int> kmer::findKmers(std::string isequence, std::set<std::string> ikmers) {
	std::map<std::string, int> retval;

	for (auto kmer : ikmers) {
	    size_t index = 0;
	    while ((index = isequence.find(kmer, index+1)) != std::string::npos) {
	    	retval[kmer]++;
	    }
	}

	return retval;
}

