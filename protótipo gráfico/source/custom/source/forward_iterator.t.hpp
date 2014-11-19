namespace custom
{
	
// iterador

// construtor (iterador)
template <class T>
_forward_iterator<T>::_forward_iterator()
: pointer(nullptr)
{
}

template <class T>
_forward_iterator<T>::_forward_iterator(_node<T>* ptr)
: pointer(ptr)
{
}


// operador de dereferenciação
template <class T>
T& _forward_iterator<T>::operator*() const
{
	return pointer->data;
}


// operadores de avanço
template <class T>
_forward_iterator<T>& _forward_iterator<T>::operator++()
{
	pointer = pointer->next;
	return *this;
}

template <class T>
_forward_iterator<T> _forward_iterator<T>::operator++(int)
{
	_forward_iterator<T> it = *this;
	pointer = pointer->next;
	return it;
}

template <class T>
_forward_iterator<T>& _forward_iterator<T>::operator--()
{
	pointer = pointer->prev;
	return *this;
}

template <class T>
_forward_iterator<T> _forward_iterator<T>::operator--(int)
{
	_forward_iterator<T> it = *this;
	pointer = pointer->prev;
	return it;
}


// operadores de comparação
template <class T>
bool _forward_iterator<T>::operator== (const _forward_iterator<T>& it)
{
	return it.pointer == pointer;
}

template <class T>
bool _forward_iterator<T>::operator== (const _const_forward_iterator<T>& it)
{
	return it.pointer == pointer;
}

template <class T>
bool _forward_iterator<T>::operator!= (const _forward_iterator<T>& it)
{
	return !operator==(it);
}

template <class T>
bool _forward_iterator<T>::operator!= (const _const_forward_iterator<T>& it)
{
	return !operator==(it);
}




// iterador de const

// construtor (iterador)
template <class T>
_const_forward_iterator<T>::_const_forward_iterator()
: pointer(nullptr)
{
}

template <class T>
_const_forward_iterator<T>::_const_forward_iterator(_node<T>* ptr)
: pointer(ptr)
{
}


// operador de dereferenciação
template <class T>
const T& _const_forward_iterator<T>::operator*() const
{
	return pointer->data;
}


// operadores de avanço
template <class T>
_const_forward_iterator<T>& _const_forward_iterator<T>::operator++()
{
	pointer = pointer->next;
	return *this;
}

template <class T>
_const_forward_iterator<T> _const_forward_iterator<T>::operator++(int)
{
	_const_forward_iterator<T> it = *this;
	pointer = pointer->next;
	return it;
}

template <class T>
_const_forward_iterator<T>& _const_forward_iterator<T>::operator--()
{
	pointer = pointer->prev;
	return *this;
}

template <class T>
_const_forward_iterator<T> _const_forward_iterator<T>::operator--(int)
{
	_const_forward_iterator<T> it = *this;
	pointer = pointer->prev;
	return it;
}


// operadores de comparação
template <class T>
bool _const_forward_iterator<T>::operator== (const _forward_iterator<T>& it)
{
	return it.pointer == pointer;
}

template <class T>
bool _const_forward_iterator<T>::operator== (const _const_forward_iterator<T>& it)
{
	return it.pointer == pointer;
}

template <class T>
bool _const_forward_iterator<T>::operator!= (const _forward_iterator<T>& it)
{
	return !operator==(it);
}

template <class T>
bool _const_forward_iterator<T>::operator!= (const _const_forward_iterator<T>& it)
{
	return !operator==(it);
}


}