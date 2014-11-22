#ifndef __REVERSE_ITERATOR
#define __REVERSE_ITERATOR

#include "node.h"


namespace custom
{

template <class T>
class list;

template <class T>
class _const_reverse_iterator;

template <class T>
class _reverse_iterator
{
public:
	_reverse_iterator();
	_reverse_iterator(_node<T>*);
	
	T& operator*() const;
	T* operator->() const;

	_reverse_iterator<T>& operator++();
	_reverse_iterator<T> operator++(int);

	_reverse_iterator<T>& operator--();
	_reverse_iterator<T> operator--(int);

	bool operator== (const _reverse_iterator<T>&);
	bool operator== (const _const_reverse_iterator<T>&);

	bool operator!= (const _reverse_iterator<T>&);
	bool operator!= (const _const_reverse_iterator<T>&);

private:
	_node<T>* pointer;

	friend class _const_reverse_iterator<T>;
	friend class list<T>;
};


template <class T>
class _const_reverse_iterator
{
public:
	_const_reverse_iterator();
	_const_reverse_iterator(_node<T>*);
	
	_const_reverse_iterator<T>& operator= (_reverse_iterator<T>&);

	const T& operator*() const;
	const T* operator->() const;

	_const_reverse_iterator<T>& operator++();
	_const_reverse_iterator<T> operator++(int);

	_const_reverse_iterator<T>& operator--();
	_const_reverse_iterator<T> operator--(int);

	bool operator== (const _reverse_iterator<T>&);
	bool operator== (const _const_reverse_iterator<T>&);

	bool operator!= (const _reverse_iterator<T>&);
	bool operator!= (const _const_reverse_iterator<T>&);

private:
	const _node<T>* pointer;

	friend class _reverse_iterator<T>;
	friend class list<T>;
};


}


#include "source/reverse_iterator.t.hpp"

#endif