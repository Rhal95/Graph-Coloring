#include<iostream>
#include<set>
#include<vector>
#include<string>
#include "tinyxml2.h"
#include "Parser.h"



using namespace std;
using namespace tinyxml2;
using namespace parser;

void Parser::load(const char* c)
{
    doc.LoadFile(c);
    lese_raeume();
    lese_veranstaltungen();
}

Parser::Parser(const char* filename)
{
    load(filename);
}


unsigned char Parser::getType(const char* attribute)
{
    string a(attribute);
    if(!a.compare("v")) return VORLESUNG;
    if(!a.compare("s")) return SEMINAR;
    if(!a.compare("l")) return LABOR;
    return 0;
}
void Parser::lese_raeume()
{
    XMLNode* t = doc.FirstChild();
    XMLNode* raume = t->FirstChildElement("raeume");
    XMLElement* ra = raume->FirstChildElement("raum");
    while(ra != nullptr)
    {
        //cout << ra->Name() << "\t" << ra->Attribute("name") << "\t" << ra->Attribute("typ") << "\n";
        raum* r = new raum();
        r->name = ra->Attribute("name");
        r->typ  = getType(ra->Attribute("typ"));
        raeume.push_back(r);
        ra = ra->NextSiblingElement();
    }
    raeume.shrink_to_fit();
}

void Parser::lese_veranstaltungen()
{
    XMLNode* t = doc.FirstChild();
    XMLElement* fs = t->FirstChildElement("faecher");
    XMLElement* s = fs->FirstChildElement("semester");
    while(s != nullptr)
    {
        XMLElement* vs = s->FirstChildElement();
        while(vs != nullptr)
        {
            XMLElement* f = vs->FirstChildElement("fach");
            while(f != nullptr)
            {
                veranstaltung* v = new veranstaltung();
                v->name = f->Attribute("name");
                string p = string(f->Attribute("kuerzel"));
                professoren.insert(p);
                v->profkuerzel = p;
                v->semester = stoi(s->Attribute("nr"));
                v->typ = getType(f->Attribute("typ"));
                v->istVorlesung = (string(vs->Value()) == ("vorlesungen"));
                veranstaltungen.push_back(v);
                f = f->NextSiblingElement("fach");
            }
            vs = vs->NextSiblingElement();
        }
        s = s->NextSiblingElement();
    }
    veranstaltungen.shrink_to_fit();
}

