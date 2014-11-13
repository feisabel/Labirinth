#include "../list.h"

<<<<<<< HEAD
#if __cplusplus < 201103L
#ifndef nullptr
	#define nullptr NULL
#endif
#endif

=======
>>>>>>> 81e952be2c43391bec246e1c1cb7b3bd19f7a154

namespace custom {

// nó da lista

// construtores (nó)
template <class T>
list<T>::node::node()
: prev(nullptr), next(nullptr)
{	
}

template <class T>
list<T>::node::node(const T& o)
: data(o), prev(nullptr), next(nullptr)
{
}



// lista

// construtor
template <class T>
list<T>::list()
: _size(0)
{
	_begin = new typename list<T>::node;
	_end   = new typename list<T>::node;

	_begin->next = _end;
	_end->prev = _begin;	
}

// destrutor
template <class T>
list<T>::~list()
{
	clear();

	delete _begin;
	delete _end;
}



// construtor de cópia
template <class T>
list<T>::list(const list<T>& o)
: _size(o._size)
{
	_begin = new typename list<T>::node;
	_end   = new typename list<T>::node;	

	mem_copy(o);
}

// atribuição
template <class T>
const list<T>& list<T>::operator= (const list<T>& o)
{
	if (&o != this)
	{	
		clear();
		
		mem_copy(o);

		_size = o._size;
	}
	return *this;
}



// tamanho da lista
template <class T>
size_t list<T>::size() const
{
	return _size;
}

// se está vazia
template <class T>
bool list<T>::is_empty() const
{
	return _size == 0;
}



// o primeiro elemento
template <class T>
const T& list<T>::front() const
{
	return _begin->next->data;
}

// o último elemento
template <class T>
const T& list<T>::back() const
{
	return _end->prev->data;
}

// o elemento que está na posição dada
template <class T>
const T& list<T>::at(size_t pos) const
{
	return search(pos)->data;;
}



// insere um elemento no começo
template <class T>
void list<T>::push_front(const T& o)
{
	typename list<T>::node* newnode = new node(o);

	newnode->prev = _begin;
	newnode->next = _begin->next;
	_begin->next->prev = newnode;
	_begin->next = newnode;

	++_size;
}

// insere um elemento no fim
template <class T>
void list<T>::push_back(const T& o)
{
	typename list<T>::node* newnode = new node(o);

	newnode->next = _end;
	newnode->prev = _end->prev;
	_end->prev->next = newnode;
	_end->prev = newnode;

	++_size;
}

// insere um elemento na posição dada
template <class T>
void list<T>::insert(const T& o, size_t pos)
{
	typename list<T>::node* newnode = new typename list<T>::node(o);
	
	typename list<T>::node* it;
	if (pos == _size) {
		it = _end;
	} else {
		it = search(pos);
	}

	newnode->prev = it->prev;
	newnode->next = it;

	it->prev->next = newnode;
	it->prev = newnode;

	++_size;
}



// remove o primeiro elemento
template <class T>
T list<T>::pop_front()
{
	typename list<T>::node* tmp = _begin->next;

	_begin->next = _begin->next->next;
	_begin->next->prev = _begin;

	T x = tmp->data;
	delete tmp;

	--_size;

	return x;
}

// remove o último elemento
template <class T>
T list<T>::pop_back()
{	
	typename list<T>::node* tmp = _end->prev;

	_end->prev = _end->prev->prev;
	_end->prev->next = _end;

	T x = tmp->data;
	delete tmp;

	--_size;

	return x;
}

// remove o elemento da posição dada
template <class T>
T list<T>::remove(size_t pos)
{	
	typename list<T>::node* tmp = search(pos);

	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	T x = tmp->data;
	
	delete tmp;

	--_size;

	return x;
}

// limpa a lista
template <class T>
void list<T>::clear()
{
	typename list<T>::node* it = _begin->next;

	while (it != _end) {
		it = it->next;
		delete it->prev;
	}
}



// interna: procura o nó que corresponde à posição dada
template <class T>
typename list<T>::node* list<T>::search(size_t pos) const
{
	typename list<T>::node* it = nullptr;

	if (0 <= pos && pos <= _size/2)
	{
		it = _begin->next;
		for (size_t i=0; i<pos; i++)
		{
			it = it->next;
		}
	}
	else if (_size/2 < pos && pos < _size)
	{
		it = _end->prev;
		for (size_t i=_size-1; i>pos; i--)
		{
			it = it->prev;
		}
	}

	return it;
}


// interna: copia os elementos de uma lista pra outra
template <class T>
void list<T>::mem_copy(const list<T>& o)
{	
	typename list<T>::node* it;
	typename list<T>::node* itt = _begin;
	for (it = o._begin; it->next != o._end; it = it->next )
	{
		itt->next = new typename list<T>::node(it->data);
		itt->next->prev = itt;
		itt = itt->next;
	}

	itt->next = _end;
}


template <class T>
bool list<T>::includes (const T& x)
{
	typename list<T>::node* it;
	for (it = _begin->next; it != _end; it = it->next)
	{
		if (it->data == x) return true;
	}
	return false;
}


}