//------------------------------------------------------------------------------
//-----portal, type of tile-----------------------------------------------------
//------------------------------------------------------------------------------

#include "portal.h"

int Portal::portalCounter = 0;

//constructors
Portal::Portal(RowColumn rowColumn, Tile* destination, Character* character) :
    Tile(rowColumn, TileAppearances::PORTAL_TEXTURE, character), destination(destination), portalType(TileTexturesIndex::PORTAL_START + portalCounter) {
    static_cast<Portal*>(destination)->setPortalType(this->portalType); //set to same portalType
    incrementPortalCounter();
    Tile::textureIndex = portalType;
}

Portal::Portal(RowColumn rowColumnThis, RowColumn rowColumnDestination) :
    Tile(rowColumnThis, TileAppearances::PORTAL_TEXTURE, nullptr), destination(new Portal(rowColumnDestination, this)), portalType(TileTexturesIndex::PORTAL_START + portalCounter) {
    static_cast<Portal*>(destination)->setPortalType(this->portalType); //set to same portalType
    incrementPortalCounter();
    Tile::textureIndex = portalType;
}

//move
Tile* Portal::onEnter(Tile* fromTile, Character* who) {
    isBlocked = destination->hasCharacter();

    if(character) {
        Tile::checkForFight(who);
    }

    bool characterOnTile = character && (character != who);
    if((!characterOnTile && !isBlocked)) {
        if(dynamic_cast<StaticNonPlayerCharacter*>(character)) {
            return this;
        } else {
            return destination;
        }
    } else {
        return this;
    }
}

//getter
Tile* Portal::getDestination() const {
    return destination;
}

bool Portal::isAccessible() const {
    if (destination->hasCharacter()) {
        return false;
    } else {
        return Tile::isAccessible();
    }
}

//setter
void Portal::setPortalType(int portalType) {
    this->portalType = portalType;
    Tile::textureIndex = portalType;
}

//constructors (private)
Portal::Portal(RowColumn rowColumnThis, Portal* destination) :
    Tile(rowColumnThis, TileAppearances::PORTAL_TEXTURE, nullptr), destination(destination) {
    Tile::textureIndex = portalType;
}

void Portal::incrementPortalCounter() {
    portalCounter = (++portalCounter)%3;
}




