/*
 * sequence.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: pjarnot
 */

#include "include/sequence.h"

#include <string>
#include <vector>

using namespace std;
using namespace seq;

std::vector<std::string> seq::getKMers(std::string sequence, int k)
{
	std::vector<std::string> retval;

	for (int i=0; (size_t)i<sequence.length()-1; i++)
	{
		string kMer = sequence.substr(i, 2);
		retval.push_back(kMer);
	}

	return retval;
}

