#ifndef ATTACKINGNONPLAYERCHARACTER_H
#define ATTACKINGNONPLAYERCHARACTER_H

#include "character.h"
#include "../../_utilities/tilegraph.h"
#include "../management/attackcontroller.h"

#include <memory>

class Level;

class AttackingNonPlayerCharacter : public Character {
public:
    AttackingNonPlayerCharacter(int strength, int stamina, int hitpoints);
    ~AttackingNonPlayerCharacter() = default;
    AttackingNonPlayerCharacter(const AttackingNonPlayerCharacter& other);

    void setDestination(const RowColumn& destination, const RowColumn& second);
    void stayOnTile();

private:
    int characterIndex;

    void updateTextureIndex() override;

    void killed() override;


};

#endif // ATTACKINGNONPLAYERCHARACTER_H
