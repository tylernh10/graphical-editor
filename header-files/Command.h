#ifndef ECCommand_h
#define ECCommand_h

#include <stack>

#include "ShapesModel.h"

using namespace std;

class ShapesModel; // necessary forward declaration

class ECCommand {
public:
    ECCommand(ShapesModel* model) : model(model) {}
    virtual ~ECCommand() {}
    virtual void Execute() = 0;
    virtual void UnExecute() = 0;
protected:
    ShapesModel* model; // holds model referenced
};

// inserts a new shape in model based on type specified in call
class InsertShape : public ECCommand {
public:
    InsertShape(int x1, int y1, int x2, int y2, ShapesModel* model, int type = 0);
    virtual ~InsertShape() { delete s; }
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    Shape* s;
};

// deletes all shapes passed in
class DeleteShape : public ECCommand {
public:    
    DeleteShape(vector<Shape*>& s, ShapesModel* model): ECCommand(model), s(s) {}
    virtual ~DeleteShape() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    vector<Shape*> s;
};

// moves all shapes passed in
class MoveShape : public ECCommand {
public:    
    MoveShape(int translateX, int translateY, vector<Shape*>& s, ShapesModel * model): ECCommand(model), translateX(translateX), translateY(translateY), s(s) {}
    virtual ~MoveShape() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    int translateX;
    int translateY;
    vector<Shape*> s;
};

class Group : public ECCommand {
public:
    Group(vector<Shape*> s, ShapesModel* model);
    virtual ~Group() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    vector<Shape*> s;
    CompositeShape* c;
};

class Ungroup : public ECCommand {
public:
    Ungroup(CompositeShape* c, ShapesModel* model): ECCommand(model), s(c->getShapes()), c(c) {}
    virtual ~Ungroup() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    vector<Shape*> s;
    CompositeShape* c;
};

class ECCommandHistory {
public:
    ECCommandHistory() {}
    virtual ~ECCommandHistory();
    bool Undo();
    bool Redo();
    void ExecuteCmd(ECCommand* pCmd);

private:
    stack<ECCommand*> undoStack;
    stack<ECCommand*> redoStack;
};

#endif
