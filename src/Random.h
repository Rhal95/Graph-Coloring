#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include "BuildGraph.h"
#include "ColorAlgorithm.h"
class Random : public ColorAlg {
	public:
    Random(parser::Parser* parser);
	int* colors;
	void color();
	Graph graph;
};
#endif
