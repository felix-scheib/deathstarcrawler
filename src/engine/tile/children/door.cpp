//------------------------------------------------------------------------------
//-----door, type of tile-------------------------------------------------------
//------------------------------------------------------------------------------

#include "door.h"

//constrcutors
Door::Door(RowColumn rowColumn, bool isOpen) :
    Tile(rowColumn, TileAppearances::DOOR_CLOSED_TEXTURE), isOpen(isOpen){
    if(isOpen) {
        Tile::textureIndex = TileTexturesIndex::DOOR_OPEN;
    } else {
        Tile::textureIndex = TileTexturesIndex::DOOR_CLOSED;
    }
}

//move
Tile* Door::onEnter(Tile* fromTile, Character* who) {
    if(isOpen) {
        if(character) {
            Tile::checkForFight(who);
        }
        return this;
    } else {
        return nullptr;
    }
}

//observer handling
void Door::notify(Active *active) {    
    if(!character) {
        isOpen = !isOpen;
    }

    if(isOpen) {
        appearance = TileAppearances::DOOR_OPEN_TEXTURE;
        textureIndex = TileTexturesIndex::DOOR_OPEN;
    } else {
        appearance = TileAppearances::DOOR_CLOSED_TEXTURE;
        textureIndex = TileTexturesIndex::DOOR_CLOSED;
    }
}

//getter
bool Door::getIsOpen() const {
    return isOpen;
}

bool Door::isAccessible() const {
    if(!isOpen) {
        return false;
    } else {
        return Tile::isAccessible();
    }
}
