#ifndef MENU_H
#define MENU_H

class Menu;
class EditModeMouseFunction;
class InsertModeMouseFunction;

#include "ECGraphicViewImp.h"
#include "MouseFunction.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <string>

using namespace std;

class Menu {
public:
	Menu(EditModeMouseFunction& e, InsertModeMouseFunction& i): editModeMouseFunction(e), insertModeMouseFunction(i) {}
	~Menu() {} // TODO: destroy all bitmaps
	void initDivider(ALLEGRO_BITMAP* div);
	void initBackground(ALLEGRO_BITMAP* bg);
	
	void initButtons(vector<ALLEGRO_BITMAP*> bts);
	void initHoverButtons(vector<ALLEGRO_BITMAP*> bts);
	void initColorButtons(vector<ALLEGRO_BITMAP*> bts);
	void initColorHoverButtons(vector<ALLEGRO_BITMAP*> bts);
	void initFont(ALLEGRO_FONT* f);
	void timer(int mode); // draws all menu buttons and take care of trace shapes
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
	EditModeMouseFunction& editModeMouseFunction;
	InsertModeMouseFunction& insertModeMouseFunction;
};

#endif
