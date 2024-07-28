//------------------------------------------------------------------------------
//-----switch, type of tile-----------------------------------------------------
//------------------------------------------------------------------------------

#include "switch.h"
#include "../../character/staticnonplayercharacter.h"

//constructors
Switch::Switch(RowColumn rowColumn) :
    Tile(rowColumn, TileAppearances::SWITCH_TEXTURE) {
        Tile::textureIndex = TileTexturesIndex::SWITCH_INACTIVE;
}

//move
Tile* Switch::onEnter(Tile* fromTile, Character* who) {
    if(character) {
        Tile::checkForFight(who);
    }

    if(!dynamic_cast<StaticNonPlayerCharacter*>(character)) {
        Tile::textureIndex = TileTexturesIndex::SWITCH_ACTIVE;
        activate();
    }
    return this;
}

Tile *Switch::onLeave(Tile *destTile, Character *who) {
    Tile::textureIndex = TileTexturesIndex::SWITCH_INACTIVE;
    return this;
}

//observer handling
void Switch::activate() {
    Active::activate();
}
