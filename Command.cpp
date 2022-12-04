#include "Command.h"

// insert command
InsertShape :: InsertShape(int x1, int y1, int x2, int y2, ShapesModel* model, int type) : ECCommand(model) {
	// inserts a Rectangle by default, if type is asserted, inserts an Ellipse
	if (type == 0) s = new Rectangle(x1, y1, x2, y2);
	else if (type == 1) s = new Ellipse(x1, y1, x2, y2);
	else if (type == 2) s = new FilledRectangle(x1, y1, x2, y2);
	else if (type == 3) s = new FilledEllipse(x1, y1, x2, y2);
}

void InsertShape::Execute() {
	// adds shape to model
	model->addShape(s);
}

void InsertShape::UnExecute() {
	model->removeShape(s);
}

// delete command
void DeleteShape::Execute() {
	model->removeShape(s);
}

void DeleteShape::UnExecute() {
	model->addShape(s);
}

// move command
void MoveShape::Execute() {
	model->moveShape(s->getX1() + translateX, s->getY1() + translateY, s->getX2() + translateX, s->getY2() + translateY, s);
}

void MoveShape::UnExecute() {
	model->moveShape(s->getX1() - translateX, s->getY1() - translateY, s->getX2() - translateX, s->getY2() - translateY, s);
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