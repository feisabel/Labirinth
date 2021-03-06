#ifndef __QUEUE
#define __QUEUE

#include "list.h"

namespace custom
{

template <class T>
class queue
{
	list<T> internal;

public:
	size_t size() const;
	bool empty() const;

	const T& front() const;
	
	void push(const T&);
	T pop();

	void clear();

	bool includes(const T& x);
};

}

#include "source/queue.t.hpp"


#endif