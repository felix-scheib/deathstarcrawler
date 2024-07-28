//------------------------------------------------------------------------------
//-----floor, type of tile------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef FLOOR_H
#define FLOOR_H

#include "../tile.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"

class Floor : public Tile {
public:
    //constructors
    Floor(RowColumn ROW_COLUMN, Character* character = nullptr);
    ~Floor() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;
};
#endif // FLOOR_H
