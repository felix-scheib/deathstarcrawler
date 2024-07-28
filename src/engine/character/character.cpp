//------------------------------------------------------------------------------
//-----character----------------------------------------------------------------
//------------------------------------------------------------------------------

#include "character.h"
#include "../tile/tile.h"
#include "maincharacter.h"
#include "dynamicnonplayercharacter.h"
#include "staticnonplayercharacter.h"

//constructors
Character::Character(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, std::string texture, Tile* tile) :
    controller(controller), texture(texture), tile(tile), strength(strength), stamina(stamina), hitpoints(hitpoints) {
}

Character::Character(const Character& other) :
    controller(other.controller), texture(other.texture), tile(nullptr), movementDirection(other.movementDirection), strength(other.strength), stamina(other.stamina), isAlive(other.isAlive) {
    hitpoints = getMaxHitpoints();
    updateTextureIndex();
}

//getter
std::string Character::getTexture() const {
    return texture;
}

Tile* Character::getTile() const {
    return tile;
}

RowColumn Character::getRowColumn() const {
    return tile->getRowColumn();
}

std::shared_ptr<Controller> Character::getController() const {
    return controller;
}

int Character::getTextureIndex() const {
    return textureIndex;
}

int Character::getStrength() const {
    return strength;
}

int Character::getStamina() const {
    return stamina;
}

bool Character::getAliveState() const {
    return isAlive;
}

//setter
void Character::setTile(Tile* tile) {
    this->tile = tile;
    tile->setCharacter(this);
}

void Character::looseHitpoints(int loosedHitpoints) {
    hitpoints -= loosedHitpoints;
    if(hitpoints <= 0) {
        isAlive = false;
    }
}

//getter
int Character::getMaxHitpoints() const {
    return 20 + (stamina * 5);
}

int Character::getHitpoints() const {
    return hitpoints;
}

//move
void Character::moveToTile(Tile* destination) {
    Character* destinationCharacter = destination->getCharacter();

    destinationCharacter = destination->getCharacter();
    if(dynamic_cast<Character*>(destinationCharacter)) {
        return;
    }

    if(isAlive) {   //still alive
        tile->resetCharacter();
        tile = destination;
        destination->setCharacter(this);
    }
}

char Character::move() {
    movementDirection = controller->move();
    updateTextureIndex();
    return movementDirection;
}

//fight
void Character::fight(Character *attackingCharacter, Character *defendingCharacter) {
    bool successfullAttack = attackingCharacter->attack(defendingCharacter);    //attack defendingCharacter
    bool successfullDefend = true;

    if(!successfullAttack) {    //defendingCharacter is still alive
        successfullDefend = !defendingCharacter->attack(attackingCharacter);    //rebound attack
    }
}

bool Character::attack(Character *defendingCharacter) {
    return !defendingCharacter->defend(this);
}

bool Character::defend(Character *attackingCharacter) {
    hitpoints -= attackingCharacter->strength;  //reduce hitpoints
    if(hitpoints <= 0) {    //defendingChracter killed by attackingCharacter
        killed();
        return false;
    } else {
        return true;
    }
}

void Character::killed() {
    tile->resetCharacter();
    tile = nullptr;
    isAlive = false;
}

void Character::updateTextureIndex() {
    if (isTopMovement()) {
        textureIndex = CharacterTexturesIndex::BACK_START + stepNumber;
    } else if (isBottomMovement()) {
        textureIndex = CharacterTexturesIndex::FRONT_START + stepNumber;
    } else if (isLeftMovement()) {
        textureIndex = CharacterTexturesIndex::LEFT_START + stepNumber;
    } else if (isRightMovement()) {
        textureIndex = CharacterTexturesIndex::RIGHT_START + stepNumber;
    }
    stepNumber = ++stepNumber % CharacterTexturesIndex::STEP_NUMBER;
}

bool Character::isTopMovement() const {
    return (((movementDirection == UserInput::TRIGGER_TOP_LEFT) || (movementDirection == UserInput::TRIGGER_TOP_CENTER)) || (movementDirection == UserInput::TRIGGER_TOP_RIGHT));
}

bool Character::isBottomMovement() const {
    return (((movementDirection == UserInput::TRIGGER_BOTTOM_LEFT) || (movementDirection == UserInput::TRIGGER_BOTTOM_CENTER)) || (movementDirection == UserInput::TRIGGER_BOTTOM_RIGHT));
}

bool Character::isLeftMovement() const {
    return movementDirection == UserInput::TRIGGER_CENTER_LEFT;
}

bool Character::isRightMovement() const {
    return movementDirection == UserInput::TRIGGER_CENTER_RIGHT;
}

//private methods
bool Character::isValidInput(char input) {
    if(UserInput::INPUT_SIGNALS.find(tolower(input)) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}
