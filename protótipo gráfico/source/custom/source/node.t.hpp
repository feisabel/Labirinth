namespace custom
{

// construtores
template <class T>
_node<T>::_node()
: prev(nullptr), next(nullptr)
{	
}

template <class T>
_node<T>::_node(const T& o)
: data(o), prev(nullptr), next(nullptr)
{
}

}