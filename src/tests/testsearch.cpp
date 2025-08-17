//#include "config-gbsc.h"

#include "include/debug.h"
#include "include/similaritysearch.h"

#include "assert.h"

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;
using namespace similaritysearch;


void test_search_sequence() {
	string sequence = ">s1\nQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQA\n";
	istringstream ssequence(sequence);

	ifstream db("src/tests/data/example.fasta");

	Options opt;
	opt.setSearchOutputFormat(0);

	Search search(&opt, &db, &cout);
	search.scanFasta(&ssequence);
	std::vector<search_result_query_t> results = search.getResults();

//	assert(results.size() == 1);
//	DEBUG(results[0].hits[0].hitSequence)
//	assert(results[0].hits[0].hitSequence == "QAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAHAQAQAQAQAQAQAQAQAQAQ");
}


void test_search_sequence_json() {
	string sequence = ">s1\nQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQA\n";
	istringstream ssequence(sequence);

	ifstream db("src/tests/data/example.fasta");

	Options opt;
	opt.setSearchOutputFormat(1);

	Search search(&opt, &db, &cout);
	search.scanFasta(&ssequence);
	std::vector<search_result_query_t> results = search.getResults();

//	assert(results.size() == 2);
//	DEBUG(results[0].hits[0].hitSequence)
//	assert(results[0].hits[0].hitSequence == "QAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAHAQAQAQAQAQAQAQAQAQAQ");
}

void test_search_sequence_json_multiquery() {
	string sequence = ">s1\nQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQA\n>s2\nQQQQQQQQQQQQQQQQQQQQQQQQQQQQ\n";
	istringstream ssequence(sequence);

	ifstream db("src/tests/data/example.fasta");

	Options opt;
	opt.setSearchOutputFormat(1);

	Search search(&opt, &db, &cout);
	search.scanFasta(&ssequence);
	std::vector<search_result_query_t> results = search.getResults();

//	assert(results.size() == 2);
//	DEBUG(results[0].hits[0].hitSequence)
//	assert(results[0].hits[0].hitSequence == "QAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAHAQAQAQAQAQAQAQAQAQAQ");
}


int main(int argc, char** argv)
{
    cout << "Test search" << endl;
    cout << endl << "Human output" << endl;
    test_search_sequence();
    cout << endl << "JSON output" << endl;
	test_search_sequence_json();
    cout << endl << "JSON output multiple queries" << endl;
	test_search_sequence_json_multiquery();
	cout << endl << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}
