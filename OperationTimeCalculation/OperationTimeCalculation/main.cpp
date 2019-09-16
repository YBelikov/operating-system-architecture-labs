#include <chrono>
#include <iostream>
#include <initializer_list>

#include "operations.h"

using namespace std::chrono;
using std::initializer_list;

template<typename T, typename Op, typename Clock = high_resolution_clock>
void f(int iterationsNum) {

	T a{};

	Op op{a};
	
	auto startPoint = Clock::now();

	for (int i = 2; i < iterationsNum; ++i) {
		op(i);
	}
	auto endPoint = Clock::now();
	auto diff = endPoint - startPoint;
	
	auto startPoint1 = Clock::now();
	for (int i = 0; i < iterationsNum; ++i);
	auto endPoint1 = Clock::now();
	
	auto diff1 = endPoint1 - startPoint1;
	std::cout << duration_cast<nanoseconds>(diff - diff1).count() << "ns\n";
}
template<typename T> 
void evaluateAllOperations(int calcNumber) {

	f<T, Plus<T>>(calcNumber);
	f<T, Minus<T>>(calcNumber);
	f<T, Multiply<T>>(calcNumber);
	f<T, Divide<T>>(calcNumber);

}

void calculate(int calcNumber) {
	
		evaluateAllOperations<int>(calcNumber);
		evaluateAllOperations<char>(calcNumber);
		evaluateAllOperations<double>(calcNumber);
		evaluateAllOperations<float>(calcNumber);
	
}

int main() {

	calculate(1e6);
	return 0;
}
