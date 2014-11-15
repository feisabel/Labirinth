#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

class SceneManager
{
public:
    SceneManager(){}
   //virtual void init();
    virtual void draw();
    virtual void display();
    static sf::RenderWindow window;
   // Scene currScene;

};

class Menu : SceneManager
{
public:
    void draw();
    void display();
    Menu(): buttonInit(sf::Vector2f(200, 45)), title_teste(sf::Vector2f(300, 45)) {}
protected:
    sf::RectangleShape buttonInit;
    sf::RectangleShape title_teste;
    sf::Text text;
    sf::Text title;
    sf::Font font;
};

