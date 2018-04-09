#ifndef GREEDY_H_INCLUDED
#define GREEDY_H_INCLUDED

#include "BuildGraph.h"
#include "ColorAlgorithm.h"
class Greedy : public ColorAlg {
	public:
    Greedy(parser::Parser* parser);
	int* colors;
	void color();
	Graph graph;
};
#endif
