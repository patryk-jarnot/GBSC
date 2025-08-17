/*
 * cluster.h
 *
 *  Created on: Nov 2, 2021
 *      Author: pjarnot
 */

#ifndef SOURCE_INCLUDE_CLUSTER_H_
#define SOURCE_INCLUDE_CLUSTER_H_


#include "include/options.h"

#include <iostream>


namespace cluster {

class Cluster {
public:
	Cluster(Options *iopt, std::istream *iinput, std::ostream *ioutput);
	~Cluster();

	void scanFasta();
	void scanFastaThreads(int ithreadCount);

private:
	Options *opt;
	std::istream *input;
	std::ostream *output;

};

}


#endif /* SOURCE_INCLUDE_CLUSTER_H_ */
