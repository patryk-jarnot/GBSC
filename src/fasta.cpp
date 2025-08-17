/*
 * fasta.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: pjarnot
 */

#include "include/fasta.h"
#include <fstream>
#include <vector>
#include <map>
#include <cstring>

using namespace fasta;
using namespace std;


Sequence FastaReader::readSequence()
{
	Sequence retval;
	std::getline(*inputStream, retval.header);
	if (retval.header.length() == 0 || retval.header[0] != '>')
	{
		throw "invalid header";
	}

	while ((!inputStream->eof() && inputStream->peek() != EOF) && inputStream->peek() != '>')
	{
		std::string tmp;
		std::getline(*inputStream, tmp);

		retval.sequence += tmp;
	}

//	cout.flush();
	return retval;
}

Sequence* FastaReader::readSequencePtr()
{
	Sequence *retval = new Sequence();
	std::getline(*inputStream, retval->header);
	if (retval->header.length() == 0 || retval->header[0] != '>')
	{
		throw "invalid header";
	}

	while ((!inputStream->eof() && inputStream->peek() != EOF) && inputStream->peek() != '>')
	{
		std::string tmp;
		std::getline(*inputStream, tmp);

		retval->sequence += tmp;
	}

//	cout.flush();
	return retval;
}


FastaReader::FastaReader(istream *istream) : initializedStream(false)
{
	inputStream = istream;
}


FastaReader::FastaReader(std::string ifileName) : initializedStream(true)
{
	inputStream = new ifstream(ifileName);
}


FastaReader::~FastaReader() {
	if (initializedStream)
	{
		((ifstream*)inputStream)->close();
		delete inputStream;
	}
}


bool FastaReader::hasNextSequence() {
	return !inputStream->eof() && inputStream->peek() != EOF;
}


Sequence* FastaReader::readNextSequence() {
	if (!inputStream->eof() && inputStream->peek() != EOF)
	{
		//current.reset(readSequencePtr());
		current = std::unique_ptr<Sequence>(readSequencePtr());
	}

	return current.get();
}

void FastaReader::resetFilePointer() {
	inputStream->seekg(0);
}


std::vector<Sequence> FastaReader::readSequences()
{
	std::vector<Sequence> retval;

	while (!inputStream->eof() && inputStream->peek() != EOF)
	{
		Sequence s = readSequence();
		retval.push_back(s);
	}

	return retval;
}


string FastaReader::readAcc(string header) {
	size_t beg = header.find('|', 0) + 1;
	size_t end = header.find('|', beg) - 1;
	return header.substr(beg, end - beg + 1);
}


std::map<string, Sequence> FastaReader::readSequencesById()
{
	std::map<string, Sequence> retval;

	while (!inputStream->eof() && inputStream->peek() != EOF)
	{
		Sequence s = readSequence();
		string proteinAcc = readAcc(s.header);
		retval[proteinAcc] = s;
	}

	return retval;
}


void FastaWriter::writeSequence(Sequence isequence)
{
	outputStream->write(isequence.header.c_str(), isequence.header.length());
	outputStream->write("\n", 1);
	outputStream->write(isequence.sequence.c_str(), isequence.sequence.length());
	outputStream->write("\n", 1);
}


FastaWriter::FastaWriter(std::ostream *istream) : initializedStream(false)
{
	outputStream = istream;
}


FastaWriter::FastaWriter(std::string ifileName) : initializedStream(true)
{
	outputStream = new ofstream(ifileName);
}


FastaWriter::~FastaWriter()
{
	if (initializedStream)
	{
		((ofstream*)outputStream)->close();
		delete outputStream;
	}
}


void FastaWriter::writeSequences(std::vector<Sequence> isequences)
{
	for (auto s : isequences)
	{
		writeSequence(s);
	}
}


FastaClusterReader::FastaClusterReader(std::string ipath) {
	dir = opendir(ipath.c_str());
	clusterPath = ipath;
}

bool FastaClusterReader::hasNextCluster() {
	if (!next) {
		dirent *ent;
		ent = readdir(dir);
		while (ent) {
			if (strcmp((const char *)ent->d_name, ".") == 0 || strcmp((const char *)ent->d_name, "..") == 0) {
				ent = readdir(dir);
				continue;
			}

			Cluster *clst = new Cluster();
			clst->model = ent->d_name;
			clst->model = clst->model.substr(0, clst->model.size()-6);
			clst->path += clusterPath;
			clst->path += "/";
			clst->path += ent->d_name;
			FastaReader fr(clst->path);
			clst->sequences = fr.readSequences();
			next = std::unique_ptr<Cluster>(clst);
			return true;
		}
		return false;
	}
	else {
		return true;
	}
}

Cluster *FastaClusterReader::readNextCluster() {
	if (hasNextCluster()) {
		current = move(next);
		return current.get();
	}
	else {
		return nullptr;
	}
}

