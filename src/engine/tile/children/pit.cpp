#include "pit.h"
#include "ramp.h"

#include <iostream>

//constructors
Pit::Pit(RowColumn rowColumn, Character* character) :
    Tile(rowColumn, TileAppearances::PIT_TEXTURE, character) {
    Tile::textureIndex = TileTexturesIndex::PIT_START + rand()%5;
}

//move
Tile* Pit::onEnter(Tile* fromTile, Character* who) {
    if(character) {
        Tile::checkForFight(who);
    }
    return this;
}

Tile* Pit::onLeave(Tile* destTile, Character* who) {
    bool isPit = (typeid (*destTile) == typeid (Pit));
    bool isRamp = (typeid (*destTile) == typeid (Ramp));

    if(isPit || isRamp) {
        return this;
    } else {
        return nullptr;
    }
}

bool Pit::isLeaveable(Tile *destination) const {
    if(dynamic_cast<Pit*>(destination) || dynamic_cast<Ramp*>(destination)) {
        return destination->isAccessible();
    } else {
        return false;
    }
}
