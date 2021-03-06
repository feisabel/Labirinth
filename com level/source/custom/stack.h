#ifndef __STACK
#define __STACK

#include "list.h"

namespace custom
{

template <class T>
class stack
{
	list<T> internal;

public:
	size_t size() const;
	bool empty() const;

	const T& top() const;
	
	void push(const T&);
	T pop();

	void clear();

	bool includes(const T& x);
};

}

#include "source/stack.t.hpp"


#endif