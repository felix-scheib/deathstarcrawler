#ifndef DYNAMICNONPLAYERCHARACTER_H
#define DYNAMICNONPLAYERCHARACTER_H

#include "character.h"
#include "../management/guardcontroller.h"
#include <string>

class Tile;

class DynamicNonPlayerCharacter : public Character {
public:
    DynamicNonPlayerCharacter(int strength, int stamina, int hitpoints, const std::string& movementString, std::size_t currentIndex = 0);
    DynamicNonPlayerCharacter(const DynamicNonPlayerCharacter& other);

    const std::string& getPath() const;
    size_t getPathIndex() const;

private:
    int characterIndex;

    void updateTextureIndex() override;

    void killed() override;
};

#endif // DYNAMICNONPLAYERCHARACTER_H
