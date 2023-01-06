#ifndef MENU_H
#define MENU_H

#include "ECGraphicViewImp.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>

using namespace std;

class Menu {
public:
	Menu() {}
	~Menu() {} // TODO: destory all bitmaps
	void initDivider(ALLEGRO_BITMAP* div);
	void initBackground(ALLEGRO_BITMAP* bg);
	
	void initButtons(vector<ALLEGRO_BITMAP*> bts);
	void initHoverButtons(vector<ALLEGRO_BITMAP*> bts);
	void initColorButtons(vector<ALLEGRO_BITMAP*> bts);
	void initColorHoverButtons(vector<ALLEGRO_BITMAP*> bts);
	void initFont(ALLEGRO_FONT* f);
	void draw(); // draws all menu buttons
	void detectMouse(int px, int py);
private:
	ALLEGRO_BITMAP* divider;
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	vector<ALLEGRO_BITMAP*> buttons;
	vector<ALLEGRO_BITMAP*> hoverButtons;
	vector<ALLEGRO_BITMAP*> colorButtons;
	vector<ALLEGRO_BITMAP*> colorHoverButtons;
	vector<char*> hoverStrings = {
		"Switch to edit mode",
		"Switch to insert mode",
		"Undo",
		"Redo",
		"Delete selected shapes",
		"Group selected shapes",
		"Insert rectangle",
		"Insert ellipse",
		"Insert filled rectangle",
		"Insert filled ellipse",
		"Change insert color to black",
		"Change insert color to white",
		"Change insert color to red",
		"Change insert color to green",
		"Change insert color to blue",
		"Change insert color to yellow",
		"Change insert color to purple",
		"Change insert color to cyan",
		"Save",
		"Help"
	};
};

#endif
