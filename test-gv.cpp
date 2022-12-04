//
//  Created by Yufeng Wu on 3/2/22.
//
#include "ECGraphicViewImp.h"
#include "ECRealObserver.h"
#include "ShapesModel.h"
#include "MouseFunction.h"
#include <iostream>
using namespace std;

// Test graphical view code
int real_main(int argc, char **argv)
{
  const int widthWin = 1000, heightWin = 1000;
  ECGraphicViewImp view(widthWin, heightWin);
  ShapesModel * model = new ShapesModel;
  Controller ctrl(model);
  
  // Creating observers
  ECSpaceObserver * SpaceObserver = new ECSpaceObserver(view, ctrl);
  ECDrawObserver* DrawObserver = new ECDrawObserver(view, ctrl);
  ECDObserver* DelObserver = new ECDObserver(view, ctrl);
  ECUndoRedoObserver* UndoRedoObserver = new ECUndoRedoObserver(view, ctrl);
  ECGObserver* GKeyObserver = new ECGObserver(view, ctrl);
  ECFObserver* FKeyObserver = new ECFObserver(view, ctrl);

  // Mouse Observers Init
  InsertModeMouseFunction insertMouseFunctionality(view, ctrl);
  EditModeMouseFunction editMouseFunctionality(view, ctrl);
  ECMouseObserver* EditModeMouseObserver = new ECMouseObserver(view, ctrl, 0, editMouseFunctionality);
  ECMouseObserver* InsertModeMouseObserver = new ECMouseObserver(view, ctrl, 1, insertMouseFunctionality);

  // Attaching observers
  view.Attach(SpaceObserver);
  view.Attach(DrawObserver);
  view.Attach(DelObserver);
  view.Attach(UndoRedoObserver);
  view.Attach(GKeyObserver);
  view.Attach(FKeyObserver);
  view.Attach(EditModeMouseObserver);
  view.Attach(InsertModeMouseObserver);

  // Run application
  view.Show();

  // Deallocate pointers
  delete SpaceObserver;
  delete DrawObserver;
  delete DelObserver;
  delete UndoRedoObserver;
  delete EditModeMouseObserver;
  delete GKeyObserver;
  delete FKeyObserver;
  delete InsertModeMouseObserver;
  delete model;
  
  return 0;
}

int main(int argc, char **argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

