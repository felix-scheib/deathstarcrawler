//------------------------------------------------------------------------------
//-----singleton for MainCharacter----------------------------------------------
//------------------------------------------------------------------------------

#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "character.h"
#include "../observer/active.h"

#include <stdexcept>

class Passive;

class MainCharacter : public Character, public Active {
private:
    MainCharacter(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, const RowColumn& startingPosition);

    static bool isInstaciated;
    RowColumn startingPosition;

    void activate() override;
public:
    ~MainCharacter();

    static MainCharacter* createMainCharacter(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, Passive* passive, const RowColumn& startingPosition);

    void setAttributes(int strength, int stamina, int hitpoints, const RowColumn& startingPosition);

    void killed() override;

    void won();

    inline const RowColumn& getStartingPosition() const {return startingPosition;}
};

#endif // MAINCHARACTER_H
