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
class ECModeObserver : public ECObserver
{
public:
    ECModeObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECModeObserver() {}
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
};

// Draw observer
// draws relevant info onscreen
class ECDrawObserver : public ECObserver
{
public:
    ECDrawObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECDrawObserver() {}
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
};

// Delete observer
// deletes selected shape in edit mode
class ECDelObserver : public ECObserver
{
public:
    ECDelObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECDelObserver() {}
    virtual void Update() override;
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
};

// Mouse Observer
// various functionality when mouse is pressed down/up in both edit and insert mode (doesn't include menu clicking functionality)
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
    ECUndoRedoObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECUndoRedoObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
};

// Group Observer
// Groups/ungroups when in edit mode
class ECGroupObserver : public ECObserver
{
public:
    ECGroupObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECGroupObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
};

// Type Insert Observer
// Determines which shape to insert
class ECTypeInsertObserver : public ECObserver
{
public:
    ECTypeInsertObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECTypeInsertObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
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

// Color Observer
// Allows user to change color with buttons in menu
class ECColorObserver : public ECObserver
{
public:
    ECColorObserver(ECGraphicViewImp& view, Controller& ctrl, Menu& m) : view(view), ctrl(ctrl), menu(m) {}
    virtual ~ECColorObserver() {}
    virtual void Update();
private:
    ECGraphicViewImp& view;
    Controller& ctrl;
    Menu& menu;
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