/*
 * testalphabet.cpp
 *
 *  Created on: Jul 25, 2022
 *      Author: pjarnot
 */

#include "include/alphabet.h"

#include "assert.h"
#include <iostream>

using namespace std;
using namespace alphabet;


void test_do_not_reduce_alphabet_char() {
	Alphabet a;

	assert(a.reduceResidue('G') == 'G');
	assert(a.reduceResidue('A') == 'A');
	assert(a.reduceResidue('V') == 'V');
	assert(a.reduceResidue('L') == 'L');
	assert(a.reduceResidue('I') == 'I');
	assert(a.reduceResidue('P') == 'P');
	assert(a.reduceResidue('F') == 'F');
	assert(a.reduceResidue('Y') == 'Y');
	assert(a.reduceResidue('W') == 'W');
	assert(a.reduceResidue('S') == 'S');
	assert(a.reduceResidue('T') == 'T');
	assert(a.reduceResidue('C') == 'C');
	assert(a.reduceResidue('M') == 'M');
	assert(a.reduceResidue('N') == 'N');
	assert(a.reduceResidue('Q') == 'Q');
	assert(a.reduceResidue('D') == 'D');
	assert(a.reduceResidue('E') == 'E');
	assert(a.reduceResidue('K') == 'K');
	assert(a.reduceResidue('R') == 'R');
	assert(a.reduceResidue('H') == 'H');

	assert(a.reduceResidue('X') == 'X');
}


void test_do_not_reduce_alphabet_string() {
	Alphabet a;

	assert(a.reduceSequence("ALA MA KOTA").compare("ALA MA KOTA") == 0);
}


void test_reduce_alphabet_char_with_li_table() {
	Alphabet a;
	a.setReductionTable(ReductionSet::LI_2003);

	assert(a.reduceResidue('G') == 'A');
	assert(a.reduceResidue('A') == 'A');
	assert(a.reduceResidue('V') == 'A');
	assert(a.reduceResidue('L') == 'A');
	assert(a.reduceResidue('I') == 'A');
	assert(a.reduceResidue('P') == 'A');

	assert(a.reduceResidue('F') == 'B');
	assert(a.reduceResidue('Y') == 'B');
	assert(a.reduceResidue('W') == 'B');

	assert(a.reduceResidue('S') == 'C');
	assert(a.reduceResidue('T') == 'C');
	assert(a.reduceResidue('C') == 'C');
	assert(a.reduceResidue('M') == 'C');
	assert(a.reduceResidue('N') == 'C');
	assert(a.reduceResidue('Q') == 'C');

	assert(a.reduceResidue('D') == 'D');
	assert(a.reduceResidue('E') == 'D');

	assert(a.reduceResidue('K') == 'E');
	assert(a.reduceResidue('R') == 'E');
	assert(a.reduceResidue('H') == 'E');

	assert(a.reduceResidue('X') == 'X');
}


void test_reduce_alphabet_string_with_li_table() {
	Alphabet a;
	a.setReductionTable(ReductionSet::LI_2003);

	assert(a.reduceSequence("ALA MA KOTA").compare("AAA CA EOCA") == 0);
}


void test_reduce_alphabet_char_with_wang_table() {
	Alphabet a;

	a.setReductionTable(ReductionSet::WANG_1999);

	assert(a.reduceResidue('C') == 'A');
	assert(a.reduceResidue('M') == 'A');
	assert(a.reduceResidue('F') == 'A');
	assert(a.reduceResidue('I') == 'A');
	assert(a.reduceResidue('L') == 'A');
	assert(a.reduceResidue('V') == 'A');
	assert(a.reduceResidue('W') == 'A');
	assert(a.reduceResidue('Y') == 'A');

	assert(a.reduceResidue('A') == 'B');
	assert(a.reduceResidue('T') == 'B');
	assert(a.reduceResidue('H') == 'B');

	assert(a.reduceResidue('G') == 'C');
	assert(a.reduceResidue('P') == 'C');

	assert(a.reduceResidue('D') == 'D');
	assert(a.reduceResidue('E') == 'D');

	assert(a.reduceResidue('S') == 'E');
	assert(a.reduceResidue('N') == 'E');
	assert(a.reduceResidue('Q') == 'E');
	assert(a.reduceResidue('R') == 'E');
	assert(a.reduceResidue('K') == 'E');

	assert(a.reduceResidue('X') == 'X');
}


void test_reduce_alphabet_string_with_wang_table() {
	Alphabet a;

	a.setReductionTable(ReductionSet::WANG_1999);

	assert(a.reduceSequence("ALA MA KOTA").compare("BAB AB EOBB") == 0);
}


int main(int argc, char** argv)
{
    cout << "Test alphabet" << endl;
    test_do_not_reduce_alphabet_char();
    test_do_not_reduce_alphabet_string();

    test_reduce_alphabet_char_with_wang_table();
    test_reduce_alphabet_string_with_wang_table();

    test_reduce_alphabet_char_with_li_table();
    test_reduce_alphabet_string_with_li_table();
	cout << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}



