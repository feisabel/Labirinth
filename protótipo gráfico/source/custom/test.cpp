#include <iostream>
#include "list.h"
using custom::list;


int main(int argc, char const *argv[])
{
	list< list<int> > l;

	int n;
	std::cin >> n;
	while (n--)
	{
		list<int> ll;

		int x;
		while (std::cin >> x && x != 0)
		{
			ll.push_back(x);
		}

		l.push_back(ll);
	}

	list< list<int> >::iterator it;
	for (it = l.begin(); it != l.end(); it++)
	{
		list<int> ll = *it;
		list<int>::iterator itt;
		for (itt = ll.begin(); itt != ll.end(); itt++)
		{
			std::cout << *itt << std::endl;
		}
	}

	return 0;
}