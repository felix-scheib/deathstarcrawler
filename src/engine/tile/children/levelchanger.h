//------------------------------------------------------------------------------
//-----LevelChanger, type of tile-----------------------------------------------
//------------------------------------------------------------------------------

#ifndef LEVELCHANGER_H
#define LEVELCHANGER_H

#include "../tile.h"
#include "../../observer/passive.h"
#include "../../observer/active.h"
#include "../../../../_config/textures.h"
#include "../../../_utilities/rowcolumn.h"
#include "../../character/maincharacter.h"


class LevelChanger : public Tile, public Active {
public:
    //constructors
    explicit LevelChanger(RowColumn rowColumn);
    ~LevelChanger() = default;

    //move
    Tile* onEnter(Tile*, Character* who) override;
    void setDestinationTile(Tile* destination);

    //observer handling
    void activate() override;

    Tile* getDestination() const {return destinationTile;}
private:
    Tile* destinationTile;
};

#endif // LEVELCHANGER_H
