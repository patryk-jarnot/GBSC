/*
 * testidentification.cpp
 *
 *  Created on: Nov 8, 2021
 *      Author: pjarnot
 */


#include "include/similaritysearch.h"
#include "include/gbsc.h"
#include "include/debug.h"
#include "include/alphabet.h"

#include "assert.h"

#include <iostream>
#include <vector>
#include <sstream>


using namespace std;
using namespace similaritysearch;
using namespace alphabet;


void test_str_only() {
	string sequence = "QAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
        assert(c.getBegin() == 1);
        assert(c.getEnd() == 48);
	}
}


void test_str_only_padding_1() {
	string sequence = "SQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAZXCVVBNMSDFGH";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
        assert(c.getBegin() == 2);
        assert(c.getEnd() == 49);
	}
}

void test_str_only_padding_2() {
	string sequence = "SQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQZXCVVBNMSDFGH";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
        assert(c.getBegin() == 2);
        assert(c.getEnd() == 50);
	}
}



void test_str_only_padding_front_1() {
	string sequence = "SQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQA";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
        assert(c.getBegin() == 2);
        assert(c.getEnd() == 49);
	}
}



void test_str_orphan_nodes() {
	string sequence = "SQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQAQASDQSDESDRSDISDOSDPSDNSD";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, true, &a);

	for (size_t i=0; i<cycles.size(); i++)
	{
		graph::Cycle c = cycles[i];
		if (i == 0) {
			assert(c.getBegin() == 2);
			assert(c.getEnd() == 49);
		}
		else if (i == 1) {
			assert(c.getBegin() == 50);
			assert(c.getEnd() == 72);
		}
	}
}


void test_complex_strs_from_real_sequence() {
	string sequence = "MKRKNKVLSILLTLLLIISTTSVNMSFAEATPSIEMVLDKTEVHVGDVITATIKVNNIRKLAGYQLNIKFDPEVLQPVDPATGEEFTDKSMPVNRVLLTNSKYGPTPVAGNDIKSGIINFATGYNNLTAYKSSGIDEHTGIIGEIGFKVLKKQNTSIRFEDTLSMPGAISGTSLFDWDAETITGYEVIQPDLIVVEAEPLKDASVALELDKTKVKVGDIITATIKIENMKNFAGYQLNIKYDPTMLEAIELETGSAIAKRTWPVTGGTVLQSDNYGKTTAVANDVGAGIINFAEAYSNLTKYRETGVAEETGIIGKIGFRVLKAGSTAIRFEDTTAMPGAIEGTYMFDWYGENIKGYSVVQPGEIVVEGEEPGEEPTEEPVPTETSVDPTPTVTEEPVPSELPDSYVIMELDKTKVKVGDIITATIKIENMKNFAGYQLNIKYDPTMLEAIELETGSAIAKRTWPVTGGTVLQSDNYGKTTAVANDVGAGIINFAEAYSNLTKYRETGVAEETGIIGKIGFRVLKAGSTAIRFEDTTAMPGAIEGTYMFDWYGENIKGYSVVQPGEIVVEGEEPGEEPTEEPVPTETSVDPTPTVTEEPVPSELPDSYVIMELDKTKVKVGDIITATIKIENMKNFAGYQLNIKYDPTMLEAIELETGSAIAKRTWPVTGGTVLQSDNYGKTTAVANDVGAGIINFAEAYSNLTKYRETGVAEETGIIGKIGFRVLKAGSTAIRFEDTTAMPGAIEGTYMFDWYGENIKGYSVVQPGEIVAEGEEPGEEPTEEPVPTETSADPTPTVTEEPVPSELPDSYVIMELDKTKVKVGDIITATIKIENMKNFAGYQLNIKYDPTMLEAIELETGSAIAKRTWPVTGGTVLQSDNYGKTTAVANDVGAGIINFAEAYSNLTKYRETGVAEETGIIGKIGFRVLKAGSTAIRFEDTTAMPGAIEGTYMFDWYGENIKGYSVVQPGEIVAEGEEPGEEPTEEPVPTETPVDPTPTVTEEPVPSELPDSYVIMELDKTKVKVGDIITATIKIENMKNFAGYQLNIKYDPTMLEAIELETGSAIAKRTWPVTGGTVLQSDNYGKTTAVANDVGAGIINFAEAYSNLTKYRETGVAEETGIIGKIGFRVLKAGSTAIRFEDTTAMPGAIEGTYMFDWYGENIKGYSVVQPGEIVAEGEEPTEEPVPTETPVDPTPTVTEEPVPSELPDSYVIMELDKTKVKEGDVIIATIRVNNIKNLAGYQIGIKYDPKVLEAFNIETGDPIDEGTWPAVGGTILKNRDYLPTGVAINNVSKGILNFAAYYVYFDDYREEGKSEDTGIIGNIGFRVLKAEDTTIRFEELESMPGSIDGTYMLDWYLNRISGYVVIQPAPIKAASDEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPIPTDTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSDEPTPSETPEEPTPTTTPTPTPSTTPTSGSGGSGGSGGGGGGGGGTVPTSPTPTPTSKPTSTPAPTEIEEPTPSDVPGAIGGEHRAYLRGYPDGSFRPERNITRAEAAVIFAKLLGADESYGAQSASPYSDLADTHWAAWAIKFATSQGLFKGYPDGTFKPDQNITRAEFATVVLHFLTKVKGQEIMSKLATIDISNPKFDDCVGHWAQEFIEKLTSLGYISGYPDGTFKPQNYIKRSESVALINRALERGPLNGAPKLFPDVNESYWAFGDIMDGALDHSYIIEDEKEKFVKLLED";

	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, true, &a);

	for (size_t i=0; i<cycles.size(); i++)
	{
		cout << "begin: " << cycles[i].getBegin() << " end: " << cycles[i].getEnd() << " " <<cycles[i].to_string() << endl;
	}

	return ;

	for (size_t i=0; i<cycles.size(); i++)
	{
		graph::Cycle c = cycles[i];
		if (i == 0) {
			assert(c.getBegin() == 2);
			assert(c.getEnd() == 49);
		}
		else if (i == 1) {
			assert(c.getBegin() == 50);
			assert(c.getEnd() == 72);
		}
	}
}


int main(int argc, char** argv)
{
    cout << "Test identification" << endl;
    test_str_only();
    test_str_only_padding_1();
    test_str_only_padding_2();
    test_str_only_padding_front_1();
	test_str_orphan_nodes();
	test_complex_strs_from_real_sequence();
	cout << "Test passed." << endl;
    cout << "------------------------------" << endl << endl;
	return 0;
}
