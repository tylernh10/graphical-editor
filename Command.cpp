#include "Command.h"

// insert command
void InsertShape::Execute() {
	// adds shape to model
	model->addShape(s);
	//cout << model->getListShapes().size() << endl;
}

void InsertShape::UnExecute() {
	model->removeShape(s);
	//cout << model->getListShapes().size() << endl;
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
	while (!redoStack.empty()) redoStack.pop(); // clear redo stack
}