#ifndef BUILDGRAPH_H_INCLUDED
#define BUILDGRAPH_H_INCLUDED
#define true (int) (1==1)

#include "Parser.h"

	
enum Typ{Fach, RZeit};

typedef struct {
	int t;
	parser::raum* r;
} RTime;

typedef union{
	parser::veranstaltung* v;
	RTime rt;
} Data;

typedef struct{
    int index;
    Typ t;
    Data d;
} Knoten;

class Graph{
public:
	parser::Parser* p;
	Knoten* ks;
	int vsize;
	int rsize;
	int tsize;
	int* degrees;
	int w;
	bool ** mat;
	void build(parser::Parser* parser);
	void save(const int* colors, char* filename);
	void _degrees();
    void useroomtime(int vindex, int rtindex);
};




#endif
