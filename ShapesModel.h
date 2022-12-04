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
	void moveShape(int x1, int y1, int x2, int y2, Shape* x);
	
	// selection
	void select(int px, int py);
	Shape* getSelected(); // return currently selected shape
	void removeSelected(); // sets selected variable to null; deselects any shape that is selected

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

	// mouse events
	bool getMouseDown() { return mouseDown; }
	void setMouseDown() { mouseDown = true; }
	void setMouseUp() { mouseDown = false; }
	void setMouseDownThisMode(bool x) { hasMouseBeenPressed = x; }
	bool getMouseDownThisMode() { return hasMouseBeenPressed; }

	// mode
	void changeMode();
	int getMode() { return mode; }

	// selection
	void select(int px, int py) { model->select(px, py); } // attempts to select a shape at the given coordinates
	Shape* getSelected() { return model->getSelected(); }

	// modifying shapes
	void insertRectangle(int x2, int y2); // insert a rectangle
	void insertEllipse(int x2, int y2); // insert an ellipse
	void insertFilledRectangle(int x2, int y2);
	void insertFilledEllipse(int x2, int y2);

	void deleteShape(); // delete selected shape
	void moveShape(int translateX, int translateY); // move shape to new position based on translation

	// G key pressed
	bool isGAsserted() { return gIsAsserted; }
	void pressGKey() { gIsAsserted = !gIsAsserted; }

	// F key pressed
	bool isFAsserted() { return fIsAsserted; }
	void pressFKey() { fIsAsserted = !fIsAsserted; }

	// undo/redo operations
	void Undo();
	void Redo();

private:
	ShapesModel* model; // reference to model
	ECCommandHistory* history; // saves history of all commands so far
	int mouseDownX; // saves x position of mouse down event
	int mouseDownY; // saves y position of mouse down event
	int mode; // edit mode is 0, insert mode is 1

	bool mouseDown; // true if mouse is clicked (down)
	bool hasMouseBeenPressed; // true if mouse has been pressed since switching modes

	bool gIsAsserted; // true if user has pressed the "G" key (indicates whether to insert rectangle or ellipse)
	bool fIsAsserted; // true if user has pressed the "F" key (indicates whether to insert a filled shape or not)
};

#endif
