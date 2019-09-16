#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

template<typename T>
struct Plus {
private:
	T a;
public:
	Plus(T firstOperand) : a{ firstOperand } {}
	T operator()(T b) { return a + b; }
};

template<typename T>
struct Minus {
private:
	T a;
public:
	Minus(T firstOperand) : a{ firstOperand } {}
	T operator()(T b) { return a - b; }
};

template<typename T>
struct Multiply {
private:
	T a;
public:
	Multiply(T firstOperand) : a{ firstOperand } {}
	T operator()(T b) { return a * b; }
};

template<typename T>
struct Divide {
private:
	T a;
public:
	Divide(T firstOperand) : a{ firstOperand } {}
	T operator()(T b) { return b == 0 ? 1 : a / b; }
};



#endif // OPERATIONS_H_INCLUDED