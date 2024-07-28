//------------------------------------------------------------------------------
//-----door, type of tile-------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef DOOR_H
#define DOOR_H

#include "../tile.h"
#include "../../observer/passive.h"
#include "../../observer/active.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"
#include "../../character/dynamicnonplayercharacter.h"

class Door : public Tile, public Passive {
public:
    //constructors
    Door(RowColumn rowColumn, bool isOpen = false);
    ~Door() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;

    //observer handling
    void notify(Active *active) override;

    //getter
    bool getIsOpen() const; //only for ui warning if door is closed

    bool isAccessible() const override;
private:
    //member variables
    bool isOpen;
};

#endif // DOOR_H
