#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "operations.h"

using namespace std::chrono;
using std::vector;
using std::string;

#pragma optimize("", off);
template<typename T, typename Op, typename Clock = high_resolution_clock>
double f(int iterationsNum) {

	T a = 5, b = 7;

	Op op{};
	
	auto startPoint = Clock::now();

	for (int i = 2; i < iterationsNum; ++i) {
		op(a , b);
	}
	auto endPoint = Clock::now();
	auto diff = endPoint - startPoint;
	
	auto startPoint1 = Clock::now();
	for (int i = 0; i < iterationsNum; ++i);
	auto endPoint1 = Clock::now();
	
	auto diff1 = endPoint1 - startPoint1;
	return duration_cast<nanoseconds>(diff - diff1).count();
}
template<typename T> 
vector<double> evaluateAllOperations(int numberOfTests, int calcNumber) {
	vector<double> operations;
	double add{}, sub{}, div{}, mult{};
	for (int i = 0; i < numberOfTests; ++i) {
		add += f<T, Plus<T>>(calcNumber);
		sub += f<T, Minus<T>>(calcNumber);
		mult += f<T, Multiply<T>>(calcNumber);
		div += f<T, Divide<T>>(calcNumber);
	}
	add =  numberOfTests * calcNumber / add * 1e9;
	sub =  numberOfTests * calcNumber / sub * 1e9;
	div = numberOfTests * calcNumber / div * 1e9;
	mult = numberOfTests * calcNumber / mult * 1e9;
	operations.push_back(add);
	operations.push_back(sub);
	operations.push_back(div);
	operations.push_back(mult);
	return operations;
}

void calculate(int numberOfTests, int calcNumber) {
	vector<string> types{ "float", "double", "char", "int", "long" };
	vector<char> operations{'+', '-', '/', '*'};
	vector<vector<double>> results{};
	results.push_back(evaluateAllOperations<float>(numberOfTests, calcNumber));
	results.push_back(evaluateAllOperations<double>(numberOfTests, calcNumber));
	results.push_back(evaluateAllOperations<char>(numberOfTests, calcNumber));
	results.push_back(evaluateAllOperations<int>(numberOfTests, calcNumber));
	results.push_back(evaluateAllOperations<long>(numberOfTests, calcNumber));

	double maxVal = results.at(0).at(0);
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (maxVal < results.at(i).at(j)) {
				maxVal = results.at(i).at(j);
			}
		}
	}
	int maxLen{ 25 };
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout.width(9);
			std::cout <<std::left << std::setw(9) << types[i];
			std::cout << operations[j] <<"          "; 
			std::cout.precision(2);
			std::cout << std::scientific;
			std::cout << results.at(i).at(j) << "       ";
			std::cout << std::fixed;
			std::cout.width(6);
			std::cout <<std::left << std::setw(6) << (double)(results.at(i).at(j)) / maxVal * 100 << "%" << "       ";
			string s{};
			for (int k = 0; k < (double)(results.at(i).at(j)) / maxVal * maxLen; ++k) {
				s += "X";
			}
			std::cout.width(20);
			std::cout <<std::left << std::setw(20) << s << '\n';
		}
		std::cout << "===============================================================================" << std::endl;
	}
}

int main() {

	calculate(10, static_cast<int>(1e6));
	system("pause");
	return 0;
}
