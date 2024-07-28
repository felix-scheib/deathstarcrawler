#include "ramp.h"

//constrcutors
Ramp::Ramp(RowColumn rowColumn, Character* character) :
    Tile(rowColumn, TileAppearances::RAMP_TEXTURE, character) {
    Tile::textureIndex = TileTexturesIndex::RAMP_UP;
}

//move
Tile* Ramp::onEnter(Tile* fromTile, Character* who) {
    if(character) {
        Tile::checkForFight(who);
    }
    Tile::textureIndex = TileTexturesIndex::RAMP_DOWN;
    return this;
}

Tile *Ramp::onLeave(Tile *destTile, Character *who) {
    Tile::textureIndex = TileTexturesIndex::RAMP_UP;
    return this;
}
