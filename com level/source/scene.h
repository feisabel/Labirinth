#ifndef __SCENE
#define __SCENE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 560;
const int WINDOW_HEIGHT = 560;

class Scene
{
public:
	Scene () : b_redraw(true) {}
    virtual void update() = 0;
    virtual void redraw() = 0;

    static void close();
    
    bool b_redraw;

protected:
    static sf::RenderWindow window;
};

#endif