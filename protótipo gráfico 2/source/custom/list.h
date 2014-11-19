#ifndef __LIST
#define __LIST

#include <cstddef>


#include "node.h"
#include "iterator.h"


namespace custom
{

template <class T>
class list
{
public:
	typedef _forward_iterator<T> 		iterator;
	typedef _const_forward_iterator<T> 	const_iterator;
	typedef _reverse_iterator<T> 		reverse_iterator;
	typedef _const_reverse_iterator<T>	const_reverse_iterator;

	list();
	~list();

	list(const list<T>&);
	const list<T>& operator= (const list<T>&);

	size_t size() const;
	bool empty() const;

	iterator begin();
	reverse_iterator rbegin();

	const_iterator begin() const;
	const_reverse_iterator rbegin() const;

	const_iterator end() const;
	const_reverse_iterator rend() const;

	const T& front() const;
	const T& back() const;
    T& at(size_t);

	void push_front(const T&);
	void push_back(const T&);

	T pop_front();
	T pop_back();

	void insert(const T&, size_t);
	void insert(const T&, iterator&);
	void insert(const T&, reverse_iterator&);

	T erase(size_t);
	T erase(const iterator&);
	T erase(const reverse_iterator&);

	void clear();

	bool includes(const T& x);

private:
	typedef _node<T> node;

	node* _begin;
	node* _end;

	size_t _size;

	node* search(size_t pos) const;
	void mem_copy(const list<T>&);
};

}

#include "source/list.t.hpp"

#endif
