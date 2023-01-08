#include "../header-files/ShapesModel.h"

// Controller
Controller :: Controller(ShapesModel* model) : model(model), mode(0), hasMouseBeenPressed(false), gIsAsserted(false), fIsAsserted(false), ctrlIsPressed(false) {
	history = new ECCommandHistory;
}

void Controller :: insertRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model);
	history->ExecuteCmd(c);
	cout << "rectangle inserted" << endl;
}

void Controller::insertEllipse(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 1);
	history->ExecuteCmd(c);
	cout << "ellipse inserted" << endl;
}

void Controller::insertFilledRectangle(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 2);
	history->ExecuteCmd(c);
	cout << "filled rectangle inserted" << endl;
}

void Controller::insertFilledEllipse(int x2, int y2) {
	InsertShape* c = new InsertShape(mouseDownX, mouseDownY, x2, y2, model, 3);
	history->ExecuteCmd(c);
	cout << "filled ellipse inserted" << endl;
}

void Controller::deleteShape() {
	vector<Shape*> s = model->getSelected();
	if (!s.empty()) {
		DeleteShape* d = new DeleteShape(s, model);
		history->ExecuteCmd(d);
		cout << "selected shapes deleted" << endl;
	}
	model->removeSelected();
}

void Controller::moveShape(int translateX, int translateY) {
	vector<Shape*> s = model->getSelected();
	if (!s.empty()) {
		MoveShape* m = new MoveShape(translateX, translateY, s, model);
		history->ExecuteCmd(m);
		cout << "selected shapes moved" << endl;
	}
}

void Controller::changeMode() {
	mode = !mode; // 0 is edit mode, 1 is insertion mode
	if (mode) model->removeSelected(); // removed when changing back to insertion mode
}

void Controller::select(int px, int py) {
	if (py <= 110) {
		model->removeSelected();
		return;
	}
	model->select(px, py, ctrlIsPressed);
}

void Controller::resetFandGAssertions() {
	gIsAsserted = false;
	fIsAsserted = false;
}

void Controller::pressUpArrow() {
	moveShape(0, -10);
}
void Controller::pressDownArrow() {
	moveShape(0, 10);
}
void Controller::pressLeftArrow() {
	moveShape(-10, 0);
}
void Controller::pressRightArrow() {
	moveShape(10, 0);
}

void Controller::GroupShapes() {
	// If only one shape is selected, attempt to ungroup
	if (model->getSelected().size() == 1) {
		CompositeShape* c = dynamic_cast<CompositeShape*>(getSelected().at(0));
		if (c != NULL) {
			Ungroup* ungroup = new Ungroup(c, model);
			history->ExecuteCmd(ungroup);
		}
	}
	else if (model->getSelected().size() > 1) {
		Group* group = new Group(getSelected(), model);
		history->ExecuteCmd(group);
		// group into a composite shape
	}
}

void Controller::Undo() {
	model->removeSelected();
	history->Undo();
}

void Controller::Redo() {
	model->removeSelected();
	history->Redo();
}

void Controller::setColor(int x) {
	model->setColor(x);
}

// ShapesModel
void ShapesModel::removeShape(Shape* x) {
	for (auto i = listShapes.begin(); i != listShapes.end(); i++) {
		if (x == *i) {
			listShapes.erase(i);
			break;
		}
	}
}

void ShapesModel::moveShape(int translateX, int translateY, Shape* x) {
	for (auto i = listShapes.begin(); i != listShapes.end(); i++) {
		if (x == *i) {
			(*i)->setNewPosition(translateX, translateY);
			break;
		}
	}
}

// parsing and loading operations
void ShapesModel::parseAtomic(vector<int> info) {
	if (info.at(0) % 2 == 0) {
		addShape(loadRectangle(info));
	} else {
		addShape(loadEllipse(info));
	}
}

void ShapesModel::loadComposite(CompositeShape* c) {
	addShape(c);
}

Rectangle* ShapesModel::loadRectangle(vector<int> info) {
	if (info.at(0) == 0) {
		Rectangle* r = new Rectangle(info.at(2), info.at(3), info.at(6), info.at(7), parseColor(info.at(10)));
		return r;
	} else {
		FilledRectangle* f = new FilledRectangle(info.at(2), info.at(3), info.at(6), info.at(7), parseColor(info.at(10)));
		return f;
	}
}

Ellipse* ShapesModel::loadEllipse(vector<int> info) {
	int x1 = info.at(1) - info.at(3);
	int y1 = info.at(2) - info.at(4);
	int x2 = info.at(1) + info.at(3);
	int y2 = info.at(2) + info.at(4);
	if (info.at(0) == 1) {
		Ellipse* e = new Ellipse(x1, y1, x2, y2, parseColor(info.at(5)));
		return e;
	} else {
		FilledEllipse* f = new FilledEllipse(x1, y1, x2, y2, parseColor(info.at(5)));
		return f;
	}
}

Shape* ShapesModel::loadShape(vector<int> info) {
	if (info.at(0) % 2 == 0) {
		return loadRectangle(info);
	} else {
		return loadEllipse(info);
	}
}

ECGVColor ShapesModel::parseColor(int x) {
	if (x == 0) return ECGV_BLACK;
	if (x == 1) return ECGV_WHITE;
	if (x == 2) return ECGV_RED;
	if (x == 3) return ECGV_GREEN;
	if (x == 4) return ECGV_BLUE;
	if (x == 5) return ECGV_YELLOW;
	if (x == 6) return ECGV_PURPLE;
	if (x == 7) return ECGV_CYAN;
	else return ECGV_NONE;
}


void ShapesModel::select(int px, int py, bool ctrlIsPressed) {
	if (!ctrlIsPressed) {
		removeSelected(); // deselect any currently selected shape if ctrl is not pressed
	}
	for (auto i = listShapes.rbegin(); i != listShapes.rend(); i++) {
		if ((*i)->isPointInside(px, py)) {
			cout << "selected inside a shape" << endl;
			(*i)->selectedColorChange();
			// only add a shape to the selected vector if it is not already in the vector
			if (find(selected.begin(), selected.end(), * i) == selected.end()) {
				selected.push_back(*i);
			}
			return;
		}
	}
	removeSelected();
	cout << "selected outside of any shape" << endl;
}

vector<Shape*> ShapesModel::getSelected() {
	return selected;
}

void ShapesModel::removeSelected() {
	if (!selected.empty()) {
		for (auto i : selected) {
			i->unselectedColorChange();
		}
		selected.clear();
	}
}

ECGVColor ShapesModel::getColor() {
	return color;
}

void ShapesModel::setColor(int x) {
	color = parseColor(x);
}

void ShapesModel::save() {
	if (filename != "") {
		ofstream f(filename, std::ios::trunc);
		f << getListShapes().size() << endl;
		for (auto i : getListShapes()) {
			i->writeShape(f);
		}
		f.close();
	}
}
