/*
 * options.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: pjarnot
 */

#include "include/options.h"
#include "include/debug.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <cstring>

#include <iostream>

using namespace std;

void Options::showHelp() {
	switch (methodMode) {
	case MethodModes::NONE:
		showGeneralHelp();
		break;
	case MethodModes::IDENTIFY:
		showIdentifyHelp();
		break;
	case MethodModes::CLUSTER:
		showClusterHelp();
		break;
	case MethodModes::SEARCH:
		showSearchHelp();
		break;
	}
}

void Options::showGeneralHelp()
{
    cout << "Usage: gbsc <command> [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "These are GBSC commands:\n";
    cout << "   identify     Identify short tandem repeats in fasta formatted file.\n";
    cout << "   cluster      Cluster a protein dataset in fasta format.\n";
    cout << "   search       Search for similar protein sequence to query.\n";
    cout << "   help         Show this help page.\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
}


void Options::showAlgorithmParameters() {
    cout << "Algorithm parameters:\n";
    cout << "  -w, --weight-threshold=THRESHOLD\n";
    cout << "                             Weight threshold. Default: " << weightThreshold << "\n";
    cout << "  -l, --lifetime=THRESHOLD\n";
    cout << "                             Lifetime. Default: " << lifetime << "\n";
    cout << "  -g, --max-gap-len=THRESHOLD\n";
    cout << "                             Maximal accepted gap length in between repetitions (-1 = off). Default: " << maxGapLength << "\n";
    cout << "  -m, --min-node-count=THRESHOLD\n";
    cout << "                             Minimal count of nodes in STR (-1 = off). Default: " << minNodeCount << "\n";
    cout << "  -x, --max-node-count=THRESHOLD\n";
    cout << "                             Maximal count of nodes in STR (-1 = off). Default: " << maxNodeCount << "\n";
    cout << "  -h, --filter-homopolymers\n";
    cout << "                             If this flag is set, homopolymers will be filtered out from results.\n";
    cout << "                               Default: " << filterHomopolymers << "\n";
    cout << "  -n, --include-orphan-nodes\n";
    cout << "                             If this flag is set, orphan nodes will be included to cycles.\n";
    cout << "                               Default: " << includeOrphanNodes << "\n";
    cout << "  -a, --alphabet-reduction\n";
    cout << "                             This option reduces alphabet when creating model.\n";
    cout << "                               Possible values are:\n";
    cout << "                                   NONE - it takes residues as they are\n";
    cout << "                                   Wang1999 - reduces residues to five letter alphabet.\n";
    cout << "                                              For details see: doi.org/10.1038/14918\n";
    cout << "                               Default: NONE\n";
}

void Options::showIdentifyHelp() {
    cout << "Usage: gbsc identify [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "Input and output:\n";
    cout << "  -i, --input-file=FILE      Input protein database. If not specified, stdin\n";
    cout << "                               will be used\n";
    cout << "  -o, --output-file=FILE     Output file for lcr identification. If not specified,\n";
    cout << "                               stdout will be used\n";
    cout << "      --identify-output-format=FORMAT\n";
    cout << "                             Output format for LCR identification, possible options:\n";
    cout << "                               0 - Intervals - SEG like output (default)\n";
    cout << "                               1 - Intervals enchanced - SEG like with types of repeats\n";
    cout << "                               2 - STRs in lowercase\n";
    cout << "                               3 - Fasta\n";
    cout << "                               4 - Fasta STRs\n";
    cout << "      --print-lcr-only       If this flag is set only proteins that contain LCRs\n";
    cout << "                               will be displayed.\n";
    cout << "\n";
    showAlgorithmParameters();
    cout << "\n";
    cout << "Multi-threading:\n";
    cout << "  -t, --threads=NUM          Number of threads in thread pool (0: all available, -1: single).\n";
    cout << "                               Default: " << threadCount << "\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
}


void Options::showClusterHelp() {
    cout << "Usage: gbsc cluster [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "Input and output:\n";
    cout << "  -i, --input-file=FILE      Input protein database. If not specified, stdin\n";
    cout << "                               will be used\n";
    cout << "  -o, --output-file=FILE     Output file for lcr identification. If not specified,\n";
    cout << "                               stdout will be used\n";
    cout << "      --clusters-dir=DIR     Output directory for clusters. The user should make\n";
    cout << "                               sure the directory is empty. If not the software will\n";
    cout << "                               append new results to already existing clusters.\n";
    cout << "                               If this option is not set, GBSC will identify LCRs\n";
    cout << "\n";
    showAlgorithmParameters();
    cout << "      --max-linked-str-gap=NUM\n";
    cout << "                             Determines maximal gap length between linked STRs.\n";
    cout << "                               Default: " << maxLinkedStrsGap << ". Set it to negative to disable.\n";
    cout << "\n";
    cout << "Multi-threading:\n";
    cout << "  -t, --threads=NUM          Number of threads in thread pool (0: all available, -1: single).\n";
    cout << "                               Default: " << threadCount << "\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
}


void Options::showSearchHelp() {
    cout << "Usage: gbsc search [options]\n";
    cout << "\n";
    cout << "Mandatory arguments to long options are mandatory for short options too.\n";
    cout << "\n";
    cout << "Input and output:\n";
    cout << "  -i, --input-file=FILE      Input protein database. If not specified, stdin\n";
    cout << "                               will be used\n";
    cout << "      --query-file=FILE      Input protein sequence in fasta format. If not specified, stdin\n";
    cout << "                               will be used. Cannot us input-file and query-file as stdin\n";
    cout << "                               at the same time.\n";
    cout << "  -o, --output-file=FILE     Output file for lcr identification. If not specified,\n";
    cout << "                               stdout will be used\n";
    cout << "      --search-output-format=FORMAT\n";
    cout << "                             Output format:\n";
    cout << "                               0 - Human.\n";
    cout << "                               1 - JSON\n";
    cout << "      --max-hit-count=COUNT  Maximal number of hits in output.\n";
    cout << "      --clusters-dir=DIR     Input directory for clusters.\n";
    cout << "\n";
    showAlgorithmParameters();
    cout << "\n";
    cout << "Multi-threading:\n";
    cout << "  -t, --threads=NUM          Number of threads in thread pool (0: all available, -1: single).\n";
    cout << "                               Default: " << threadCount << "\n";
    cout << "\n";
    cout << "Miscellaneous:\n";
    cout << "      --help                 Show this help message and exit\n";
    cout << "      --version              Output version information and exit\n";
}


MethodModes readMode(char *imode) {
	if (strcmp(imode, "identify") == 0) {
		return MethodModes::IDENTIFY;
	}
	else if (strcmp(imode, "cluster") == 0) {
		return MethodModes::CLUSTER;
	}
	else if (strcmp(imode, "search") == 0) {
		return MethodModes::SEARCH;
	}
	return MethodModes::NONE;
}


int Options::parseOptions(int argc, char **argv)
{
	int retval = 0;

    if (argc == 1) {
		showHelp();
		return -1;
    }

    methodMode = readMode(argv[1]);

    if (methodMode == MethodModes::NONE) {
		showHelp();
		return -1;
    }
    if (argc > 2 && (strcmp(argv[2], "help") == 0)) {
		showHelp();
		return -1;
    }

	switch (methodMode) {
	case MethodModes::NONE:
		break;
	case MethodModes::IDENTIFY:
		retval = parseIdentifyOptions(argc, argv);
		break;
	case MethodModes::CLUSTER:
		retval = parseClusterOptions(argc, argv);
		break;
	case MethodModes::SEARCH:
		retval = parseSearchOptions(argc, argv);
		break;
	}

    return retval;
}

int Options::parseIdentifyOptions(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"input-file",     required_argument, 0,  'i' },
            {"output-file",     required_argument, 0,  'o' },
            {"weight-threshold",     required_argument, 0,  'w' },
            {"lifetime",     required_argument, 0,  'l' },
            {"max-gap-len",     required_argument, 0,  'g' },
            {"min-node-count",     required_argument, 0,  'm' },
            {"max-node-count",     required_argument, 0,  'x' },
            {"filter-homopolymers",     no_argument, 0,  'h' },
            {"include-orphan-nodes",     no_argument, 0,  'n' },
            {"threads",     required_argument, 0,  't' },
            {"identify-output-format",     required_argument, 0,  0 },
            {"print-lcr-only",     no_argument, 0,  0 },
            {"alphabet-reduction",     required_argument, 0,  'a' },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

       c = getopt_long(argc, argv, "i:o:w:l:t:g:m:x:hna:",
                 long_options, &option_index);

        if (c == -1)
        	break;

       switch (c) {
        case 0:
        	if (strcmp(long_options[option_index].name, "help") == 0)
        	{
        		showHelp();
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "version") == 0)
        	{
        		cout << "version: 0.0.1";
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "identify-output-format") == 0)
        	{
        		setIdentifyOutputFormat(atoi(optarg));
        	}
        	else if (strcmp(long_options[option_index].name, "print-lcr-only") == 0)
        	{
        		printProtsWithLcrsOnly = true;
        	}
            break;

       case 'i':
            inputFilePath = optarg;
            break;

       case 'a':
            alphabetReduction = optarg;
            break;

       case 'o':
            outputFilePath = optarg;
            break;

       case 'w':
            weightThreshold = atoi(optarg);
            break;

       case 'l':
            lifetime = atoi(optarg);
            break;

       case 'g':
            maxGapLength = atoi(optarg);
            break;

       case 'm':
            minNodeCount = atoi(optarg);
            break;

       case 'x':
            maxNodeCount = atoi(optarg);
            break;

       case 'h':
            filterHomopolymers = true;
            break;

       case 'n':
            includeOrphanNodes = true;
            break;

       case 't':
            threadCount = atoi(optarg);
            break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}

int Options::parseClusterOptions(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"input-file",     required_argument, 0,  'i' },
            {"output-file",     required_argument, 0,  'o' },
            {"clusters-dir",     required_argument, 0,  0 },
            {"weight-threshold",     required_argument, 0,  'w' },
            {"lifetime",     required_argument, 0,  'l' },
            {"max-gap-len",     required_argument, 0,  'g' },
            {"min-node-count",     required_argument, 0,  'm' },
            {"max-node-count",     required_argument, 0,  'x' },
            {"filter-homopolymers",     no_argument, 0,  'h' },
            {"include-orphan-nodes",     no_argument, 0,  'n' },
            {"max-linked-strs-gap",     required_argument, 0,  0 },
            {"threads",     required_argument, 0,  't' },
            {"alphabet-reduction",     required_argument, 0,  'a' },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

       c = getopt_long(argc, argv, "i:o:w:l:t:g:m:x:hna:",
                 long_options, &option_index);

        if (c == -1)
        	break;

       switch (c) {
        case 0:
        	if (strcmp(long_options[option_index].name, "help") == 0)
        	{
        		showHelp();
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "version") == 0)
        	{
        		cout << "version: 0.0.1";
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "clusters-dir") == 0)
        	{
				clustersDirPath = optarg;
        	}
        	else if (strcmp(long_options[option_index].name, "max-linked-strs-gap") == 0)
        	{
				maxLinkedStrsGap = atoi(optarg);
        	}
            break;


       case 'i':
            inputFilePath = optarg;
            break;

       case 'a':
            alphabetReduction = optarg;
            break;

       case 'o':
            outputFilePath = optarg;
            break;

       case 'w':
            weightThreshold = atoi(optarg);
            break;

       case 'l':
            lifetime = atoi(optarg);
            break;

       case 'g':
            maxGapLength = atoi(optarg);
            break;

       case 'm':
            minNodeCount = atoi(optarg);
            break;

       case 'x':
            maxNodeCount = atoi(optarg);
            break;

       case 'h':
            filterHomopolymers = true;
            break;

       case 'n':
            includeOrphanNodes = true;
            break;

       case 't':
            threadCount = atoi(optarg);
            break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}

int Options::parseSearchOptions(int argc, char **argv) {
    int c;
   while (1)
   {
        int option_index = 0;
        static struct option long_options[] = {
            {"input-file",     required_argument, 0,  'i' },
            {"query-file",     required_argument, 0,  0 },
            {"output-file",     required_argument, 0,  'o' },
            {"search-output-format",     required_argument, 0,  0 },
            {"clusters-dir",     required_argument, 0,  0 },
            {"weight-threshold",     required_argument, 0,  'w' },
            {"lifetime",     required_argument, 0,  'l' },
            {"max-gap-len",     required_argument, 0,  'g' },
            {"min-node-count",     required_argument, 0,  'm' },
            {"max-node-count",     required_argument, 0,  'x' },
            {"max-hit-count",     required_argument, 0,  0 },
            {"filter-homopolymers",     no_argument, 0,  'h' },
            {"include-orphan-nodes",     no_argument, 0,  'n' },
            {"threads",     required_argument, 0,  't' },
            {"alphabet-reduction",     required_argument, 0,  'a' },
            {"help",    no_argument,       0,  0 },
            {"version",    no_argument,       0,  0 },
            {0,         0,                 0,  0 }
        };

       c = getopt_long(argc, argv, "i:o:w:l:t:g:m:x:hna:",
                 long_options, &option_index);

        if (c == -1)
        	break;

       switch (c) {
        case 0:
        	if (strcmp(long_options[option_index].name, "help") == 0)
        	{
        		showHelp();
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "version") == 0)
        	{
        		cout << "version: 0.0.1";
        		return -1;
        	}
        	else if (strcmp(long_options[option_index].name, "clusters-dir") == 0)
        	{
				clustersDirPath = optarg;
        	}
        	else if (strcmp(long_options[option_index].name, "query-file") == 0)
        	{
				inputQueryFilePath = optarg;
        	}
        	else if (strcmp(long_options[option_index].name, "search-output-format") == 0)
        	{
        		setSearchOutputFormat(atoi(optarg));
        	}
        	else if (strcmp(long_options[option_index].name, "max-hit-count") == 0)
        	{
				maxHitCount = atoi(optarg);
        	}
            break;

       case 'i':
            inputFilePath = optarg;
            break;

       case 'a':
            alphabetReduction = optarg;
            break;

       case 'o':
            outputFilePath = optarg;
            break;

       case 'w':
            weightThreshold = atoi(optarg);
            break;

       case 'l':
            lifetime = atoi(optarg);
            break;

       case 'g':
            maxGapLength = atoi(optarg);
            break;

       case 'm':
            minNodeCount = atoi(optarg);
            break;

       case 'x':
            maxNodeCount = atoi(optarg);
            break;

       case 'h':
            filterHomopolymers = true;
            break;

       case 'n':
            includeOrphanNodes = true;
            break;

       case 't':
            threadCount = atoi(optarg);
            break;

       case '?':
            break;

       default:
            printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
	return 0;
}
