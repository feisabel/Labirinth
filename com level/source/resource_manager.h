#ifndef __RESOURCE_MANAGER
#define __RESOURCE_MANAGER

#include <string>
#include <SFML/Graphics.hpp>

#include "custom/hash_table.h"
using custom::hash_table;


class ResourceManager
{
public:
	static hash_table<std::string, sf::Texture> textures;

	static void load();
};

size_t hash(std::string);

#endif
