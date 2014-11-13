#ifndef __LIST
#define __LIST

#include <cstddef>

namespace custom
{

template <class T>
class list
{
public:
	list();
	~list();

	list(const list<T>&);
	const list<T>& operator= (const list<T>&);

	size_t size() const;
	bool is_empty() const;

	const T& front() const;
	const T& back() const;
	const T& at(size_t) const;

	void push_front(const T&);
	void push_back(const T&);
	void insert(const T&, size_t);

	T pop_front();
	T pop_back();
	T remove(size_t);
	void clear();

	bool includes(const T& x);

private:
	struct node;

	node* _begin;
	node* _end;

	size_t _size;

	node* search(size_t pos) const;
	void mem_copy(const list<T>&);
};


template <class T>
struct list<T>::node {
	T data;

	node* prev;
	node* next;

	node();
	node(const T&);
};

}

#include "source/list.t.hpp"

#endif