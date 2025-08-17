/*
 * main.cpp
 *
 *  Created on: Jun 12, 2019
 *      Author: pjarnot
 */

#include "include/options.h"
#include "include/fasta.h"
#include "include/gbsc.h"
#include "include/output.h"
#include "include/cluster.h"
#include "include/identify.h"
#include "include/similaritysearch.h"

#include "assert.h"

#include <iostream>

using namespace std;

istream *getQueryInput(Options &opt)
{
	if (opt.getInputQueryFilePath().length() > 0)
	{
		return new ifstream(opt.getInputQueryFilePath());
	}
	else if (opt.getInputFilePath().length() > 0)
	{
		return &cin;
	}
	else {
		return nullptr;
	}
}

istream *getInput(Options &opt)
{
	if (opt.getInputFilePath().length() > 0)
	{
		return new ifstream(opt.getInputFilePath());
	}
	else
	{
		return &cin;
	}
}


ostream *getOutput(Options &opt)
{
	if (opt.getOutputFilePath().length() > 0)
	{
		return new ofstream(opt.getOutputFilePath());
	}
	else
	{
		return &cout;
	}
}


int main(int argc, char **argv)
{
	Options opt;
	int status = opt.parseOptions(argc, argv);
	if (status < 0)
		return status;

	istream *input = getInput(opt);
	ostream *output = getOutput(opt);

	if (opt.getMethodMode() == MethodModes::IDENTIFY) {
		identify::Identify ident(&opt, input, output);
		if (opt.getThreadCount() >= 0) {
			ident.scanFastaThreads(opt.getThreadCount());
		}
		else {
			ident.scanFasta();
		}
	}
	else if (opt.getMethodMode() == MethodModes::CLUSTER) {
		cluster::Cluster cluster(&opt, input, output);
		if (opt.getThreadCount() >= 0) {
			cluster.scanFastaThreads(opt.getThreadCount());
		}
		else {
			cluster.scanFasta();
		}
	}
	else if (opt.getMethodMode() == MethodModes::SEARCH) {
		istream *queryInput = getQueryInput(opt);
		if (queryInput == nullptr) {
			cerr << "Input and Query cannot be both set to stdin at the same time\n";
			opt.showHelp();
			return -1;
		}
//		cout << "searching...\n";
		similaritysearch::Search search(&opt, input, output);

		if (opt.getThreadCount() >= 0) {
			search.scanFastaThreads(queryInput, opt.getThreadCount());
		}
		else {
			search.scanFasta(queryInput);
		}
	}

	if(ofstream* outFile = dynamic_cast<ofstream*>(output)) {
		outFile->close();
		delete outFile;
	}
	if(ifstream* inFile = dynamic_cast<ifstream*>(input)) {
		inFile->close();
		delete inFile;
	}

	return 0;
}


