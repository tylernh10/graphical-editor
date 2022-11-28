#ifndef ECCONTROLLER_H
#define ECCONTROLLER_H

#include "Shape.h"
#include "Command.h"
#include <vector>
using namespace std;

class ECCommandHistory; // necessary forward declaration

class ShapesModel {
public:
	ShapesModel() {}
	vector<Shape*> getListShapes() { return listShapes; }
	void addShape(Shape* x) { listShapes.push_back(x); }
	void removeShape(Shape* x);
	void select(int px, int py);
	Shape* getSelected();
private:
	vector<Shape*> listShapes;
	Shape* selected = NULL;
};

class Controller {
public:
	Controller(ShapesModel* model);
	vector<Shape*> getListShapes() { return model->getListShapes(); }
	
	// cursor position
	void updateX(int x) { mouseDownX = x; }
	void updateY(int y) { mouseDownY = y; }
	int getX() { return mouseDownX; }
	int getY() { return mouseDownY; }
	void incMouseEvents() { mouseEvents++; }
	int getMouseEvents() { return mouseEvents; }

	// mode
	void changeMode() { 
		mode = !mode;
		if (mode) cout << "mode changed to edit" << endl;
		else cout << "mode changed to insert" << endl;
	}
	int getMode() { return mode; }

	void select(int px, int py) { model->select(px, py); }

	void insertRectangle(int x2, int y2);

	void Undo();
	void Redo();

private:
	ShapesModel* model;
	ECCommandHistory* history; // saves history of all commands so far
	int mouseDownX; // saves x position of mouse down event
	int mouseDownY; // saves y position of mouse down event
	int mouseEvents; // keeps track of how many mouse up and mouse down events have occurred
	int mode = 0; // insert mode is 0, edit mode is 1
};

#endif // !
