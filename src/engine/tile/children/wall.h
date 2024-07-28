//------------------------------------------------------------------------------
//-----wall, type of tile-------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef WALL_H
#define WALL_H

#include "../tile.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"

class Wall : public Tile {
public:
    //constructors
    Wall(RowColumn ROW_COLUMN);
    ~Wall() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;

    bool isAccessible() const override;
};
#endif // WALL_H
