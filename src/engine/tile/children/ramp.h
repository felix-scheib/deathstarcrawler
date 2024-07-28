#ifndef RAMP_H
#define RAMP_H

#include "../tile.h"
#include "../../../../_config/textures.h"

class Ramp : public Tile {
public:
    //constructors
    Ramp(RowColumn ROW_COLUMN, Character* character = nullptr);
    ~Ramp() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;
};

#endif // RAMP_H
