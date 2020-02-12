#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;
class Parser {

	int position;
	string operation;
	
public:
	Parser();
	void setLine(const string&);
	string getNextToken();
	void reset();
};

Parser::Parser() : position{}, operation{} {}

void Parser::setLine(const string& str) {
	operation = str;
}

string Parser::getNextToken() {
	position = operation.find_first_of(" ");
	string token = operation.substr(0, position);
	operation = operation.substr(position + 1, operation.size());
	return token;
}

void Parser::reset() {
	position = 0;
}
