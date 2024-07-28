//------------------------------------------------------------------------------
//-----LevelChanger, type of tile-----------------------------------------------
//------------------------------------------------------------------------------

#include "levelchanger.h"
#include "../../../engine/management/dungeoncrawler.h"

//constructors
LevelChanger::LevelChanger(RowColumn rowColumn) :
    Tile(rowColumn, TileAppearances::LEVEL_CHANGER_TEXTURE) {
    Tile::textureIndex = TileTexturesIndex::LEVEL_CHANGER;
}

//move
Tile* LevelChanger::onEnter(Tile *fromTile, Character *who) {
    if(character) {
        Tile::checkForFight(who);
    }

    if(dynamic_cast<MainCharacter*>(who) && !character) {
        activate();
        return destinationTile;
    } else {
        return this;
    }
}

void LevelChanger::setDestinationTile(Tile *destination) {
    destinationTile = destination;
}

//observer handling
void LevelChanger::activate() {
    Active::activate();
}
