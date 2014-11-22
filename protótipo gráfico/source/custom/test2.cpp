#include "hash_table.h"
#include <string>
#include <iostream>

using custom::hash_table;

size_t hashf(std::string s)
{
	return s.size();
}

int main(int argc, char const *argv[])
{
	hash_table<std::string, int> hash(hashf);
	
	hash["one"] = 1;
	hash["two"] = 2;

	std::cout << hash["one"] << std::endl;
	std::cout << hash["two"] << std::endl;

	return 0;
}