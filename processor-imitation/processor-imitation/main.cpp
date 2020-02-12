#include <bitset>
#include <iostream>
#include "Processor.h"
#include <bitset>

using std::cout;
using std::bitset;
int main() {
	string name = "proc.txt";
	Processor<4, 12> proc;
	proc.start(name);

	return 0;
}

