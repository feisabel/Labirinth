#ifndef __MENU
#define __MENU

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "scene.h"

class Main;

struct Button
{
	sf::RectangleShape rect;
	sf::Text content;
	unsigned int v_padding;
	unsigned int h_padding;

	Button()
	: v_padding(5), h_padding(5)
	{
	}

	void setPosition(const sf::Vector2f& v)
	{
		rect.setPosition(v);
		content.setPosition(sf::Vector2f(v.x+v_padding, v.y+h_padding));
	}
};


class Menu : public Scene
{
public:
    void redraw();
    void update();
    Menu();

private:
    //Button button[3];
    //sf::RectangleShape title_teste;
    //sf::Text title;
    //sf::Font font;

    sf::Texture background;
    sf::Sprite spriteBackground;
};

#endif
