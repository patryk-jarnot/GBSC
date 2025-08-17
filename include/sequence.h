/*
 * sequence.h
 *
 *  Created on: Jun 12, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_SEQUENCE_H_
#define GBSC_INCLUDE_SEQUENCE_H_

#include <string>
#include <vector>

namespace seq
{
	std::vector<std::string> getKMers(std::string sequence, int k);
}


#endif /* GBSC_INCLUDE_SEQUENCE_H_ */
