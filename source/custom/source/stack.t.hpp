#include "../stack.h"

namespace custom
{

template <class T>
size_t stack<T>::size() const { return internal.size(); }

template <class T>
bool stack<T>::is_empty() const { return internal.is_empty(); }


template <class T>
const T& stack<T>::top() const { return internal.front(); }


template <class T>
void stack<T>::push(const T& o) { internal.push_front(o); }

template <class T>
T stack<T>::pop() { return internal.pop_front(); }


template <class T>
void stack<T>::clear() { return internal.clear(); }


template <class T>
bool stack<T>::includes(const T& x) { return internal.includes(x); }

}