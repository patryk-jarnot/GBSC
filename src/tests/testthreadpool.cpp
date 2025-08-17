/*
 * testthreadpool.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: pjarnot
 */

#include "include/threadpool.h"

#include <iostream>

using namespace std;



void test_threadpool_example() {
	test_threadpool();
}


int main(int argc, char** argv)
{
    cout << "Test threadpool" << endl;
    test_threadpool_example();
	cout << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}

