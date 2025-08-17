/*
 * output.h
 *
 *  Created on: Feb 11, 2020
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_OUTPUT_H_
#define GBSC_INCLUDE_OUTPUT_H_


#include "graph.h"
#include "similaritysearch.h"
#include "fasta.h"
#include "options.h"
#include <string>
#include <vector>


namespace output {


	void print_search_result_json(std::ostream *output, std::vector<similaritysearch::search_result_query_t> *isearchResultsQueries, int max_count);
	void print_search_result_human(std::ostream *output, std::vector<similaritysearch::search_result_query_t> *isearchResultsQueries, int max_count);
	void print_search_results(std::ostream *output, SearchOutputFormat format, std::vector<similaritysearch::search_result_query_t> isearchresults, int max_count);

	void print_intervals(std::ostream *output, std::string &iheader, std::vector<graph::Cycle> &icycles);
	void print_intervals_enriched(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles);
	void print_masked_lower_case(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles, std::string isequence);
	void print_fasta_str(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles, std::string isequence);
	void print_fasta(std::ostream *output, const std::string &iheader, const std::string &isequence);
	void print_lcr_identification(std::ostream *ioutput, fasta::Sequence &isequence, std::vector<graph::Cycle> &icycles, IdentifyOutputFormat ioutputFormat, bool printProtsWithLcrsOnly);

	void save_clusters(std::string ioutputDir, fasta::Sequence &isequence, std::vector<graph::Cycle> &icycles, int maxLinkedStrsGap);
}


#endif /* GBSC_INCLUDE_OUTPUT_H_ */
