/*
 * alphabetreduction.cpp
 *
 *  Created on: Jul 25, 2022
 *      Author: pjarnot
 */


#include "include/alphabet.h"
#include "include/debug.h"

#include <algorithm>

using namespace alphabet;


Alphabet::Alphabet() : currentSet(ReductionSet::NONE) {
	setWang1999ReductionTable();
	setLi2003ReductionTable();
	setCollagenReductionTable();
	setDeReductionTable();
}


char Alphabet::reduceResidue(char iresidue) {
	switch (currentSet) {
	case ReductionSet::NONE:
		break;
	case ReductionSet::CUSTOM:
		return ' ';
	case ReductionSet::WANG_1999:
		if (wang1999ReductionTable.find(iresidue) != wang1999ReductionTable.end())
			return wang1999ReductionTable[iresidue];
		break;
	case ReductionSet::LI_2003:
		if (li2003ReductionTable.find(iresidue) != li2003ReductionTable.end())
			return li2003ReductionTable[iresidue];
		break;
	case ReductionSet::COLLAGEN:
		if (collagenReductionTable.find(iresidue) != collagenReductionTable.end()){
			return collagenReductionTable[iresidue];
		}
		break;
	case ReductionSet::DE:
		if (deReductionTable.find(iresidue) != deReductionTable.end()){
			return deReductionTable[iresidue];
		}
		break;
	}
	return iresidue;
}


std::string Alphabet::reduceSequence(std::string isequence) {
	for (size_t i=0; i< isequence.size(); i++) {
		isequence[i] = reduceResidue(isequence[i]);
	}
	return isequence;
}


void Alphabet::setAlphabet(std::string ialphabetSet) {
	std::transform(ialphabetSet.begin(), ialphabetSet.end(), ialphabetSet.begin(),
	    [](unsigned char c){ return std::tolower(c); });

	//DEBUG(ialphabetSet);

	if (ialphabetSet.compare("wang1999") == 0) {
		currentSet = ReductionSet::WANG_1999;
	}
	else if (ialphabetSet.compare("li2003") == 0) {
		currentSet = ReductionSet::LI_2003;
	}
	else if (ialphabetSet.compare("collagen") == 0) {
		//DEBUG("Changed current alphabet to collagen.");
		currentSet = ReductionSet::COLLAGEN;
	}
	else if (ialphabetSet.compare("de") == 0) {
		//DEBUG("Changed current alphabet to collagen.");
		currentSet = ReductionSet::DE;
	}
	else {
		currentSet = ReductionSet::NONE;
	}
}


void Alphabet::setReductionTable(ReductionSet iset) {
	currentSet = iset;
}


void Alphabet::setLi2003ReductionTable() {
	li2003ReductionTable['G'] = 'A';
	li2003ReductionTable['A'] = 'A';
	li2003ReductionTable['V'] = 'A';
	li2003ReductionTable['L'] = 'A';
	li2003ReductionTable['I'] = 'A';
	li2003ReductionTable['P'] = 'A';

	li2003ReductionTable['F'] = 'B';
	li2003ReductionTable['Y'] = 'B';
	li2003ReductionTable['W'] = 'B';

	li2003ReductionTable['S'] = 'C';
	li2003ReductionTable['T'] = 'C';
	li2003ReductionTable['C'] = 'C';
	li2003ReductionTable['M'] = 'C';
	li2003ReductionTable['N'] = 'C';
	li2003ReductionTable['Q'] = 'C';

	li2003ReductionTable['D'] = 'D';
	li2003ReductionTable['E'] = 'D';

	li2003ReductionTable['K'] = 'E';
	li2003ReductionTable['R'] = 'E';
	li2003ReductionTable['H'] = 'E';
}


void Alphabet::setCollagenReductionTable() {
	collagenReductionTable['G'] = 'G';
	collagenReductionTable['A'] = 'A';
	collagenReductionTable['V'] = 'A';
	collagenReductionTable['L'] = 'A';
	collagenReductionTable['I'] = 'A';
	collagenReductionTable['P'] = 'A';

	collagenReductionTable['F'] = 'A';
	collagenReductionTable['Y'] = 'A';
	collagenReductionTable['W'] = 'A';

	collagenReductionTable['S'] = 'A';
	collagenReductionTable['T'] = 'A';
	collagenReductionTable['C'] = 'A';
	collagenReductionTable['M'] = 'A';
	collagenReductionTable['N'] = 'A';
	collagenReductionTable['Q'] = 'A';

	collagenReductionTable['D'] = 'A';
	collagenReductionTable['E'] = 'A';

	collagenReductionTable['K'] = 'A';
	collagenReductionTable['R'] = 'A';
	collagenReductionTable['H'] = 'A';
}


void Alphabet::setDeReductionTable() {
	deReductionTable['D'] = 'D';
	deReductionTable['E'] = 'D';
}


void Alphabet::setWang1999ReductionTable() {
	wang1999ReductionTable['C'] = 'A';
	wang1999ReductionTable['M'] = 'A';
	wang1999ReductionTable['F'] = 'A';
	wang1999ReductionTable['I'] = 'A';
	wang1999ReductionTable['L'] = 'A';
	wang1999ReductionTable['V'] = 'A';
	wang1999ReductionTable['W'] = 'A';
	wang1999ReductionTable['Y'] = 'A';

	wang1999ReductionTable['A'] = 'B';
	wang1999ReductionTable['T'] = 'B';
	wang1999ReductionTable['H'] = 'B';

	wang1999ReductionTable['G'] = 'C';
	wang1999ReductionTable['P'] = 'C';

	wang1999ReductionTable['D'] = 'D';
	wang1999ReductionTable['E'] = 'D';

	wang1999ReductionTable['S'] = 'E';
	wang1999ReductionTable['N'] = 'E';
	wang1999ReductionTable['Q'] = 'E';
	wang1999ReductionTable['R'] = 'E';
	wang1999ReductionTable['K'] = 'E';
}

