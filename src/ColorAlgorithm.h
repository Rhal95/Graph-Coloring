#ifndef COLORALG_H_INCLUDED
#define COLORALG_H_INCLUDED

#include "BuildGraph.h"
#include "Parser.h"

class ColorAlg{
  public:
  ColorAlg(parser::Parser* p);
  int* colors;
  virtual void color() = 0;
  Graph graph;
};

#endif
