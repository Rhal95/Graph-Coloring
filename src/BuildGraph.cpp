#include "BuildGraph.h"

#include "Parser.h"

#include <iostream>
#include <string>

using namespace std;

void Graph::_degrees(){
	degrees = new int[vsize];
	memset(degrees, 0, vsize); 
	for(int i = 0; i<vsize;i++){
		for(int j = 0; j<vsize;j++){
			degrees[i] += mat[j][i];
		}
	}
}

void Graph::useroomtime(int vindex, int rtindex){
	//if(rtindex < vsize || rtindex >= w) return;
	//spalte löschen
	for(int k = 0; k < vsize; k++) {
		if(k != vindex) mat[k][rtindex] = true;
	}
                   
	//zeile löschen
	for(int k = vsize; k < w; k++){
		if(k != rtindex) mat[vindex][k] = true;
	}
	//für jeden knoten, welcher nicht gleichzeitig statt finden kann die zeiten streichen
	for(int k = 0; k < vsize; k++){
		if(k != vindex && mat[vindex][k]){
			int start = rtindex-((rtindex-vsize)%rsize);
			for(int l = 0; l < rsize; l++){
				mat[k][l+start] = true;
			}
		}
	}
}

void Graph::build(parser::Parser* parser) {
    p = parser;
    vsize = p->veranstaltungen.size();
    rsize = p->raeume.size();
    tsize = 30;
    w = vsize + rsize * tsize;
    ks = new Knoten[w];
    for(int i = 0; i < w; i++) {
        if(i < vsize) {
            ks[i].index = i;
            ks[i].t = Fach;
            ks[i].d.v = p->veranstaltungen.at(i);
        } else {
            int ti = (i-vsize) / 6;
            int ri = (i-vsize) % 6;
            ks[i].index = i;
            ks[i].t = RZeit;
            ks[i].d.rt.r = p->raeume.at(ri);
            ks[i].d.rt.t = ti;
            //cout << "(" << ri << "|" << ti << ")" << endl;
        }
    }
    mat = new bool*[vsize];
    mat[0] = new bool[vsize * w];
    for(int i = 1; i < vsize; i++) {
        mat[i] = mat[i-1] + w;
    }
    memset(mat[0], false, vsize * w);
    for(int i = 0; i < vsize; i++) {
        for(int j = i; j < w; j++) {
            if(i < vsize && j < vsize) {
                //fach - fach
                if(i == j){
					mat[i][j] = false;
					continue;
				}
                parser::veranstaltung* v1 = ks[i].d.v;
                parser::veranstaltung* v2 = ks[j].d.v;
                if(v1->name == v2->name && v1->typ != v2->typ) {
                    mat[i][j] = true;
                    mat[j][i] = true;
                } else if(v1->semester == v2->semester && (v1->istVorlesung || v2->istVorlesung)) {
                    mat[i][j] = true;
                    mat[j][i] = true;
                } else if(v1->profkuerzel == v2->profkuerzel) {
                    mat[i][j] = true;
                    mat[j][i] = true;
                }
            } else {
                //fach - raum - zeit
                parser::veranstaltung* v = ks[i].d.v;
                parser::raum* r = ks[j].d.rt.r;
                if(v->typ != r->typ) {
                    mat[i][j] = true;
                    //cout << "diff: " << v->typ+0 << " " << r->typ+0 << endl;
                }
                //else cout << "same: " << v->typ+0 << " " << r->typ+0 << endl;
            }
        }
    }
    Graph::_degrees();
}

const char* fromTyp(unsigned char t){
	switch (t){
	case 1: return "v";
	case 2: return "s";
	case 3: return "l";
	default: return "";
	}
}

void Graph::save(const int* colors, char* filename){
	using namespace parser;
	using namespace tinyxml2;
	XMLDocument toSave;
	XMLNode* root = toSave.NewElement("template");
	toSave.InsertFirstChild(root);
	//räume
	XMLNode* rs = toSave.NewElement("raeume");
	root->InsertEndChild(rs);

	for(int i = 0; i < rsize; i++){
		struct raum* raum = p->raeume.at(i);
		XMLElement* r = toSave.NewElement("raum");
		r->SetAttribute("id", i+1);
		r->SetAttribute("name", raum->name.c_str());
		r->SetAttribute("typ", fromTyp(raum->typ));
			for(int k = 0; k < vsize; k++){			
				if(colors[k] % rsize == i){
					struct veranstaltung* vera = ks[k].d.v;
					const char* name = 
						vera->istVorlesung? "vorlesung": "veranstaltung";
					XMLElement* t = toSave.NewElement(name);
					t->SetAttribute("name", vera->name.c_str());
					t->SetAttribute("prof", vera->profkuerzel.c_str());
					t->SetAttribute("time", (colors[k]-1)/rsize+1);
					t->SetAttribute("typ", fromTyp(vera->typ));
					t->SetAttribute("semester", vera->semester);
					r->InsertEndChild(t);
				
			}
		}

		rs->InsertEndChild(r);
	}

	//und so weiter, und so weiter
	//struktur für ausgehendes xml?

	toSave.SaveFile(filename);
}


