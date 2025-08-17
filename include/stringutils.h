/*
 * stringutils.h
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_STRINGUTILS_H_
#define GBSC_INCLUDE_STRINGUTILS_H_

#include <string>
#include <vector>

namespace strutils {
	std::vector<std::string> split(std::string istr, std::string idelimiter);
}


#endif /* GBSC_INCLUDE_STRINGUTILS_H_ */
