#ifndef LOOTCHEST_H
#define LOOTCHEST_H

#include "../tile.h"
#include "../../../../_config/textures.h"
#include "../../character/maincharacter.h"

class LootChest : public Tile{
public:
    //constructors
    LootChest(RowColumn ROW_COLUMN, Character* character = nullptr);
    ~LootChest() = default;

    Tile* onEnter(Tile* fromTile, Character* who) override;
};

#endif // LOOTCHEST_H
