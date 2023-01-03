#ifndef MENU_H
#define MENU_H

#include "ECGraphicViewImp.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

class Menu {
public:
	Menu() {}
	~Menu() {} // TODO: destory all bitmaps
	void initBackrgound(ALLEGRO_BITMAP* bg);
	void draw(); // draws all menu buttons
private:
	ALLEGRO_BITMAP* background;
	vector<ALLEGRO_BITMAP*> buttons;
};

#endif
