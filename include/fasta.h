/*
 * fasta.h
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#ifndef GBSC_INCLUDE_FASTA_H_
#define GBSC_INCLUDE_FASTA_H_

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <memory>

#include "dirent.h"


namespace fasta
{
	struct Sequence {
		Sequence() { }
		Sequence(std::string iheader, std::string isequence) : header(iheader), sequence(isequence) { }

		std::string header;
		std::string sequence;
	};


	struct Cluster {
		Cluster() {}
		Cluster(std::string imodel, std::string ipath, std::vector<Sequence> isequences) : model(imodel), path(ipath), sequences(isequences) { }

		std::string model;
		std::string path;
		std::vector<Sequence> sequences;
	};


	class FastaReader
	{
	private:
		bool initializedStream;
		std::istream *inputStream;

		std::unique_ptr<Sequence> current;

		Sequence readSequence();
		Sequence* readSequencePtr();
		std::string readAcc(std::string header);
	protected:
	public:
		FastaReader(std::istream *istream);
		FastaReader(std::string ifileName);
		virtual ~FastaReader();

		std::vector<Sequence> readSequences();
		std::map<std::string, Sequence> readSequencesById();

		bool hasNextSequence();
		Sequence* readNextSequence();
		void resetFilePointer();
	};


	class FastaWriter
	{
	private:
		bool initializedStream;
		std::ostream *outputStream;

		void writeSequence(Sequence isequence);
	protected:
	public:
		FastaWriter(std::ostream *istream);
		FastaWriter(std::string ifileName);
		virtual ~FastaWriter();

		void writeSequences(std::vector<Sequence> isequences);
	};


	class FastaClusterReader {
	public:
		FastaClusterReader(std::string ipath);

		bool hasNextCluster();
		Cluster *readNextCluster();

	private:
		DIR *dir;
		std::string clusterPath;
		std::unique_ptr<Cluster> current;
		std::unique_ptr<Cluster> next;

	};
}


#endif /* GBSC_INCLUDE_FASTA_H_ */
