/*
 * testkmer.cpp
 *
 *  Created on: Jun 26, 2022
 *      Author: pjarnot
 */

#include "include/kmer.h"

#include "include/debug.h"

#include "assert.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <string>


using namespace std;
using namespace kmer;


void test_find_kmer() {
	string sequence = "QAQAQAQAQAQAQA\n";

	set<string> kmers;
	kmers.insert("QA");
	kmers.insert("AQ");

	map<string, int> countedKmers = findKmers(sequence, kmers);

	assert(countedKmers["QA"] == 6);
	assert(countedKmers["AQ"] == 6);
}


int main(int argc, char** argv)
{
    cout << "Test kmers" << endl;
    test_find_kmer();
	cout << "Test kmers passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}



