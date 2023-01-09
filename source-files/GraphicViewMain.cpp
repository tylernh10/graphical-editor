#include "../header-files/ECGraphicViewImp.h"
#include "../header-files/ECRealObserver.h"
#include "../header-files/ShapesModel.h"
#include "../header-files/MouseFunction.h"
#include "../header-files/Shape.h"
#include "../header-files/Menu.h"
#include <iostream>
using namespace std;

CompositeShape* parseComposite(int numMembers, ifstream& f, ShapesModel* model) {
    vector<Shape*> shapes;
    while (shapes.size() < (long unsigned int)numMembers) {
        vector<int> x;
        string data;
        getline(f, data);
        stringstream ss(data);
        string word;
        while (ss >> word) {
            int y = stoi(word);
            x.push_back(y);
        }
        if (x.size() == 2) {
            shapes.push_back(parseComposite(x.at(1), f, model));
        } else if (x.size() > 2) {
            shapes.push_back(model->loadShape(x));
        }
    }
    CompositeShape* c = new CompositeShape(shapes);
    return c;
}

// Test graphical view code
int real_main(int argc, char** argv)
{
    // Initialize view
    const int widthWin = 1000, heightWin = 1000;
    ECGraphicViewImp view(widthWin, heightWin);

    // Get filename from command line args
    string filename = (argc == 2) ? argv[1] : "";
    
    // Initialize Model and Controller
    ShapesModel* model = new ShapesModel(filename);
    Controller ctrl(model);
    
    // Mouse Functions --> these will be accessed in the menu and in the mouse observers
    InsertModeMouseFunction insertMouseFunctionality(view, ctrl);
    EditModeMouseFunction editMouseFunctionality(view, ctrl);

    // menu init
    Menu menu(editMouseFunctionality, insertMouseFunctionality);
    menu.initFont(al_load_ttf_font("res/IBMPlexSans-Regular.ttf", 18, 0));
    menu.initDivider(al_load_bitmap("res/divider.jpg"));
    menu.initBackground(al_load_bitmap("res/background.jpg"));

    vector<ALLEGRO_BITMAP*> buttons;
    buttons.push_back(al_load_bitmap("res/bt-edit.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-insert.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-undo.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-redo.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-delete.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-group.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-rectangle.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-ellipse.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-filled-rectangle.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-filled-ellipse.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-save.jpg"));
    buttons.push_back(al_load_bitmap("res/bt-help.jpg"));
    menu.initButtons(buttons);

    vector<ALLEGRO_BITMAP*> hoverButtons;
    hoverButtons.push_back(al_load_bitmap("res/bt-edit-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-insert-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-undo-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-redo-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-delete-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-group-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-rectangle-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-ellipse-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-filled-rectangle-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-filled-ellipse-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-save-hover.jpg"));
    hoverButtons.push_back(al_load_bitmap("res/bt-help-hover.jpg"));
    menu.initHoverButtons(hoverButtons);

    vector<ALLEGRO_BITMAP*> colorButtons;
    colorButtons.push_back(al_load_bitmap("res/bt-color-black.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-white.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-red.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-green.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-blue.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-yellow.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-purple.jpg"));
    colorButtons.push_back(al_load_bitmap("res/bt-color-cyan.jpg"));
    menu.initColorButtons(colorButtons);

    vector<ALLEGRO_BITMAP*> hoverColorButtons;
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-black-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-white-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-red-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-green-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-blue-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-yellow-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-purple-hover.jpg"));
    hoverColorButtons.push_back(al_load_bitmap("res/bt-color-cyan-hover.jpg"));
    menu.initColorHoverButtons(hoverColorButtons);

    // fetches and loads data from file specified via command line
    if (argc > 1) {
        ifstream f(argv[1]);
        string data;
        if (f.is_open()) {
            while (getline(f, data)) {
                vector<int> x;
                stringstream ss(data);
                string word;
                while (ss >> word) {
                    int y = stoi(word);
                    x.push_back(y);
                }
                if (x.size() == 2) {
                    model->loadComposite(parseComposite(x.at(1), f, model));
                }
                else if (x.size() > 2) {
                    model->parseAtomic(x);
                }
            }
        }
        f.close();
    }

    // Creating observers
    ECModeObserver* ModeObserver = new ECModeObserver(view, ctrl, menu);
    ECDrawObserver* DrawObserver = new ECDrawObserver(view, ctrl, menu);
    ECDelObserver* DelObserver = new ECDelObserver(view, ctrl, menu);
    ECUndoRedoObserver* UndoRedoObserver = new ECUndoRedoObserver(view, ctrl, menu);
    ECGroupObserver* GroupObserver = new ECGroupObserver(view, ctrl, menu);
    ECTypeInsertObserver* TypeInsertObserver = new ECTypeInsertObserver(view, ctrl, menu);
    ECCtrlObserver* CtrlKeyObserver = new ECCtrlObserver(view, ctrl);
    ECColorObserver* ColorObserver = new ECColorObserver(view, ctrl, menu);
    ECSaveObserver* SaveObserver = new ECSaveObserver(view, ctrl, menu);
    ECHelpObserver* HelpObserver = new ECHelpObserver(view, ctrl, menu);
    ECUpArrowObserver* UpKeyObserver = new ECUpArrowObserver(view, ctrl);
    ECDownArrowObserver* DownKeyObserver = new ECDownArrowObserver(view, ctrl);
    ECLeftArrowObserver* LeftKeyObserver = new ECLeftArrowObserver(view, ctrl);
    ECRightArrowObserver* RightKeyObserver = new ECRightArrowObserver(view, ctrl);

    // Mouse Observers Init
    ECMouseObserver* EditModeMouseObserver = new ECMouseObserver(view, ctrl, 0, editMouseFunctionality);
    ECMouseObserver* InsertModeMouseObserver = new ECMouseObserver(view, ctrl, 1, insertMouseFunctionality);

    // Attaching observers
    view.Attach(ModeObserver);
    view.Attach(DrawObserver);
    view.Attach(DelObserver);
    view.Attach(UndoRedoObserver);
    view.Attach(GroupObserver);
    view.Attach(TypeInsertObserver);
    view.Attach(CtrlKeyObserver);
    view.Attach(EditModeMouseObserver);
    view.Attach(InsertModeMouseObserver);
    view.Attach(ColorObserver);
    view.Attach(SaveObserver);
    view.Attach(HelpObserver);
    view.Attach(UpKeyObserver);
    view.Attach(DownKeyObserver);
    view.Attach(LeftKeyObserver);
    view.Attach(RightKeyObserver);

    // Run application
    view.Show();

    // Save before closing
    model->save();

    // Deallocate pointers
    delete ModeObserver;
    delete DrawObserver;
    delete DelObserver;
    delete UndoRedoObserver;
    delete EditModeMouseObserver;
    delete GroupObserver;
    delete TypeInsertObserver;
    delete CtrlKeyObserver;
    delete ColorObserver;
    delete SaveObserver;
    delete HelpObserver;
    delete UpKeyObserver;
    delete DownKeyObserver;
    delete LeftKeyObserver;
    delete RightKeyObserver;
    delete InsertModeMouseObserver;
    delete model;

    return 0;
}

int main(int argc, char** argv)
{
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

