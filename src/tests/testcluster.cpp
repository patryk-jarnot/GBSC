/*
 * testcluster.cpp
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */


#include "include/cluster.h"
#include "include/options.h"
#include "include/file.h"
#include "include/stringutils.h"

#include "assert.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace cluster;


void test_cluster_multiple_adjacent_fragments(string root_path) {
	string sequence = ">header\nAAAAAAAAAACCCCCCCCCCDDDDDDDD";
	string dir_path = root_path + "/src/tests/output/adjacent_clusters";
	assert(false != file::is_path_exists(dir_path));
	stringstream ss;
	ss << sequence;
	ofstream null("/dev/null");
	Options opt;
	opt.setClustersDirPath(dir_path);
	Cluster cluster(&opt, &ss, &null);

	cluster.scanFasta();

	string file_content = file::read_file(dir_path + "/AA-AA~CC-CC~DD-DD.fasta");
	vector<string> items = strutils::split(file_content, "\n");
	file::delete_files(dir_path + "/*.fasta");
	assert(items.size() == 3);
	assert(items[0].rfind(">header", 0) == 0);
	assert(items[1].compare("AAAAAAAAAACCCCCCCCCCDDDDDDDD") == 0);
}

void test_cluster_multiple_and_repeated_adjacent_fragments(string root_path) {
	string sequence = ">header\nAAAAAAAAAACCCCCCCCCCAAAAAAAAAACCCCCCCCCCCCAAAAAAAAAAAAACCCCCCCCCCCCC";
	string dir_path = root_path + "/src/tests/output/adjacent_clusters";
	assert(false != file::is_path_exists(dir_path));
	stringstream ss;
	ss << sequence;
	ofstream null("/dev/null");
	Options opt;
	opt.setClustersDirPath(dir_path);
	Cluster cluster(&opt, &ss, &null);

	cluster.scanFasta();

	string file_content = file::read_file(dir_path + "/AA-AA~CC-CC~AA-AA~CC-CC~AA-AA~CC-CC.fasta");
	vector<string> items = strutils::split(file_content, "\n");
	file::delete_files(dir_path + "/*.fasta");
	assert(items.size() == 3);
	assert(items[0].rfind(">header", 0) == 0);
	assert(items[1].compare("AAAAAAAAAACCCCCCCCCCAAAAAAAAAACCCCCCCCCCCCAAAAAAAAAAAAACCCCCCCCCCCCC") == 0);
}


int main(int argc, char** argv)
{
	string root_path = string(argv[1]);
    cout << "Test cluster" << endl;
    test_cluster_multiple_adjacent_fragments(root_path);
    test_cluster_multiple_and_repeated_adjacent_fragments(root_path);
	cout << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}


