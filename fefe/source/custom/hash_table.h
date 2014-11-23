#ifndef __HASH
#define __HASH

#include <cstddef>

#include "node.h"

namespace custom
{

enum state_t {FREE, OCCUPIED, EXTERNAL};
template <class Key, class Data>
struct _pair_state
{
	Key key;
	Data data;
	state_t state;
};

template <class Key, class Data>
class hash_table
{
	typedef size_t (*func_t) (Key);
public:

	hash_table(func_t);
	hash_table(size_t, func_t);
	~hash_table();

	size_t size() const;

	size_t hash(const Key&) const;

	Data& operator[](const Key&);
	const Data& operator[](const Key&) const;

	void erase(const Key&);

	void clear();

private:
	typedef _node< _pair_state<Key, Data> > node;

	node* table;

	node* _begin;
	node* _end;

	func_t exthash;

	const size_t _capacity;
	size_t _size;

	void mem_clear();
};


}


#include "source/hash_table.t.hpp"


#endif