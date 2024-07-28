#include "lootchest.h"
#include "../../character/maincharacter.h"


LootChest::LootChest(RowColumn ROW_COLUMN, Character* character) :
    Tile(ROW_COLUMN, " G " ) {
    Tile::textureIndex = TileTexturesIndex::CHEST;
}

//move
Tile* LootChest::onEnter(Tile* fromTile, Character* who) {
    if(character) {
        Tile::checkForFight(who);
    }

    MainCharacter* mainCharacter = dynamic_cast<MainCharacter*>(who);

    if(mainCharacter && !character) {
        mainCharacter->won();
    }

    return this;
}
