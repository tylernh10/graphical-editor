#ifndef ECOBSERVERSPACE_H
#define ECOBSERVERSPACE_H

#include "ECObserver.h"
#include "ECGraphicViewImp.h"
#include "ShapesModel.h"
#include "MouseFunction.h"
#include "Menu.h"

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
// draws relevant info onscreen
class ECDrawObserver : public ECObserver
{
public:
    ECDrawObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECDrawObserver() {}
    virtual void Update() override;
    void attachMenu(Menu* m) { menu = m; }
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu* menu;
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

// G Key Observer
// Toggles rectangle and ellipse insertion when in insert mode
// Groups/ungroups when in edit mode
class ECGObserver : public ECObserver
{
public:
    ECGObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECGObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// F Key Observer
// Toggles filled and non-filled mode
class ECFObserver : public ECObserver
{
public:
    ECFObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECFObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// CTRL Key Observer
// Allows multiple shapes to be selected at once when pressed
class ECCtrlObserver : public ECObserver
{
public:
    ECCtrlObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECCtrlObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

// Arrow Key Observers
// When pressed, they move all selected shapes 10 by the direction specified by the key pressed
class ECGenericArrowObserver : public ECObserver
{
public:
    ECGenericArrowObserver(ECGraphicViewImp& view, Controller& ctrl) : view(view), ctrl(ctrl) {}
    virtual ~ECGenericArrowObserver() {}
    virtual void Update() = 0;
protected:
    ECGraphicViewImp& view;
    Controller& ctrl;
};

class ECUpArrowObserver : public ECGenericArrowObserver {
public:
    ECUpArrowObserver(ECGraphicViewImp& view, Controller& ctrl): ECGenericArrowObserver(view, ctrl) {}
    virtual ~ECUpArrowObserver() {}
    virtual void Update();
};

class ECDownArrowObserver : public ECGenericArrowObserver {
public:
    ECDownArrowObserver(ECGraphicViewImp& view, Controller& ctrl) : ECGenericArrowObserver(view, ctrl) {}
    virtual ~ECDownArrowObserver() {}
    virtual void Update();
};

class ECLeftArrowObserver : public ECGenericArrowObserver {
public:
    ECLeftArrowObserver(ECGraphicViewImp& view, Controller& ctrl) : ECGenericArrowObserver(view, ctrl) {}
    virtual ~ECLeftArrowObserver() {}
    virtual void Update();
};

class ECRightArrowObserver : public ECGenericArrowObserver {
public:
    ECRightArrowObserver(ECGraphicViewImp& view, Controller& ctrl) : ECGenericArrowObserver(view, ctrl) {}
    virtual ~ECRightArrowObserver() {}
    virtual void Update();
};

#endif