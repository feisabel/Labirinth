#include "../resource_manager.h"


size_t hashf(std::string s)
{
    size_t sum = 0;
    for (size_t i = 0; i < s.size()/2; i++)
    {
        sum += 7*s[i] + 5*s[s.size()-i-1];
    }
}


hash_table<std::string, sf::Texture> ResourceManager::textures(hashf);


void ResourceManager::load()
{
	sf::Texture wall;
	if (!wall.loadFromFile("wall1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["wall"] = wall;


    sf::Texture floor;
    if (!floor.loadFromFile("floor1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["floor"] = floor;


    sf::Texture trap_off;
    if (!trap_off.loadFromFile("trap_off3.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["trap_off"] = trap_off;


    sf::Texture trap_on;
    if (!trap_on.loadFromFile("trap_on3.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["trap_on"] = trap_on;


    sf::Texture spawn;
    if (!spawn.loadFromFile("spawn1.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["spawn"] = spawn;


    sf::Texture monster_front;
    if (!monster_front.loadFromFile("skeleton_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["monster_front"] = monster_front;


    sf::Texture ammo;
    if (!ammo.loadFromFile("ammo.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["ammo"] = ammo;


    sf::Texture med;
    if (!med.loadFromFile("medkit.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["med"] = med;


    sf::Texture char_back;
    if (!char_back.loadFromFile("char_back.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["char_back"] = char_back;


    sf::Texture char_front;
    if (!char_front.loadFromFile("char_front.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["char_front"] = char_front;


    sf::Texture char_left;
    if (!char_left.loadFromFile("char_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["char_left"] = char_left;


    sf::Texture char_right;
    if (!char_right.loadFromFile("char_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["char_right"] = char_right;

	    
    sf::Texture bullet_down;
    if (!bullet_down.loadFromFile("bullet_down.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["bullet_down"] = bullet_down;
    

    sf::Texture bullet_up;
    if (!bullet_up.loadFromFile("bullet_up.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["bullet_up"] = bullet_up;
    

    sf::Texture bullet_left;
    if (!bullet_left.loadFromFile("bullet_left.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["bullet_left"] = bullet_left;
    

    sf::Texture bullet_right;
    if (!bullet_right.loadFromFile("bullet_right.png"))
    {
        std::cout << "erro de textura" << std::endl;
        return;
    }
    textures["bullet_right"] = bullet_right;
}