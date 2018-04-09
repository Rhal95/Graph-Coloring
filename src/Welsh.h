#ifndef WELSH_H_INCLUDED
#define WELSH_H_INCLUDED

#include "BuildGraph.h"
#include "ColorAlgorithm.h"
class Welsh : public ColorAlg{
	public:
    Welsh(parser::Parser* parser);
	int* colors;
	void color();
	//Graph graph;
};
#endif
