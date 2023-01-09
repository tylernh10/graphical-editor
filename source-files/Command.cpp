#include "../header-files/Command.h"

// insert command
InsertShape :: InsertShape(int x1, int y1, int x2, int y2, ShapesModel* model, int type) : ECCommand(model) {
	// inserts a Rectangle by default (type 0)
	if (type == 0) s = new Rectangle(x1, y1, x2, y2, model->getColor());
	else if (type == 1) s = new Ellipse(x1, y1, x2, y2, model->getColor());
	else if (type == 2) s = new FilledRectangle(x1, y1, x2, y2, model->getColor());
	else if (type == 3) s = new FilledEllipse(x1, y1, x2, y2, model->getColor());
}

void InsertShape::Execute() {
	// adds shapes to model
	model->addShape(s);
}

void InsertShape::UnExecute() {
	model->removeShape(s);
}

// delete command
void DeleteShape::Execute() {
	for (auto i : s) {
		model->removeShape(i);
	}
}

void DeleteShape::UnExecute() {
	for (auto i : s) {
		model->addShape(i);
	}
}

// move command
void MoveShape::Execute() {
	for (auto i : s) {
		model->moveShape(translateX, translateY, i);
	}
}

void MoveShape::UnExecute() {
	for (auto i : s) {
		model->moveShape(-translateX, -translateY, i);
	}
}

// group command
Group::Group(vector<Shape*> s, ShapesModel* model) : ECCommand(model), s(s) {
	c = new CompositeShape(s);
}

void Group::Execute() {
	for (auto i : s) {
		model->removeShape(i);
	}
	model->addShape(c);
}

void Group::UnExecute() {
	model->removeShape(c);
	for (auto i : c->getShapes()) {
		model->addShape(i);
	}
}

void Ungroup::Execute() {
	model->removeShape(c);
	for (auto i : c->getShapes()) {
		model->addShape(i);
	}
}

void Ungroup::UnExecute() {
	for (auto i : s) {
		model->removeShape(i);
	}
	model->addShape(c);
}

// command history
ECCommandHistory::~ECCommandHistory() {
	// deallocate all commands in both undo and redo stacks
	while (!undoStack.empty()) {
		delete undoStack.top();
		undoStack.pop();
	}
	while (!redoStack.empty()) {
		delete redoStack.top();
		redoStack.pop();
	}
}

bool ECCommandHistory::Undo() {
	if (undoStack.empty()) return false; // make sure there is a command to undo
	undoStack.top()->UnExecute();
	redoStack.push(undoStack.top());
	undoStack.pop();
	return true;
}

bool ECCommandHistory::Redo() {
	if (redoStack.empty()) return false; // make sure there is a command to redo
	redoStack.top()->Execute();
	undoStack.push(redoStack.top());
	redoStack.pop();
	return true;
}

void ECCommandHistory::ExecuteCmd(ECCommand* pCmd) {
	pCmd->Execute(); // execute command
	undoStack.push(pCmd); // push command onto undo stack
	// clear redo stack
	while (!redoStack.empty()) {
		delete redoStack.top();
		redoStack.pop();
	}
}