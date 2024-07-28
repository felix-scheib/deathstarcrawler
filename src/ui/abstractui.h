//------------------------------------------------------------------------------
//-----abstract user interface--------------------------------------------------
//------------------------------------------------------------------------------

#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H

#include <memory>
#include "../engine/management/controller.h"


//forward declarations
class Level;

class AbstractUi : public Controller{
public:
    //constructors
    AbstractUi();
    virtual ~AbstractUi() = default;

    //gameplay
    virtual void draw(std::shared_ptr<Level> currentLevel) = 0;
    virtual char move() = 0;
    virtual void wait();
};

#endif // ABSTRACTUI_H
