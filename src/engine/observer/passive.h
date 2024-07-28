//------------------------------------------------------------------------------
//-----abstract passive observer------------------------------------------------
//------------------------------------------------------------------------------

#ifndef PASSIVE_H
#define PASSIVE_H

//forward declarations
class Active;

class Passive {
public:
    //constructors
    Passive() = default;
    virtual ~Passive() = default;

    //observer handling
    virtual void notify(Active* active) = 0;
};

#endif // PASSIVE_H
