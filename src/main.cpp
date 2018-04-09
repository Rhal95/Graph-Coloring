#include <iostream>
#include "Parser.h"
#include "Greedy.h"
#include "Welsh.h"
#include "Random.h"

using namespace std;
int main(int arggc, char** argv){
    cout << "Starting Programm" << endl;
    parser::Parser* p = new parser::Parser("bsp-in.xml");
    cout << "Parser build" << endl;    

    cout << "Calling Greedy" << endl;
    Greedy g = Greedy(p);
    cout << "Done." << endl;

    cout << "Calling Welsh" << endl;
    Welsh w = Welsh(p);
    cout << "Done." << endl;

	cout << "Calling Random" << endl;
    Random r = Random(p);
    cout << "Done." << endl;

    cout << "Saving Files" << endl;
    
    g.ColorAlg::graph.save(g.colors, "greedy.xml");
    w.ColorAlg::graph.save(w.colors, "welsh.xml");
    r.ColorAlg::graph.save(r.colors, "random.xml");
    
    cout << "All Done" << endl;
    return 0;
}
