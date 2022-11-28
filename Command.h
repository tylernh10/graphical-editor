#ifndef ECCommand_h
#define ECCommand_h

#include <stack>

#include "Controller.h"

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

// maybe make this insert rectangle
class InsertShape : public ECCommand {
public:
    InsertShape(int x1, int y1, int x2, int y2, ShapesModel* model) : ECCommand(model) {
        s = new Rectangle(x1, y1, x2, y2);
    }
    virtual ~InsertShape() { delete s; }
    virtual void Execute() override;
    virtual void UnExecute() override;
private:
    Shape* s;
};

class ECCommandHistory {
public:
    ECCommandHistory() {}
    virtual ~ECCommandHistory() {}
    bool Undo();
    bool Redo();
    void ExecuteCmd(ECCommand* pCmd);

private:
    stack<ECCommand*> undoStack;
    stack<ECCommand*> redoStack;
};

#endif
