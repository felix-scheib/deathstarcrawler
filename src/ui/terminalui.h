//------------------------------------------------------------------------------
//-----terminal user interface--------------------------------------------------
//------------------------------------------------------------------------------

#ifndef TERMINALUI_H
#define TERMINALUI_H

#include "abstractui.h"

#include <memory>

//forward declarations
class Level;

class TerminalUi : public AbstractUi {
public:
    //constructors
    TerminalUi();
    ~TerminalUi() = default;

    //gameplay
    void draw(std::shared_ptr<Level> currentLevel) override;
    char move() override;
private:
    //private methods
    bool isValidInput(char input);
};

#endif // TERMINALUI_H
