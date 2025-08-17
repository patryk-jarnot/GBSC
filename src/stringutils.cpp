/*
 * stringutils.cpp
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */

#include "include/stringutils.h"
#include <string>
#include <iostream>

using namespace std;

std::vector<std::string> strutils::split(std::string istr, std::string idelimiter) {
	std::vector<std::string> retval;

	size_t prev_pos = 0;
	size_t cur_pos = istr.find(idelimiter, prev_pos);

	if (cur_pos == std::string::npos) {
		return retval;
	}
	while (cur_pos != std::string::npos) {
		retval.push_back(istr.substr(prev_pos, cur_pos - prev_pos));
		prev_pos = cur_pos + idelimiter.size();
		cur_pos = istr.find(idelimiter, prev_pos);
	}
	retval.push_back(istr.substr(prev_pos));
	return retval;
}

