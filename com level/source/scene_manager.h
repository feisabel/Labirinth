#ifndef __SCENE_MANAGER
#define __SCENE_MANAGER

#include "scene.h"

//classe que administra as cenas
class SceneManager
{
	static Scene* current_scene; //ponteiro estático para a cena mostrada na janela

public:
	static void update() { current_scene->update(); } //chama o update da cena atual
	static void redraw() { current_scene->redraw(); } //chama o redraw da cena atual

	static void change_scene(Scene& s) //método para trocar a cena atual
	{
		current_scene = &s;
		current_scene->b_redraw = true;
	}
};


#endif
