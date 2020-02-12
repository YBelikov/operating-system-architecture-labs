#pragma once
#include "Register.h"
#include "Accumulator.h"
#include "Parser.h"
#include <fstream>
#include <array>
#include <string>


using std::array;
using std::string;
using std::ifstream;
using std::cout;
using std::cin;

template<size_t N, size_t Bits>
class Processor {

private:

	string commandString;
	size_t commandCounter;
	size_t tactsCounter;
	int lastResult;
	
	Accumulator<Bits> accumulator;
	array<Register<Bits>*, N> registers;
	Parser parser;
	void add(size_t);
	void add(const string&);
	void add(int);
	void move(size_t, int);
	void move(const string&);
	void move(int);
	void makeAddOperation();
	void makeMoveOperation();
	void printTact();

public:
	Processor();
	void start(const string&);
	~Processor();
};

template<size_t N, size_t Bits>
Processor<N, Bits>::Processor() : commandString{ "" }, commandCounter{1}, tactsCounter{1}, parser{} {
	
	for (int i = 0; i < registers.size(); ++i) {
		registers[i] = new Register<Bits>;
		(*registers[i]) = i + 1;
	}
}

template<size_t N, size_t Bits>
Processor<N, Bits>::~Processor() {
	for (int i = 0; i < registers.size(); ++i) {
		delete registers[i];
	}
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::add(size_t registerIndex) {
	accumulator + (*registers[registerIndex - 1]);
	int num = (int)accumulator.getBits().to_ulong();
	if (num < 0) lastResult = -1;
	else if (!num) lastResult = 0;
	else lastResult = 1;
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::add(int num) {
	
	accumulator + num;
	int n = (int)accumulator.getBits().to_ulong();
	if (n < 0) lastResult = -1;
	else if (!n) lastResult = 0;
	else lastResult = 1;
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::move(size_t registerIndex, int value) {
	if (value < 0) lastResult = -1;
	else if (!value) lastResult = 0;
	else lastResult = 1;

	(*registers[registerIndex - 1]) = value;
}


template<size_t N, size_t Bits>
void Processor<N, Bits>::start(const string& commandFile) {
	ifstream in(commandFile);
	if (!in) {
		cout << "here";
		return;
	}
	while (!in.eof()) {

		parser.reset();
		getline(in, commandString);
		parser.setLine(commandString);
		string command = parser.getNextToken();
		if (command == "move") {

			printTact();
			makeMoveOperation();
			printTact();
			tactsCounter = 1;
			++commandCounter;
		}
		else if (command == "add") {
			
			printTact();
			makeAddOperation();
			printTact();
			tactsCounter = 1;
			++commandCounter;
		}
	}
}
template<size_t N, size_t Bits>
void Processor<N, Bits>::makeMoveOperation() {

	
	string reg = parser.getNextToken();
	if (reg.size() == 2) {
		if (reg[0] != 'R') {
			//regIndex = stoi(reg.substr(1, 1));
			move(stoi(reg));
		}
		else if (reg[0] == 'R') {
			move(reg);
		}
		
	}
	else if (reg.size() == 1) {
		//string number = parser.getNextToken();
		int num = stoi(reg);
		move(num);
	}
	else {
		move(stoi(reg));
	}
	
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::move(int n) {

	int edge = static_cast<int>(pow(2, Bits));
	while (n > edge) {
		n -= edge;
	}
	while (n < -edge) {
		n += edge;
	}
	accumulator = n;
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::move(const string& str) {
	int regIndex = stoi(str.substr(1, 1));
	(*registers[regIndex - 1]) = accumulator;
}


template<size_t N, size_t Bits>
void Processor<N, Bits>::makeAddOperation() {
	string reg = parser.getNextToken();
	if (reg.size() == 2 && reg[0] == 'R') {
		add(stoi(reg.substr(1, reg.size() - 1)));
	}
	else if (reg.size() && reg[0] != 'R') {
		int regIndex = stoi(reg);
		add(regIndex);
	}
	
}

template<size_t N, size_t Bits>

void Processor<N, Bits>::add(const string& regIndex) {
	int registerIndex = stoi(regIndex);
	accumulator + (*registers[registerIndex - 1].getBits());
	int num = (int)accumulator.getBits().to_ulong();
	if (num < 0) lastResult = -1;
	else if (!num) lastResult = 0;
	else lastResult = 1;
}

template<size_t N, size_t Bits>
void Processor<N, Bits>::printTact() {

		cout <<"Comand: " << commandString << '\n';
		cout << "AC" << ' ' << accumulator.getBits() << '\n';
		for (int i = 0; i < registers.size(); ++i) {
			cout << "R" << i + 1 << ' ' << registers[i]->getBits() << '\n';
		}
		char sign{};
		if (lastResult < 0) sign = '-';
		else if (!lastResult) sign = '0';
		else sign = '+';
		cout << "PS" << ' ' << sign << '\n';
		cout << "PC" << ' ' << commandCounter << '\n';
		cout << "TC" << ' ' << tactsCounter++ << '\n' << '\n';

}