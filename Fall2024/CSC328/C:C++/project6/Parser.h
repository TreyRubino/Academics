/// Trey Rubino

#ifndef PARSER_H
#define PARSER_H

#include <string>

/// Dr. Schwesingers implmentation of the Parser class
struct Parser 
{
	std::string port;
	std::string file;
	
	Parser();
	void parse(int argc, char** argv);
	std::string usage();
};

#endif 
