#include "include/debug.h"
#include "include/gbsc.h"
#include "include/alphabet.h"

#include "config-gbsc.h"
#include "assert.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace alphabet;
using namespace std;


void test_draw_graph_5_nodes() {
	string sequence = "QAZWSQAZWSQAZWSQAZWSQAZWSQAZWSQAZWS";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		stringstream ss;
		ss << "+->(QA)-->(AZ)-->(ZW)--+" << endl;
		ss << "|                      |" << endl;
		ss << "+--(SQ)<--(WS)<--------+" << endl;
		assert(ss.str() == c.getGraph().drawGraph());
	}

}

void test_draw_graph_4_nodes() {
	string sequence = "QAZWQAZWQAZWQAZWQAZWQAZWQAZWQAZWQAZWQAZWQAZWQAZW";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		stringstream ss;
		ss << "+->(QA)-->(AZ)--+" << endl;
		ss << "|               |" << endl;
		ss << "+--(WQ)<--(ZW)<-+" << endl;
		assert(ss.str() == c.getGraph().drawGraph());
	}
}

void test_draw_graph_3_nodes() {
	string sequence = "QAZQAZQAZQAZQAZQAZQAZQAZQAZQAZ";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		stringstream ss;
		ss << "+->(QA)-->(AZ)--+" << endl;
		ss << "|               |" << endl;
		ss << "+--(ZQ)<--------+" << endl;
		assert(ss.str() == c.getGraph().drawGraph());
	}

}


void test_draw_graph_2_nodes() {
	string sequence = "QAQAQAQAQAQAQAQAQAQAQA";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		stringstream ss;
		ss << "+->(QA)--+" << endl;
		ss << "|        |" << endl;
		ss << "+--(AQ)<-+" << endl;
		assert(ss.str() == c.getGraph().drawGraph());
	}

}


void test_draw_graph_1_nodes() {
	string sequence = "QQQQQQQQQQQQQQQQQQQQQQQQ";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		stringstream ss;
		ss << "+->(QQ)--+" << endl;
		ss << "|        |" << endl;
		ss << "+--------+" << endl;
		assert(ss.str() == c.getGraph().drawGraph());
	}

}

void test_region_interval()
{
	string sequence = "MRGGMGNMQKMMKQMQKMQKDMAKAQEELAEKVVEGTAGGGMVTVKANGQKEILDVIIKEEVVDPEDIDMLQDLVLAATNEALKKVDEITNETMGQFTKGMNMPGLF";
	Gbsc gbsc;
	Alphabet a;
	std::vector<graph::Cycle> cycles = gbsc.findSubgraphs(sequence, 3, 7, false, &a);

	for (auto c : cycles)
	{
		cout << c.getGraph().drawGraph() << endl;

		cout << c.getBegin() << endl;
		cout << c.getEnd() << endl;
		cout.flush();
        assert(c.getBegin() == 8);
        assert(c.getEnd() == 20);
	}
}

int main(int argc, char** argv)
{
	cout << "Test GBSC\n";
	DEBUG("Debugging enabled");
	test_region_interval();
	test_draw_graph_1_nodes();
	test_draw_graph_2_nodes();
	test_draw_graph_3_nodes();
	test_draw_graph_4_nodes();
	test_draw_graph_5_nodes();
    cout << "Test passed" << endl;
	cout << "------------------------------" << endl << endl;
	return 0;
}
