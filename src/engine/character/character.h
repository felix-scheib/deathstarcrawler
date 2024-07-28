//------------------------------------------------------------------------------
//-----character----------------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../../_config/textures.h"
#include "../../_utilities/rowcolumn.h"
#include "../management/controller.h"

#include <string>
#include <memory>

//forward declarations
class Tile;

class Character {
public:
    //constructors
    Character(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, std::string texture = CharacterTextures::CHARACTER_TEXTURE, Tile* tile = nullptr);
    virtual ~Character() = default;
    Character(const Character& other);

    //getter
    std::string getTexture() const;
    Tile* getTile() const;
    RowColumn getRowColumn() const;
    std::shared_ptr<Controller> getController() const;
    int getTextureIndex() const;
    int getStrength() const;
    int getStamina() const;
    bool getAliveState() const;
    int getMaxHitpoints() const;
    int getHitpoints() const;

    //setter
    void setTile(Tile* tile);
    void looseHitpoints(int loosedHitpoints);

    //move
    void moveToTile(Tile* destination);

    char move();

    static void fight(Character* attackingCharacter, Character* defendingCharacter);
protected:
    //member variables
    std::shared_ptr<Controller> controller;
    const std::string texture;
    Tile* tile;



    int stepNumber = 0;
    int textureIndex = CharacterTexturesIndex::FRONT_01;
    char movementDirection;

    int strength;
    int stamina;
    int hitpoints;

    bool isAlive = true;

    //private methods
    bool isValidInput(char input);
    virtual void updateTextureIndex();

    bool isTopMovement() const;
    bool isBottomMovement() const;
    bool isLeftMovement() const;
    bool isRightMovement() const;

    //fight
    bool attack(Character* defendingCharacter);
    bool defend(Character* attackingCharacter);
    virtual void killed() = 0;
};

#endif // CHARACTER_H
