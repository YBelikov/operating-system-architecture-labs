#pragma once
#include <bitset>
#include "Accumulator.h"

using std::bitset;

template<size_t N>

class Register {

private:
	
	bitset<N> bits;
	bitset<N> convertToBitset(int);
public:
	
	Register& operator=(int value) {
		bits = convertToBitset(value);
		return (*this); 
	};
	Register operator+(const Register&);
	bitset<N>& getBits() { return bits; }
	Register<N> operator=(Accumulator<N> ac) {
		bits = ac.getBits();
		return (*this);
	}
};

template<size_t N>
bitset<N> Register<N>::convertToBitset(int n) {
	bitset<N> temp;
	bool isNegative = n < 0;
	n = std::abs(n);
	for (int i = 0; i < N && n > 0; ++i, n /= 2) {
		temp.set(i, (bool)(n % 2));
	}
	if (isNegative) {
		temp.flip();
		int rem = 0, i = 0;
		do {
			rem = temp.test(i);
			temp[i].flip();
			++i;
		} while (i < N && rem);
	}
	return temp;
}