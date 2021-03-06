namespace custom
{

template <class T>
size_t queue<T>::size() const { return internal.size(); }

template <class T>
bool queue<T>::empty() const { return internal.empty(); }


template <class T>
const T& queue<T>::front() const { return internal.front(); }


template <class T>
void queue<T>::push(const T& o) { internal.push_back(o); }

template <class T>
T queue<T>::pop() { return internal.pop_front(); }


template <class T>
void queue<T>::clear() { return internal.clear(); }


template <class T>
bool queue<T>::includes(const T& x) { return internal.includes(x); }

}