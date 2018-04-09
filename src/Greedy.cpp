#include "Greedy.h"
#include <iostream>
#include <string>

using namespace std;

Greedy::Greedy(parser::Parser* par) : ColorAlg(par){
color();
}

void Greedy::color() {
    colors = new int[ColorAlg::graph.w];
    memset(colors, 0, ColorAlg::graph.w);
    //initialiseren von raum x zeit
    for(int i = ColorAlg::graph.vsize; i < ColorAlg::graph.w; i++) {
        colors[i] = i - ColorAlg::graph.vsize + 1;
    }
    //iterieren über colors & zeilen
    for(int i = 0; i < ColorAlg::graph.vsize; i++) {
        if(!colors[i]) {
            for(int j = ColorAlg::graph.vsize; j < ColorAlg::graph.w; j++) {
                if(!ColorAlg::graph.mat[i][j] && i != j) {
                    colors[i] = (j - ColorAlg::graph.vsize)+1;
                    ColorAlg::graph.useroomtime(i, j);
                    break;
                }
            }
        }
    }
  
}
/*
int main() {
    Greedy g;
    g.color();
    g.ColorAlg::graph.save(g.colors);
}*/
