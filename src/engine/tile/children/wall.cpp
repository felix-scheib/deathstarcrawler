//------------------------------------------------------------------------------
//-----wall, type of tile-------------------------------------------------------
//------------------------------------------------------------------------------

#include "wall.h"

//constructors
Wall::Wall(RowColumn rowColumn) :
    Tile(rowColumn, TileAppearances::WALL_TEXTURE) {
    Tile::textureIndex = TileTexturesIndex::WALL_START + rand()%4;
}

//move
Tile* Wall::onEnter(Tile* fromTile, Character* who) {
    return nullptr;
}

bool Wall::isAccessible() const {
    return false;
}

