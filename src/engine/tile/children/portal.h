//------------------------------------------------------------------------------
//-----portal, type of tile-----------------------------------------------------
//------------------------------------------------------------------------------

#ifndef PORTAL_H
#define PORTAL_H

#include "../tile.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"
#include "../../character/staticnonplayercharacter.h"

class Portal : public Tile {
public:
    //constructors
    Portal(RowColumn ROW_COLUMN, Tile* destination = nullptr, Character* character = nullptr);
    Portal(RowColumn rowColumnThis, RowColumn rowColumnDestination);
    ~Portal() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;

    //getter
    Tile* getDestination() const;

    bool isAccessible() const override;
private:
    //member variables
    bool isBlocked = false;
    Tile* destination;
    int portalType;
    static int portalCounter;

    //constructors
    Portal(RowColumn rowColumnThis, Portal* destination);

    //setter
    void setPortalType(int portalType);

    static void incrementPortalCounter();
};
#endif // PORTAL_H
