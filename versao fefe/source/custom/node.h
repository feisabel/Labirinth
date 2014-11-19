#ifndef __NODE
#define __NODE


#if __cplusplus < 201103L
#ifndef nullptr
	#define nullptr NULL
#endif
#endif


namespace custom
{

template <class T>
struct _node
{
	T data;

	_node<T>* prev;
	_node<T>* next;

	_node();
	_node(const T&);
};

}


#include "source/node.t.hpp"

#endif