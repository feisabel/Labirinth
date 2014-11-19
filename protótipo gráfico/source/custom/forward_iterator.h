#ifndef __FORWARD_ITERATOR
#define __FORWARD_ITERATOR

#include "node.h"


namespace custom
{

template <class T>
class list;

template <class T>
class _const_forward_iterator;

template <class T>
class _forward_iterator
{
public:
	_forward_iterator();
	_forward_iterator(_node<T>*);
	
	T& operator*() const;

	_forward_iterator<T>& operator++();
	_forward_iterator<T> operator++(int);

	_forward_iterator<T>& operator--();
	_forward_iterator<T> operator--(int);

	bool operator== (const _forward_iterator<T>&);
	bool operator== (const _const_forward_iterator<T>&);

	bool operator!= (const _forward_iterator<T>&);
	bool operator!= (const _const_forward_iterator<T>&);

private:
	_node<T>* pointer;

	friend class _const_forward_iterator<T>;
	friend class list<T>;
};


template <class T>
class _const_forward_iterator
{
public:
	_const_forward_iterator();
	_const_forward_iterator(_node<T>*);
	
	_const_forward_iterator<T>& operator= (_forward_iterator<T>&);

	const T& operator*() const;

	_const_forward_iterator<T>& operator++();
	_const_forward_iterator<T> operator++(int);

	_const_forward_iterator<T>& operator--();
	_const_forward_iterator<T> operator--(int);

	bool operator== (const _forward_iterator<T>&);
	bool operator== (const _const_forward_iterator<T>&);

	bool operator!= (const _forward_iterator<T>&);
	bool operator!= (const _const_forward_iterator<T>&);

private:
	const _node<T>* pointer;

	friend class _forward_iterator<T>;
	friend class list<T>;
};


}


#include "source/forward_iterator.t.hpp"

#endif