#ifndef MENU_H
#define MENU_H

#include "ECGraphicViewImp.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <string>

using namespace std;

class Menu {
public:
	Menu() {}
	~Menu() {} // TODO: destory all bitmaps
	void initBackrgound(ALLEGRO_BITMAP* bg);
	void initButtons(vector<ALLEGRO_BITMAP*> bts);
	void initHoverButtons(vector<ALLEGRO_BITMAP*> bts);
	void initFont(ALLEGRO_FONT* f);
	void draw(); // draws all menu buttons
	void detectMouse(int px, int py);
private:
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	vector<ALLEGRO_BITMAP*> buttons;
	vector<ALLEGRO_BITMAP*> hoverButtons;
	vector<char*> hoverStrings = {
		"Edit mode",
		"Insert mode",
		"Undo",
		"Redo",
		"Delete",
		"Group",
		"Insert rectangle",
		"Insert ellipse",
		"Insert filled rectangle",
		"Insert filled ellipse"
	};
};

#endif
