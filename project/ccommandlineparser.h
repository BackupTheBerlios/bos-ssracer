#ifndef CCOMMANDLINEPARSER_H
#define CCOMMANDLINEPARSER_H

#include "bos.h"

#define STL_USING_ALL
#include "stl.h" // for vectors

//using namespace Wml;

class CCommandLineParser {
public:
	CCommandLineParser();
	CCommandLineParser(std::string dels);
	~CCommandLineParser();

	int initKeywords();
	int parse(std::string command);
	int setDeliminators(std::string dels);
	bool isDeliminator(char c);
	int execute();

	std::string* getDeliminators() {return &deliminators;} 
	int getNDels() {return ndels;}
	vector<std::string>* getKeywords() {return &Keywords;}
	vector<std::string>* getTokens() {return &Tokens;}

	// Add your command function here:
	int setvol();
	int loadmap();
	int pause();
	int play(); // soundFX or music
	int help();
	int clear(); // clear console
	int echo(); // echo text
	int stop(); // soundFX or music
    int settimer(); // set game timer resolution 

protected:
	std::string deliminators;
	int ndels;

	vector<std::string> Keywords;
	vector<std::string> Tokens;

private:

};

#endif