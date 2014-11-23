#include <stdexcept>


namespace custom
{

template <class Key, class Data>
hash_table<Key, Data>::hash_table(hash_table<Key, Data>::func_t f)
: exthash(f), _capacity(128), _size(0)
{
	table = new typename hash_table<Key, Data>::node[_capacity+2];

	table[0].prev = nullptr;
	table[0].next = &table[1];
	_begin = &table[0];

	for (int i=1; i<=_capacity; i++)
	{
		table[i].prev = &table[i-1];
		table[i].next = &table[i+1];
		table[i].data.state = FREE;
	}

	table[_capacity+1].prev = &table[_capacity];
	table[_capacity+1].next = nullptr;
	_end = &table[_capacity+1];
}

template <class Key, class Data>
hash_table<Key, Data>::hash_table(size_t cap, hash_table<Key, Data>::func_t f)
: exthash(f), _capacity(cap), _size(0)
{
	table = new typename hash_table<Key, Data>::node[_capacity+2];

	table[0].prev = nullptr;
	table[0].next = &table[1];
	_begin = &table[0];

	for (int i=1; i<=_capacity; i++)
	{
		table[i].prev = &table[i-1];
		table[i].next = &table[i+1];
		table[i].data.state = FREE;
	}

	table[_capacity+1].prev = &table[_capacity];
	table[_capacity+1].next = nullptr;
	_end = &table[_capacity+1];
}


template <class Key, class Data>
hash_table<Key, Data>::~hash_table()
{
	mem_clear();

	delete[] table;
}


template <class Key, class Data>
size_t hash_table<Key, Data>::size() const
{
	return _size;
}


template <class Key, class Data>
size_t hash_table<Key, Data>::hash(const Key& k) const
{
	return exthash(k) % _capacity + 1;
}


template <class Key, class Data>
Data& hash_table<Key, Data>::operator[](const Key& k)
{
	size_t idx = hash(k);

	typename hash_table<Key, Data>::node* it = &table[idx];
	while (it->next != &table[idx+1] && it->data.state != FREE && it->data.key != k) it = it->next;

	if (it->data.state == FREE)
	{
		it->data.state = OCCUPIED;
		it->data.key = k;
		++_size;

		return it->data.data;
	}
	else if (it->data.key == k)
	{
		return it->data.data;
	}
	else
	{
		typename hash_table<Key, Data>::node* newnode = new typename hash_table<Key, Data>::node;
		
		newnode->prev = it;
		newnode->next = &table[idx+1];
		table[idx+1].prev = newnode;

		newnode->data.key = k;
		newnode->data.state = EXTERNAL;

		it->next = newnode;

		++_size;
		
		return newnode->data.data;
	}
}


template <class Key, class Data>
const Data& hash_table<Key, Data>::operator[](const Key& k) const
{
	size_t idx = hash(k);

	if (table[idx].data.state == OCCUPIED)
	{
		typename hash_table<Key, Data>::node* it = &table[idx];
		while (it->next != &table[idx+1] && (it->data.state == FREE || it->data.key != k)) it = it->next;

		if (it->data.state != FREE && it->data.key == k) return it->data.data;
	}
 	throw std::runtime_error("Impossible to create new data for constant hash_table!");
}


template <class Key, class Data>
void hash_table<Key, Data>::erase(const Key& k)
{
	size_t idx = hash(k);

	if (table[idx].data.state == OCCUPIED)
	{
		typename hash_table<Key, Data>::node* it = &table[idx];
		while (it->next != &table[idx+1] && (it->data.state == FREE || it->data.key != k)) it = it->next;

		if (it->data.state != FREE && it->data.key == k)
		{
			if (it->data.state == EXTERNAL)
			{
				it->next->prev = it->prev;
				it->prev->next = it->next;
				delete it;
			}
			else
			{
				it->data.state = FREE;
			}

			--_size;

			return;
		}
	}
 	throw std::runtime_error("Impossible to delete unused key in hash_table!");
}


template <class Key, class Data>
void hash_table<Key, Data>::clear()
{
	mem_clear();

	for (int i=1; i<=_capacity; i++)
	{
		table[i].prev = &table[i-1];
		table[i].next = &table[i+1];
		table[i].data.state = FREE;
	}

	_size = 0;
}


template <class Key, class Data>
void hash_table<Key, Data>::mem_clear()
{
	for (int i=1; i<=_capacity; i++)
	{
		typename hash_table<Key, Data>::node* it = table[i].next;
		while (it != &table[i+1])
		{
			it = it->next;
			delete it->prev;
		}
	}	
}


}