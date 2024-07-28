//------------------------------------------------------------------------------
//-----abstract tile------------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef TILE_H
#define TILE_H

#include "../../_utilities/rowcolumn.h"

#include <string>

class Character;

class Tile {
public:
    //constructors
    Tile(RowColumn rowColumn, Character* character = nullptr);
    Tile(RowColumn rowColumn, std::string appearance, Character* character = nullptr);
    virtual ~Tile() = default;

    //getter
    int getTextureIndex() const;
    std::string getAppearance() const;
    RowColumn getRowColumn() const;
    Character* getCharacter() const;

    //setter
    void setCharacter(Character* character);

    //move
    bool moveTo(Tile* destTile, Character* who);
    virtual Tile* onEnter(Tile* fromTile, Character* who) = 0;
    virtual Tile* onLeave(Tile* destTile, Character* who);

    //other methods
    bool hasCharacter() const;
    void resetCharacter();

    virtual bool isAccessible() const;
    virtual bool isLeaveable(Tile* destination) const;
protected:
    //member variables
    const RowColumn ROW_COLUMN;
    int textureIndex;
    std::string appearance;
    Character* character;

    void checkForFight(Character* attacker);
};

#endif // TILE_H
