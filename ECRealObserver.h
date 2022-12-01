#ifndef ECOBSERVERSPACE_H
#define ECOBSERVERSPACE_H

#include "ECObserver.h"
#include "ECGraphicViewImp.h"
#include "ShapesModel.h"
#include "MouseFunction.h"

#include <iostream>
#include <cmath>
using namespace std;

class ECAbstractMouseFunction;

// Spacebar observer
// used to change mode
class ECSpaceObserver : public ECObserver
{
public:
    ECSpaceObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECSpaceObserver() {}
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// Draw observer
// draws all shapes in model
class ECDrawObserver : public ECObserver
{
public:
    ECDrawObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECDrawObserver() {}
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// D key observer
// deletes selected shape in edit mode
class ECDObserver : public ECObserver
{
public:
    ECDObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECDObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// Mouse Observer
// various functionality when mouse is pressed down/up in both edit and insert mode
class ECMouseObserver : public ECObserver
{
public:
    ECMouseObserver(ECGraphicViewImp& view, Controller& ctrl, int observerModeType, ECAbstractMouseFunction& mouseFunction) : view(view), ctrl(ctrl), observerModeType(observerModeType), mouseFunction(mouseFunction) {}
    virtual ~ECMouseObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    int observerModeType;
    ECAbstractMouseFunction& mouseFunction;
};

// Undo/Redo Observer
// completes undo when user presses z, redo when user presses y
class ECUndoRedoObserver : public ECObserver
{
public:
    ECUndoRedoObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECUndoRedoObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

#endif