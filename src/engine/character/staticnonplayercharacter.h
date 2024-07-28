#ifndef STATICNONPLAYERCHARACTER_H
#define STATICNONPLAYERCHARACTER_H

#include "character.h"
#include "../management/stationarycontroller.h"

class StaticNonPlayerCharacter : public Character {
public:
    StaticNonPlayerCharacter(int strength, int stamina, int hitpoints);
    ~StaticNonPlayerCharacter() = default;
    StaticNonPlayerCharacter(const StaticNonPlayerCharacter& other);
private:
    void updateTextureIndex() override;
    int characterIndex;

    void killed() override;
};

#endif // STATICNONPLAYERCHARACTER_H
