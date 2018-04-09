#include "Random.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

Random::Random(parser::Parser* par) : ColorAlg(par){
color();
}


void Random::color(){
	colors = new int[ColorAlg::graph.w];
    memset(colors, 0, ColorAlg::graph.w);
    //initialiseren von raum x zeit
    for(int i = ColorAlg::graph.vsize; i < ColorAlg::graph.w; i++) {
        colors[i] = i - ColorAlg::graph.vsize + 1;
    }
    
    srand(time(NULL));
    
    int tries;
    for(int i = 0; i < ColorAlg::graph.vsize; i++){
    	tries = 0;
    	do{
    		int number = (rand() % (ColorAlg::graph.rsize*30)) + 1;
    		
    		if(!ColorAlg::graph.mat[i][number]){
    			ColorAlg::graph.useroomtime(i, number);
    			colors[i] = number - ColorAlg::graph.vsize + 1;
    			break;
    		}else{
    			tries++;
    		}
    	}while(tries < 1000);
    	if(tries >= 1000){
    		cout << "ERROR" << endl;
    	}
    }
}
