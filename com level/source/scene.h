#ifndef __SCENE
#define __SCENE

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 560;
const int WINDOW_HEIGHT = 560;

/*
	Classe abstrata para representar as cenas
*/
class Scene
{
public:
	Scene () : b_redraw(true) {}
    virtual void update() = 0; //método virtual que é implementado pelas classes filhas
    virtual void redraw() = 0;

    static void close();
    
    bool b_redraw; //variável que indica se precisa desenhar novamente na tela 

protected:
    static sf::RenderWindow window;
};

#endif