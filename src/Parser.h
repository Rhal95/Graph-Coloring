#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include"tinyxml2.h"
#include<iostream>
#include<set>
#include<vector>
#include<string>


namespace parser
{
#define VORLESUNG 1
#define SEMINAR 2
#define LABOR 3

static tinyxml2::XMLDocument doc;
struct raum {
    std::string name;
    unsigned char typ;
};

struct veranstaltung {
    std::string name;
    std::string profkuerzel;
    unsigned char typ;
    unsigned char semester;
    bool istVorlesung;
};


class Parser {

public:
    Parser(const char* filename);
    Parser(const Parser& p);
    std::vector<raum*> raeume;
    std::set<std::string>  professoren;
    std::vector<veranstaltung*> veranstaltungen;
    void load(const char* c);
	void save(const int* colors, char* fileName);
private:
    unsigned char getType(const char* attribute);
    void lese_raeume();
    void lese_veranstaltungen();
};
}

#endif // PARSER_H_INCLUDED
