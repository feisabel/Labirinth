#ifndef __SCENE_MANAGER
#define __SCENE_MANAGER

#include "scene.h"

class SceneManager
{
	static Scene* current_scene;

public:
	static void update() { current_scene->update(); }
	static void redraw() { current_scene->redraw(); }

	static void change_scene(Scene& s)
	{
		current_scene = &s;
		current_scene->b_redraw = true;
	}
};


#endif
