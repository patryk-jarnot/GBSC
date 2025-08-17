/*
 * alphabetreduction.h
 *
 *  Created on: Jul 25, 2022
 *      Author: pjarnot
 */

#ifndef CONTENT_INCLUDE_ALPHABET_H_
#define CONTENT_INCLUDE_ALPHABET_H_

#include <string>
#include <map>

namespace alphabet {


enum class ReductionSet {
	NONE = 0, CUSTOM, WANG_1999, LI_2003, COLLAGEN, DE
};


class Alphabet {
public:
	char reduceResidue(char);
	std::string reduceSequence(std::string);
	void setReductionTable(ReductionSet);
	void setAlphabet(std::string);
	Alphabet();

private:
	ReductionSet currentSet;
	std::map<char, char> wang1999ReductionTable;
	std::map<char, char> li2003ReductionTable;
	std::map<char, char> collagenReductionTable;
	std::map<char, char> deReductionTable;

	void setLi2003ReductionTable();
	void setWang1999ReductionTable();
	void setCollagenReductionTable();
	void setDeReductionTable();

};


}


#endif /* CONTENT_INCLUDE_ALPHABET_H_ */
