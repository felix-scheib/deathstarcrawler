//------------------------------------------------------------------------------
//-----switch, type of tile-----------------------------------------------------
//------------------------------------------------------------------------------

#ifndef SWITCH_H
#define SWITCH_H

#include "../tile.h"
#include "../../observer/active.h"
#include "../../observer/passive.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"

class Switch : public Tile, public Active {
public:
    //constructors
    explicit Switch(RowColumn rowColumn);
    ~Switch() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;

    //observer handling
    void activate() override;
};

#endif // SWITCH_H
