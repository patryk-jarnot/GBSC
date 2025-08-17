/*
 * output.cpp
 *
 *  Created on: Feb 11, 2020
 *      Author: pjarnot
 */


#include "include/output.h"
#include "include/similaritysearch.h"

#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <mutex>
#include <limits>

std::mutex output_mutex;
std::mutex output_file_mutex;



void output::print_search_result_json(std::ostream *output, std::vector<similaritysearch::search_result_query_t> *isearchResultsQueries, int max_count) {
	*output << "{\"method\": \"GBSC\", \"queries\": [";
	bool firstQuery = true;
	for (auto srq : *isearchResultsQueries) {
		if (firstQuery) {
			firstQuery = false;
		}
		else {
			*output << ",";
		}
		*output << "{ \"header\": \"" << srq.queryHeader << "\"";
		*output << ", \"sequence\": \"" << srq.querySequence << "\"";
		*output << ", \"begin\": " << srq.begin << "";
		*output << ", \"end\": " << srq.end << "";
		*output << ", \"hits\": [";

		bool firstHit = true;
		std::sort(srq.hits.rbegin(), srq.hits.rend());
		int hit_count = max_count == -1 ? (int)srq.hits.size() : std::min((int)srq.hits.size(), max_count);
		for (int i=0; i<hit_count; i++){
			similaritysearch::search_result_hit_t *srh = &(srq.hits[i]);
			if (firstHit) {
				firstHit = false;
			}
			else {
				*output << ",";
			}
			*output << "{ \"header\": \"" << srh->hitHeader << "\"";
			*output << ", \"sequence\": \"" << srh->hitSequence << "\"";
			*output << ", \"begin\": " << srh->begin << "";
			*output << ", \"end\": " << srh->end << "";
			*output << ", \"score\": " << srh->score << "";
			*output << "}";
		}
		*output << "]}";
	}
	*output << "]}\n";
}

void output::print_search_result_human(std::ostream *output, std::vector<similaritysearch::search_result_query_t> *isearchResultsQueries, int max_count) {
	// acquiring output_mutex here will cause double acquire and lock of thread while searching
	for (auto srq : *isearchResultsQueries) {
		for (auto srh : srq.hits) {
			*output << " query: " << srq.queryHeader << "\n";
			*output << " query: " << srq.querySequence << "\n";
			*output << "   hit: " << srh.hitSequence << "\n";
			*output << "   hit: " << srh.hitHeader << "\n";
			*output << " score: " << srh.score << "\n";
			*output << "\n";
			*output << srq.queryCycle.getGraph().drawGraph() << "\n";
		}
	}
}

void output::print_search_results(std::ostream *output, SearchOutputFormat format, std::vector<similaritysearch::search_result_query_t> isearchResultsQueries, int max_count) {
	if (format == SearchOutputFormat::HUMAN) {
		print_search_result_human(output, &isearchResultsQueries, max_count);
	}
	else if (format == SearchOutputFormat::JSON) {
		print_search_result_json(output, &isearchResultsQueries, max_count);
	}
	else {
		throw "Not implemented";
	}
}


void output::print_intervals(std::ostream *output, std::string &iheader, std::vector<graph::Cycle> &icycles) {
	std::lock_guard<std::mutex> guard(output_mutex);
	*output << iheader << "\n";

	for (auto c : icycles)
	{
		*output << c.getBegin() << " - " << c.getEnd() << "\n";
	}
}


void output::print_intervals_enriched(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles) {
	std::lock_guard<std::mutex> guard(output_mutex);
	*output << iheader << "\n";

	for (auto c : icycles)
	{
		*output << c.getBegin() << " - " << c.getEnd() << " |" << c.getGraph().getAminoacids() << "\n";
	}
}


void output::print_masked_lower_case(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles, std::string isequence) {
	std::lock_guard<std::mutex> guard(output_mutex);
	*output << iheader << "\n";

	for (auto c : icycles)
	{
		std::transform(isequence.begin() + c.getBegin() - 1, isequence.begin() + c.getEnd(), isequence.begin() + c.getBegin() - 1,
		    [](unsigned char c){ return std::tolower(c); });
	}
	*output << isequence << "\n";
}

void output::print_fasta_str(std::ostream *output, const std::string &iheader, std::vector<graph::Cycle> &icycles, std::string isequence) {
	std::lock_guard<std::mutex> guard(output_mutex);

	for (auto c : icycles)
	{
		*output << iheader << '|' << c.getBegin() << '|' << c.getEnd() << '|' << c.to_string() << "\n";
		*output << isequence.substr(c.getBegin()-1, c.getEnd() - c.getBegin() + 1) << "\n";
	}
}


void output::print_fasta(std::ostream *output, const std::string &iheader, const std::string &isequence) {
	std::lock_guard<std::mutex> guard(output_mutex);
	*output << iheader << "\n";
	*output << isequence << "\n";
}


void output::print_lcr_identification(std::ostream *ioutput, fasta::Sequence &isequence, std::vector<graph::Cycle> &icycles, IdentifyOutputFormat ioutputFormat, bool printProtsWithLcrsOnly) {
	if (printProtsWithLcrsOnly && icycles.size() == 0) {
		return;
	}

	switch (ioutputFormat) {
	case IdentifyOutputFormat::INTERVALS:
		output::print_intervals(ioutput, isequence.header, icycles);
		break;
	case IdentifyOutputFormat::INTERVALS_ENRICHED:
		output::print_intervals_enriched(ioutput, isequence.header, icycles);
		break;
	case IdentifyOutputFormat::SEQUENCE_LOWER_CASE:
		output::print_masked_lower_case(ioutput, isequence.header, icycles, isequence.sequence);
		break;
	case IdentifyOutputFormat::FASTA:
		output::print_fasta(ioutput, isequence.header, isequence.sequence);
		break;
	case IdentifyOutputFormat::FASTA_STR:
		output::print_fasta_str(ioutput, isequence.header, icycles, isequence.sequence);
		break;
	}
}


void save_cycle_chain(std::string ioutputDir, fasta::Sequence &isequence, std::vector<graph::Cycle> &cycleChain) {
	std::string graphStr = "";
	int begin = std::numeric_limits<int>::max();
	int end = std::numeric_limits<int>::min();

	for (auto c : cycleChain)
	{
		if (graphStr.empty()) {
			graphStr = c.to_string();
		}
		else {
			graphStr += "~";
			graphStr += c.to_string();
		}
		if (c.getBegin() < begin) {
			begin = c.getBegin();
		}
		if (c.getEnd() > end) {
			end = c.getEnd();
		}
	}

	std::string outputPath = ioutputDir + "/";
	outputPath += graphStr;
	outputPath += ".fasta";
	std::lock_guard<std::mutex> guard(output_file_mutex);
	std::ofstream ofs(outputPath, std::ios_base::app);
	ofs << isequence.header << '|' << begin << '|' << end << '|' << graphStr << "\n";
	ofs << isequence.sequence.substr(begin - 1, end - begin + 1) << "\n";
}


bool compareCycles(graph::Cycle ileftCycle, graph::Cycle irightCycle) {
	return ileftCycle.getBegin() < irightCycle.getBegin();
}


void save_linked_str_clusters(std::string ioutputDir, fasta::Sequence &isequence, std::vector<graph::Cycle> icycles, int maxLinkedStrsGap) {
	sort(icycles.begin(), icycles.end(), compareCycles);
	for (size_t i=0; i<icycles.size(); i++) {
		std::vector<graph::Cycle> cycleChain;
		cycleChain.push_back(icycles[i]);

		for (size_t j=i+1; j<icycles.size(); j++) {
			if (((icycles[j].getBegin() - cycleChain.back().getEnd()) < maxLinkedStrsGap) &&
					((cycleChain.back().getEnd() - icycles[j].getBegin()) < maxLinkedStrsGap)) {
				cycleChain.push_back(icycles[j]);
				save_cycle_chain(ioutputDir, isequence, cycleChain);
			}
		}
	}
}


void output::save_clusters(std::string ioutputDir, fasta::Sequence &isequence, std::vector<graph::Cycle> &icycles, int maxLinkedStrsGap) {
	for (auto c : icycles)
	{
		std::string outputPath = ioutputDir + "/";
		outputPath += c.to_string();
		outputPath += ".fasta";
		std::lock_guard<std::mutex> guard(output_file_mutex);
		std::ofstream ofs(outputPath, std::ios_base::app);
//		ofs << isequence.header << " LCR:begin=" << c.getBegin() << ", end=" << c.getEnd() << "\n";
		ofs << isequence.header << '|' << c.getBegin() << '|' << c.getEnd() << '|' << c.to_string() << "\n";
		ofs << isequence.sequence.substr(c.getBegin() - 1, c.getEnd() - c.getBegin() + 1) << "\n";
	}
	if (maxLinkedStrsGap >= 0) {
		save_linked_str_clusters(ioutputDir, isequence, icycles, maxLinkedStrsGap);
	}
}
