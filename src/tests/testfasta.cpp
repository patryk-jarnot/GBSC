/*
 * testfasta.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#include "include/fasta.h"
//#include "config-gbsc.h"

#include "stdio.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "assert.h"


using namespace std;

class TestFasta
{
private:
	std::string testFileName;
	std::string sprotFileName;
	std::string testClustersDirPath;

protected:

public:
	TestFasta(std::string root_path)
	{
		testFileName = root_path + "/src/tests/data/reading_writing.fasta";
		sprotFileName = root_path + "/src/tests/data/sprot_samples.fasta";
		testClustersDirPath = root_path + "/src/tests/data/gbsc_pfam_clusters";
	}

	void test_init()
	{
		std::remove(testFileName.c_str());
	}

	void test_readingFastaSequenceBySequence()
	{
		fasta::FastaReader fr(testFileName);

		int i = 0;
		while (fr.hasNextSequence()) {
			fasta::Sequence* s = fr.readNextSequence();

            stringstream header;
            header << ">header " << i;
            stringstream sequence;
            sequence << "sequence " << i;
			//cout << "header: " << s.header << "; sequence: " << s.sequence << "\n";
			//cout << "header: " << header.str() << "; sequence: " << sequence.str() << "\n";
            assert(s->header == header.str() && s->sequence == sequence.str());
            i++;
		}
	}

	void test_readingFasta()
	{
		vector<fasta::Sequence> sequences;
		fasta::FastaReader fr(testFileName);
		sequences = fr.readSequences();

		//cout << "sequences.size(): " << sequences.size() << "\n";
		cout.flush();
		assert(sequences.size() == 10);

		for (size_t i=0; i<sequences.size(); i++)
		{
            auto s = sequences[i];
            stringstream header;
            header << ">header " << i;
            stringstream sequence;
            sequence << "sequence " << i;
			//cout << "header: " << s.header << "; sequence: " << s.sequence << "\n";
			//cout << "header: " << header.str() << "; sequence: " << sequence.str() << "\n";
            assert(s.header == header.str() && s.sequence == sequence.str());
		}
	}

	void test_readingFastaById()
	{
		map<string, fasta::Sequence> sequences;
		fasta::FastaReader fr(sprotFileName);
		sequences = fr.readSequencesById();

		cout.flush();
		assert(sequences.size() == 14);

		auto s = sequences["A1WYA9"];
		string header = ">sp|A1WYA9|COBQ_HALHL Cobyric acid synthase OS=Halorhodospira halophila (strain DSM 244 / SL1) OX=349124 GN=cobQ PE=3 SV=1";
		string sequence = "MVRARTLMLQGTCSGAGKTALVAGLCRLLARHGVRVAPFKPQNMSNNAAVTADGGEIGRGQWLQALAAGLPAHTDMNPVLLKPEAERTAQVVVQGHVTGRLEARAFREARQPLLPPVLESFQRLCAAYDVVLVEGAGSPAEPNLRQGDIANMGFAEAADVPVWLVGDIDRGGVFASLLGTLEWLDDADRRRVEALIINRFRGSPELLGEAPAQLEARGGVPVIGVVPAVPDLHLPEEDAPYRMAGPRGSGGALQVVAVAYPRMSNHDDLDALDAESGVHVRFARQPRELDGADLIVLPGSKHVFSDLAWLRESGMAEALYRHCRYGGRVVGLCGGLQMLGEGIEDPEGVEGGGSAPGLGLLPVHTRLAPTKQLAEVHGHAEWPAPVAVTGYEIHHGVTGAQEGLFPFVARSDDGRVLGSYLHRLFDSGPFRRALLVEWFALEGEGGDEQARIEAELDRLADTLEQALEPGWLKALGVPARPST";
		assert(s.header == header && s.sequence == sequence);

		s = sequences["P59610"];
		header = ">sp|P59610|ARGJ_BRADU Arginine biosynthesis bifunctional protein ArgJ OS=Bradyrhizobium diazoefficiens (strain JCM 10833 / IAM 13628 / NBRC 14792 / USDA 110) OX=224911 GN=argJ PE=3 SV=1";
		sequence = "MSSSVSPLAPKTVPDMPVIAGVRLATAEAGIRYKNRTDVLLAVMDKGTAVAGVFTKSKCPSAPVEWCRAKLKGGKARALVVNSGNANAFTGKTGRSSTALTAKIAAKAVGCSESEIFLASTGVIGEPLDATKFDGVLGRLAETAEPGDYLAAAKAIMTTDTFPKVATATVKLGKAKVTINGMAKGAGMIAPDMATMLSFVFTDAPIAPAALQALLKSGVEDTFNAVTIDGDTSTSDTLLAFATGAAAEHGAPKISRASDPRLKAFVKAFNQVLANLAEQVARDGEGARKLVEITVEGAKTKASARKIAMSIANSPLVKTAIAGEDANWGRVVMAVGKAGEPADRDKLSISFNGIRVARSGARDPDYDEAQVSEAMKAPEIAIKVSLGLGKGRDRVMTCDLTKEYVAINGDYRS";
		assert(s.header == header && s.sequence == sequence);
	}

	void test_writingFasta()
	{
		vector<fasta::Sequence> sequences;
		for (int i=0; i<10; i++)
		{
			fasta::Sequence s1;
			s1.header = ">header ";
			s1.header += to_string(i);
			s1.sequence = "sequence ";
			s1.sequence += to_string(i);
			sequences.push_back(s1);
		}

		fasta::FastaWriter fw(testFileName);
		fw.writeSequences(sequences);
	}

	/**
	 * Depending on g++ & lib versions readNextCluster() can return clusters in different order.
	 */
	void test_readingFastaClusters() {
//		fasta::FastaClusterReader fcr(testClustersDirPath);
//
//		assert(fcr.hasNextCluster());
//		if (fcr.hasNextCluster()) {
//			fasta::Cluster *c = fcr.readNextCluster();
//			assert(c->model == "EQ-QL_QQ-QL");
//			assert(c->path == "src/tests/data/gbsc_pfam_clusters/EQ-QL_QQ-QL.fasta");
//			assert(c->sequences.size() == 2);
//		}
//
//		assert(fcr.hasNextCluster());
//		if (fcr.hasNextCluster()) {
//			fasta::Cluster *c = fcr.readNextCluster();
//			assert(c->model == "EQ-QQ_GQ-QL_HL-LE_KH-HL_QL-LE_QL-LK_QQ-QE");
//			assert(c->path == "src/tests/data/gbsc_pfam_clusters/EQ-QQ_GQ-QL_HL-LE_KH-HL_QL-LE_QL-LK_QQ-QE.fasta");
//			assert(c->sequences.size() == 1);
//		}
	}
};


int main(int argc, char** argv)
{
	string root_path = string(argv[1]);
    cout << "Test fasta" << endl;
    TestFasta testFasta(root_path);
    testFasta.test_init();
	testFasta.test_writingFasta();
	testFasta.test_readingFasta();
	testFasta.test_readingFastaById();
	testFasta.test_readingFastaSequenceBySequence();
	testFasta.test_readingFastaClusters();
	cout << "Test passed." << endl;
    cout << "------------------------------"<< endl << endl;
	return 0;
}



