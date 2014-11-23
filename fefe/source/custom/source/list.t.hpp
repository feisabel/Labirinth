#include <stdexcept>

namespace custom
{

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
bool list<T>::empty() const
{
	return _size == 0;
}



// iterador pro início
template <class T>
typename list<T>::iterator list<T>::begin()
{
	return list<T>::iterator(_begin->next);
}

template <class T>
typename list<T>::const_iterator list<T>::begin() const
{
	return list<T>::const_iterator(_begin->next);
}


// iterador pro início (inverso)
template <class T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
	return list<T>::reverse_iterator(_end->prev);
}

template <class T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const
{
	return list<T>::const_reverse_iterator(_end->prev);
}


// iterador pro fim
template <class T>
typename list<T>::const_iterator list<T>::end() const
{
	return list<T>::const_iterator(_end);
}

// iterador pro fim
template <class T>
typename list<T>::const_reverse_iterator list<T>::rend() const
{
	return list<T>::const_reverse_iterator(_begin);
}



// o primeiro elemento
template <class T>
const T& list<T>::front() const
{	
	if (_size == 0) throw std::runtime_error("Invalid front_access: list is empty!");
	return _begin->next->data;
}

// o último elemento
template <class T>
const T& list<T>::back() const
{
	if (_size == 0) throw std::runtime_error("Invalid back_access: list is empty!");
	return _end->prev->data;
}

// o elemento que está na posição dada
template <class T>
const T& list<T>::at(size_t pos) const
{	
	if (_size == 0) throw std::runtime_error("Invalid at_access: list is empty!");
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

// remove o primeiro elemento
template <class T>
T list<T>::pop_front()
{
	if (_size == 0) throw std::runtime_error("Invalid pop_front_deletion: list is empty!");
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
	if (_size == 0) throw std::runtime_error("Invalid pop_back_deletion: list is empty!");
	typename list<T>::node* tmp = _end->prev;

	_end->prev = _end->prev->prev;
	_end->prev->next = _end;

	T x = tmp->data;
	delete tmp;

	--_size;

	return x;
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

// insere um elemento na posição dada
template <class T>
void list<T>::insert(const T& o, list<T>::iterator& it)
{
	typename list<T>::node* newnode = new typename list<T>::node(o);

	newnode->prev = it.pointer->prev;
	newnode->next = it.pointer;

	it.pointer->prev->next = newnode;
	it.pointer->prev = newnode;

	--it;

	++_size;
}

// insere um elemento na posição dada
template <class T>
void list<T>::insert(const T& o, list<T>::reverse_iterator& it)
{
	typename list<T>::node* newnode = new typename list<T>::node(o);

	newnode->prev = it.pointer;
	newnode->next = it.pointer->next;

	it.pointer->next->prev = newnode;
	it.pointer->next = newnode;

	--it;

	++_size;
}



// remove o elemento da posição dada
template <class T>
T list<T>::erase(size_t pos)
{	
	if (pos >= _size) throw std::runtime_error("Invalid erase_deletion: list is empty!");
	typename list<T>::node* tmp = search(pos);

	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	T x = tmp->data;
	
	delete tmp;

	--_size;

	return x;
}

// remove o elemento da posição dada
template <class T>
T list<T>::erase(const list<T>::iterator& it)
{	
	if (_size == 0) throw std::runtime_error("Invalid erase_deletion: list is empty!");
	it.pointer->prev->next = it.pointer->next;
	it.pointer->next->prev = it.pointer->prev;

	T x = *it;

	delete it.pointer;

	--_size;

	return x;
}

// remove o elemento da posição dada
template <class T>
T list<T>::erase(const list<T>::reverse_iterator& it)
{	
	if (_size == 0) throw std::runtime_error("Invalid erase_deletion: list is empty!");
	it.pointer->prev->next = it.pointer->next;
	it.pointer->next->prev = it.pointer->prev;

	T x = *it;

	delete it.pointer;

	--_size;

	return x;
}



// limpa a lista
template <class T>
void list<T>::clear()
{
	typename list<T>::node* it = _begin->next;

	while (it != _end)
	{
		it = it->next;
		delete it->prev;
	}

	_begin->next = _end;
	_end->prev = _begin;

	_size = 0;
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
	for (it = o._begin; it->next != o._end; it = it->next)
	{
		itt->next = new typename list<T>::node(it->next->data);
		itt->next->prev = itt;
		itt = itt->next;
	}

	itt->next = _end;
	_end->prev = itt;
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