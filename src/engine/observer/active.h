//------------------------------------------------------------------------------
//-----abstract active observer-------------------------------------------------
//------------------------------------------------------------------------------


#ifndef ACTIVE_H
#define ACTIVE_H

#include<vector>

//forward declarations
class Passive;

class Active {
public:
    //constructors
    Active() = default;
    virtual ~Active() = default;

    //observer handling
    void attach(Passive* passive);
    void detach(Passive* passive);

    //getter
    const std::vector<Passive*>& getPassiveVector() const;  //only used in copy constructor
protected:
    //member variables
    std::vector<Passive*> passiveVector;

    //protected methods
    int passiveIndex(Passive* passive) const;   //check if passive is inside and return index (for deletion)

    virtual void activate() = 0;
};

#endif // ACTIVE_H
