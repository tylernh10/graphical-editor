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

// maybe make this insert rectangle --> eventually edit to support adding different types of shapes
class InsertShape : public ECCommand {
public:
    InsertShape(int x1, int y1, int x2, int y2, ShapesModel* model, int type = 0);
    virtual ~InsertShape() { delete s; }
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    Shape* s;
};

class DeleteShape : public ECCommand {
public:    
    DeleteShape(Shape * s, ShapesModel* model): s(s), ECCommand(model) {}
    virtual ~DeleteShape() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    Shape* s;
};

class MoveShape : public ECCommand {
public:    
    MoveShape(int translateX, int translateY, Shape * s, ShapesModel * model): translateX(translateX), translateY(translateY), s(s), ECCommand(model) {}
    virtual ~MoveShape() {}
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    int translateX;
    int translateY;
    Shape* s;
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
