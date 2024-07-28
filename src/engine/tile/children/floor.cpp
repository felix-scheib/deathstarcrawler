//------------------------------------------------------------------------------
//-----floor, type of tile------------------------------------------------------
//------------------------------------------------------------------------------

#include "floor.h"

//constructors
Floor::Floor(RowColumn rowColumn, Character* character) :
    Tile(rowColumn, TileAppearances::FLOOR_TEXTURE, character) {
    Tile::textureIndex = TileTexturesIndex::FLOOR_START + rand()%5;
}

//move
Tile* Floor::onEnter(Tile* fromTile, Character* who) {
    if(character) {
        Tile::checkForFight(who);
    }
    return this;
}
