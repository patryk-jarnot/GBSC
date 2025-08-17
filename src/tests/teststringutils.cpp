/*
 * teststringutils.cpp
 *
 *  Created on: Dec 12, 2023
 *      Author: pjarnot
 */

#include "include/debug.h"
#include "include/stringutils.h"

#include "assert.h"

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;


void test_split_by_new_line() {
	vector<string> items = strutils::split("asdf\nzxcv", "\n");

	assert(items.size() == 2);
	assert(items[0].compare("asdf") == 0);
	assert(items[1].compare("zxcv") == 0);
}


int main(int argc, char** argv)
{
    cout << "Test search" << endl;
    test_split_by_new_line();
	cout << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}



