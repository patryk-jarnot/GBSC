/*
 * postprocess.h
 *
 *  Created on: Jan 28, 2022
 *      Author: pjarnot
 */

#ifndef SOURCE_INCLUDE_POSTPROCESS_H_
#define SOURCE_INCLUDE_POSTPROCESS_H_

#include "include/graph.h"

#include <string>
#include <vector>


namespace postprocess {

class Postprocess {
private:

public:
	Postprocess() {}
	std::vector<graph::Cycle> remove_long_gaps(std::vector<graph::Cycle> &icycles, int imaxGapAllowed, int iscoreThreshold);
	void filterHomopolymers(std::vector<graph::Cycle> &icycles, bool ifilterHomopolymers);
	void minMaxNodeCount(std::vector<graph::Cycle> &icycles, int iminNodeCount, int imaxNodeCount);
	void minStrLengthByNodeCount(std::vector<graph::Cycle> &icycles, int iweightThreshold);
};

}



#endif /* SOURCE_INCLUDE_POSTPROCESS_H_ */
