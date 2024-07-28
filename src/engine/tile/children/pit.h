#ifndef PIT_H
#define PIT_H

#include "../tile.h"
#include "../../../../_config/textures.h"

class Pit : public Tile {
public:
    //constructors
    Pit(RowColumn ROW_COLUMN, Character* character = nullptr);
    ~Pit() = default;

    //move
    Tile* onEnter(Tile* fromTile, Character* who) override;
    Tile* onLeave(Tile* destTile, Character* who) override;

    bool isLeaveable(Tile *destination) const override;
};

#endif // PIT_H
