#include "../deque.h"

namespace custom
{

template <class T>
size_t deque<T>::size() const { return internal.size(); }

template <class T>
bool deque<T>::is_empty() const { return internal.is_empty(); }


template <class T>
const T& deque<T>::front() const { return internal.front(); }

template <class T>
const T& deque<T>::back() const { return internal.back(); }


template <class T>
void deque<T>::push_front(const T& o) { internal.push_front(o); }

template <class T>
void deque<T>::push_back(const T& o) { internal.push_back(o); }


template <class T>
T deque<T>::pop_front() { return internal.pop_front(); }

template <class T>
T deque<T>::pop_back() { return internal.pop_back(); }


template <class T>
void deque<T>::clear() { return internal.clear(); }

}