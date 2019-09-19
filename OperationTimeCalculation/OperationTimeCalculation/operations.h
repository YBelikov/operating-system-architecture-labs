#ifndef OPERATIONS_H_INCLUDED
#define OPERATIONS_H_INCLUDED

template<typename T>
struct Plus {
	T operator()(T a, T b) { return a + b; }
};

template<typename T>
struct Minus {
	T operator()(T a, T b) { return a - b; }
};

template<typename T>
struct Multiply {
	T operator()(T a , T b) { return a * b; }
};

template<typename T>
struct Divide {
	T operator()(T a, T b) { return b == 0 ? 1 : a / b; }
};



#endif // OPERATIONS_H_INCLUDED