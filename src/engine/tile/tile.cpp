//------------------------------------------------------------------------------
//-----abstract tile------------------------------------------------------------
//------------------------------------------------------------------------------

#include "tile.h"
#include "../character/character.h"
#include "../character/maincharacter.h"


//constructors
Tile::Tile(RowColumn rowColumn, Character* character) :
    ROW_COLUMN(rowColumn), character(character) {
}

Tile::Tile(RowColumn rowColumn, std::string texture, Character* character) :
    ROW_COLUMN(rowColumn), appearance(texture), character(character) {
}

//getter
int Tile::getTextureIndex() const {
    return textureIndex;
}

std::string Tile::getAppearance() const {
    if(character) {
        return character->getTexture();
    } else {
        return appearance;
    }
}

RowColumn Tile::getRowColumn() const {
    return ROW_COLUMN;
}

Character* Tile::getCharacter() const {
    return  character;
}

//setter
void Tile::setCharacter(Character* character){
    this->character = character;
}

//move
bool Tile::moveTo(Tile* destTile, Character* who) {
    Tile* origin = this->onLeave(destTile, who);
    bool onLeaveValid = (origin != nullptr);

    destTile = destTile->onEnter(this, who);
    bool onEnterValid = (destTile != nullptr);

    if (onLeaveValid && onEnterValid) {
        who->moveToTile(destTile);
        return true;
    } else {
        return false;
    }
}

Tile* Tile::onLeave(Tile* destTile, Character* who) {
    return this;
}

bool Tile::isAccessible() const {
    if(character && !dynamic_cast<MainCharacter*>(character)) {
        return false;
    } else {
        return true;
    }
}

bool Tile::isLeaveable(Tile* destination) const {
    return destination->isAccessible();
}

//other methods
bool Tile::hasCharacter() const {
    return character;
}

void Tile::resetCharacter() {
    character = nullptr;
}

void Tile::checkForFight(Character* attacker) {
    bool attackerIsMainCharacter = dynamic_cast<MainCharacter*>(attacker);
    bool defenderIsMainCharacter = dynamic_cast<MainCharacter*>(character);
    bool attacksItself = attacker == character;

    if((attackerIsMainCharacter || defenderIsMainCharacter) && !attacksItself) {
            Character::fight(attacker, character);
    }
}
