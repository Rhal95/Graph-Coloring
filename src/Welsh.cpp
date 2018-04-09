#include "Welsh.h"
#include <iostream>
#include <string>
#include <iterator>

using namespace std;
Welsh::Welsh(parser::Parser* parser): ColorAlg(parser){
color();
}

class IteratorMaxDegree : public std::iterator<std::forward_iterator_tag, int>{
public:
int selectedIndex;
int selectedValue;
int size;
int *arr;

IteratorMaxDegree(const int size,const int * arr): size(size){
    this->arr = new int[size];
    for(int i = 0; i < size; i++){
        this->arr[i] = arr[i];
    }
    selectedIndex = 0;
    selectedValue = -1;
    for(int i = 0; i < size; i++){
        if(arr[i] >= selectedValue){
            selectedValue = arr[i];
            selectedIndex = i;
        }
    }
}



//selects next node
void operator++(){
    arr[selectedIndex] = -1;
    selectedValue = -1;
    for(int i = 0; i < size; i++){
        if(arr[i] >= selectedValue){
            selectedValue = arr[i];
            selectedIndex = i;
        }
    }
}
const int& operator*()const { return selectedIndex;}

};


void Welsh::color(){
	//ColorAlg::graph.build();
    ColorAlg::graph._degrees();

	colors = new int[ColorAlg::graph.w];
	memset(colors, 0, ColorAlg::graph.w);

	//initialiseren von raum x zeit
    for(int i = ColorAlg::graph.vsize; i < ColorAlg::graph.w; i++) {
        colors[i] = i - ColorAlg::graph.vsize + 1;
    }
        IteratorMaxDegree it = IteratorMaxDegree(ColorAlg::graph.vsize, ColorAlg::graph.degrees);
    	//find biggest value        
    	for(int p = *it; it.arr[*it] > -1; ++it, p = *it){

            //finding a room for p using first avalible color
    		for(int i = ColorAlg::graph.vsize; i < ColorAlg::graph.w; i++){
    			if(!ColorAlg::graph.mat[p][i]){
    				//room found color and try finding courses for same time slot
    				colors[p] = i - ColorAlg::graph.vsize + 1;

					ColorAlg::graph.useroomtime(p, i);

					ColorAlg::graph.degrees[p] = -1;
                    //break;

					IteratorMaxDegree itn = IteratorMaxDegree(ColorAlg::graph.vsize, ColorAlg::graph.degrees);
                   				
                    for(int pn = *itn; itn.arr[*itn] > -1; ++itn){
					    
    				    //set found
    				    for(int in= i-((i-ColorAlg::graph.vsize)%ColorAlg::graph.rsize); in-(i-((i-ColorAlg::graph.vsize)%ColorAlg::graph.rsize)) < ColorAlg::graph.rsize; in++){
    						if(ColorAlg::graph.mat[pn][in] == 0){
    							colors[pn] = in - ColorAlg::graph.vsize + 1;
								ColorAlg::graph.useroomtime(pn, in);
								ColorAlg::graph.degrees[pn] = -1;
                                break;
							}
    					}		
					}
    			}
    		}
    	}
}


