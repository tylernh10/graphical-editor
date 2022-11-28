#include "Controller.h"

// controller
Controller :: Controller(ShapesModel* model) : model(model) {
	history = new ECCommandHistory;
}

void Controller :: insertRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model);
	history->ExecuteCmd(c);
}

void Controller::Undo() {
	history->Undo();
}

void Controller::Redo() {
	history->Redo();
}

// model
void ShapesModel::removeShape(Shape* s) {
	for (auto i = listShapes.begin(); i != listShapes.end(); i++) {
		if (s == *i) {
			listShapes.erase(i);
			break;
		}
	}
}
