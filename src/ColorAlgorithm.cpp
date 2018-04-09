#include "ColorAlgorithm.h"

ColorAlg::ColorAlg(parser::Parser* p){
graph = Graph();
graph.build(p);
}
