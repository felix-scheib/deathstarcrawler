//------------------------------------------------------------------------------
//-----abstract active observer-------------------------------------------------
//------------------------------------------------------------------------------

#include "active.h"
#include "passive.h"

//observer handling
void Active::attach(Passive* passive) {
    if(passiveIndex(passive) == -1) {
        passiveVector.push_back(passive);
    }
}

void Active::detach(Passive* passive) {
    int index = passiveIndex(passive);
    if(index != -1) {
        passiveVector.erase(passiveVector.begin() + index);
    }
}

//getter
const std::vector<Passive*>& Active::getPassiveVector() const {
    return passiveVector;
}

//protected methods
int Active::passiveIndex(Passive* passive) const {
    for(std::size_t i = 0; i < passiveVector.size(); ++i) {
        if(passiveVector.at(i) == passive) {
            return i;
        }
    }
    return -1;
}

void Active::activate() {
    for(auto& passive : passiveVector) {
        passive->notify(this);
    }
}
