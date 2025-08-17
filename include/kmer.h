/*
 * kmer.h
 *
 *  Created on: Jun 26, 2022
 *      Author: pjarnot
 */

#ifndef CONTENT_INCLUDE_KMER_H_
#define CONTENT_INCLUDE_KMER_H_

#include <string>
#include <map>
#include <set>

namespace kmer {
	std::map<std::string, int> findKmers(std::string isequence, std::set<std::string> ikmers);
}


#endif /* CONTENT_INCLUDE_KMER_H_ */
