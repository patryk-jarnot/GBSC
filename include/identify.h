/*
 * identify.h
 *
 *  Created on: Nov 9, 2021
 *      Author: pjarnot
 */

#ifndef SOURCE_INCLUDE_IDENTIFY_H_
#define SOURCE_INCLUDE_IDENTIFY_H_



#include "include/options.h"

#include <iostream>


namespace identify {

class Identify {
public:
	Identify(Options *iopt, std::istream *iinput, std::ostream *ioutput);
	~Identify();

	void scanFasta();
	void scanFastaThreads(int ithreadCount);

private:
	Options *opt;
	std::istream *input;
	std::ostream *output;

};

}


#endif /* SOURCE_INCLUDE_IDENTIFY_H_ */
