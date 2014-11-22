#include "list.h"
#include <iostream>

using custom::list;


int main(int argc, char const *argv[])
{
	list<int> l;

	int x;
	while (std::cin >> x && x != 0)
	{
		l.push_back(x);
	}

	list<int>::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	l.clear();

	while (std::cin >> x && x != 0)
	{
		l.push_back(x);
	}

	for (it = l.begin(); it != l.end(); it++)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}