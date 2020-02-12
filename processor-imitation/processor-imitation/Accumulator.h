#pragma once
#include <bitset>
#include "Register.h"

using std::bitset;


template<size_t N>
class Accumulator {
private:

	bitset<N> result;
	void addRegisterValue(bitset<N>&);
	bool fullAdder(bool, bool, bool&);
	
public:
	bitset<N>& getBits() { return result; }
	
	Accumulator<N>& operator+(bitset<N>& set) {
		addRegisterValue(set);
		return (*this);
	};
	Accumulator<N>& operator+(int n) {
		bitset<N> set(n);
		addRegisterValue(set);
		return (*this);
	};
	Accumulator<N> operator=(int n) {
		bitset<N> set(n);
		result = set;
		return (*this);
	}
	
};





/*addRegisterValue(reg.getBits());
	return (*this);*/


template<size_t N>
void Accumulator<N>::addRegisterValue( bitset<N>& set) {
	bool carry = false;
	for (int i = 0; i < N; ++i){
		result[i] = fullAdder(result[i], set[i], carry);
	}

}

template<size_t N>
bool Accumulator<N>::fullAdder(bool b1, bool b2, bool& carry) {
	bool sum = (b1 ^ b2) ^ carry;
	carry = (b1 && b2) || (b1 && carry) || (b2 && carry);
	return sum;
}