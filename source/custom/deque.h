#ifndef __DEQUE
#define __DEQUE

#include "list.h"

namespace custom
{

template <class T>
class deque
{
	list<T> internal;

public:
	size_t size() const;
	bool is_empty() const;

	const T& front() const;
	const T& back() const;
	
	void push_front(const T&);
	void push_back(const T&);

	T pop_front();
	T pop_back();

	void clear();

	bool includes(const T& x);
};

}

#include "source/deque.t.hpp"


#endif