/*
 * options.h
 *
 *  Created on: Jun 14, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_OPTIONS_H_
#define GBSC_INCLUDE_OPTIONS_H_

#include <string>
#include <limits>


enum class IdentifyOutputFormat {
	INTERVALS = 0, INTERVALS_ENRICHED, SEQUENCE_LOWER_CASE, FASTA, FASTA_STR
};

enum class SearchOutputFormat {
	HUMAN = 0, JSON
};

enum class MethodModes {
	NONE = 0, IDENTIFY, CLUSTER, SEARCH
};


class Options
{
private:
	std::string inputFilePath;
	std::string outputFilePath;
	std::string clustersDirPath;
	int weightThreshold;
	int lifetime;
	IdentifyOutputFormat identifyOutputFormat;
	SearchOutputFormat searchOutputFormat;
	bool printProtsWithLcrsOnly;
	MethodModes methodMode;
	std::string inputQueryFilePath;
	int threadCount;
	int maxGapLength;
	int minNodeCount;
	int maxNodeCount;
	int maxHitCount;
	bool filterHomopolymers;
	bool includeOrphanNodes;
	int maxLinkedStrsGap;
	std::string alphabetReduction;

public:
	Options() : weightThreshold(3), lifetime(7), identifyOutputFormat(IdentifyOutputFormat::INTERVALS), searchOutputFormat(SearchOutputFormat::HUMAN), printProtsWithLcrsOnly(false), methodMode(MethodModes::NONE), threadCount(-1), maxGapLength(-1), minNodeCount(-1), maxNodeCount(-1), maxHitCount(-1), filterHomopolymers(false), includeOrphanNodes(false), maxLinkedStrsGap(3) {
		maxNodeCount = std::numeric_limits<int>::max();
	}
	virtual ~Options() {}

	int parseOptions(int argc, char **argv);
	int parseIdentifyOptions(int argc, char **argv);
	int parseClusterOptions(int argc, char **argv);
	int parseSearchOptions(int argc, char **argv);
	void showHelp();
	void showGeneralHelp();
	void showIdentifyHelp();
	void showClusterHelp();
	void showAlgorithmParameters();
	void showSearchHelp();

	void setClustersDirPath(std::string ipath){ clustersDirPath = ipath; }
	void setIdentifyOutputFormat(int iformat){ identifyOutputFormat = static_cast<IdentifyOutputFormat>(iformat); }
	void setSearchOutputFormat(int iformat){ searchOutputFormat = static_cast<SearchOutputFormat>(iformat); }

	std::string getInputFilePath() { return inputFilePath; }
	std::string getOutputFilePath() { return outputFilePath; }
	std::string getClustersDirPath() { return clustersDirPath; }
	int getWeightThreshold() { return weightThreshold; }
	int getLifetime() { return lifetime; }
	IdentifyOutputFormat getIdentifyOutputFormat() { return identifyOutputFormat; }
	SearchOutputFormat getSearchOutputFormat() { return searchOutputFormat; }
	bool isPrintProtsWithLcrsOnly() { return printProtsWithLcrsOnly; }
	MethodModes getMethodMode() { return methodMode; }
	std::string getInputQueryFilePath() { return inputQueryFilePath; }
	int getThreadCount() { return threadCount; }
	int getMaxGapLength() { return maxGapLength; }
	int getMinNodeCount() { return minNodeCount; }
	int getMaxNodeCount() { return maxNodeCount; }
	int getMaxHitCount() { return maxHitCount; }
	bool isFilterHomopolymers() { return filterHomopolymers; }
	bool isIncludeOrphanNodes() { return includeOrphanNodes; }
	int getMaxLinkedStrsGap() { return maxLinkedStrsGap; }
	std::string getAlphabetReduction() { return alphabetReduction; }
};


#endif /* GBSC_INCLUDE_OPTIONS_H_ */
