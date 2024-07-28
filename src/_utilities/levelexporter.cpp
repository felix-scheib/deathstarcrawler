#include "levelexporter.h"

#include "../engine/management/level.h"
#include "../engine/character/maincharacter.h"
#include "../engine/character/attackingnonplayercharacter.h"
#include "../engine/character/dynamicnonplayercharacter.h"
#include "../engine/character/staticnonplayercharacter.h"
#include "../engine/tile/children/wall.h"
#include "../engine/tile/children/pit.h"
#include "../engine/tile/children/ramp.h"
#include "../engine/tile/children/lootchest.h"
#include "../engine/tile/children/door.h"
#include "../engine/tile/children/portal.h"
#include "../engine/tile/children/levelchanger.h"
#include "../engine/tile/children/switch.h"

void LevelExporter::exportEmptyFile() {
    std::ofstream outputFile(JsonPaths::STORE_PATH);

    createMetadata(false);

    outputFile << jsonExport.dump(2);

    outputFile.close();
}

void LevelExporter::exportLevelFile() {
    std::ofstream outputFile(JsonPaths::STORE_PATH);

    jsonExport["levels"] = levelArray;

    outputFile << jsonExport.dump(2);

    outputFile.close();
}

void LevelExporter::dumpMetaData(bool validSave) {
    createMetadata(validSave);
}

void LevelExporter::dumpLevel(Level* level) {
    nlohmann::json levelJson;

    //export level data
    auto levelDimensions = level->getRowColumns();
    auto spawnPosition = level->getSpawnPosition();

    levelJson["rows"] = levelDimensions.row;
    levelJson["columns"] = levelDimensions.column;
    levelJson["spawnRow"] = spawnPosition.row;
    levelJson["spawnColumn"] = spawnPosition.column;

    //export tiles
    auto tileArray = nlohmann::json::array();
    auto tileVector = level->getTileVector();

    for(size_t i = 1; i < (tileVector.size() - 1); ++i) {
        for(size_t j = 1; j < (tileVector.at(i).size() - 1); ++j) {
            Tile* tile = tileVector.at(i).at(j);

            Wall* isWall = dynamic_cast<Wall*>(tile);
            Pit* isPit = dynamic_cast<Pit*>(tile);
            Ramp* isRamp = dynamic_cast<Ramp*>(tile);
            LootChest* isLootChest = dynamic_cast<LootChest*>(tile);
            Switch* isSwitch = dynamic_cast<Switch*>(tile);
            Portal* isPortal = dynamic_cast<Portal*>(tile);
            LevelChanger* isLevelChanger = dynamic_cast<LevelChanger*>(tile);

            if(isWall) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();

                tileData["type"] = "wall";
                tileData["row"] = position.row;
                tileData["column"] = position.column;

                tileArray.push_back(tileData);
            } else if(isPit) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();

                tileData["type"] = "pit";
                tileData["row"] = position.row;
                tileData["column"] = position.column;

                tileArray.push_back(tileData);
            } else if(isRamp) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();

                tileData["type"] = "ramp";
                tileData["row"] = position.row;
                tileData["column"] = position.column;

                tileArray.push_back(tileData);
            } else if(isLootChest) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();

                tileData["type"] = "lootChest";
                tileData["row"] = position.row;
                tileData["column"] = position.column;

                tileArray.push_back(tileData);
            } else if(isSwitch) {
                nlohmann::json tileData;
                RowColumn switchPosition = tile->getRowColumn();

                auto passiveVector = isSwitch->getPassiveVector();
                Door* door = dynamic_cast<Door*>(passiveVector.at(0));
                RowColumn doorPosition = door->getRowColumn();

                tileData["type"] = "door";
                tileData["row"] = doorPosition.row;
                tileData["column"] = doorPosition.column;
                tileData["switchRow"] = switchPosition.row;
                tileData["switchColumn"] = switchPosition.column;
                tileData["isOpen"] = door->getIsOpen();

                tileArray.push_back(tileData);
            } else if(isPortal) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();
                RowColumn destination = isPortal->getDestination()->getRowColumn();

                tileData["type"] = "portal";
                tileData["row"] = position.row;
                tileData["column"] = position.column;
                tileData["destinationRow"] = destination.row;
                tileData["destinationColumn"] = destination.column;

                tileArray.push_back(tileData);
            } else if(isLevelChanger) {
                nlohmann::json tileData;
                RowColumn position = tile->getRowColumn();

                tileData["type"] = "levelChanger";
                tileData["row"] = position.row;
                tileData["column"] = position.column;

                tileArray.push_back(tileData);
            }
        }
    }

    levelJson["specialTiles"] = tileArray;

    //export characters
    auto characterArray = nlohmann::json::array();
    auto characterVector = level->getCharacterVector();

    for(auto& character : characterVector) {
        AttackingNonPlayerCharacter* isAttackCharacter = dynamic_cast<AttackingNonPlayerCharacter*>(character);
        DynamicNonPlayerCharacter* isDynamicCharacter = dynamic_cast<DynamicNonPlayerCharacter*>(character);
        StaticNonPlayerCharacter* isStaticCharacter = dynamic_cast<StaticNonPlayerCharacter*>(character);

        bool isAlive = character->getAliveState();

        if(isAttackCharacter && isAlive) {
            nlohmann::json characterData;
            RowColumn position = character->getRowColumn();

            characterData["type"] = "attack";
            characterData["row"] = position.row;
            characterData["column"] = position.column;
            characterData["stamina"] = character->getStamina();
            characterData["strength"] = character->getStrength();
            characterData["hitpoints"] = character->getHitpoints();

            characterArray.push_back(characterData);
        } else if(isDynamicCharacter && isAlive) {
            nlohmann::json characterData;
            RowColumn position = character->getRowColumn();

            characterData["type"] = "dynamic";
            characterData["row"] = position.row;
            characterData["column"] = position.column;
            characterData["stamina"] = character->getStamina();
            characterData["strength"] = character->getStrength();
            characterData["hitpoints"] = character->getHitpoints();
            characterData["currentIndex"] = isDynamicCharacter->getPathIndex();
            characterData["path"] = isDynamicCharacter->getPath();

            characterArray.push_back(characterData);
        } else if(isStaticCharacter && isAlive) {
            nlohmann::json characterData;
            RowColumn position = character->getRowColumn();

            characterData["type"] = "static";
            characterData["row"] = position.row;
            characterData["column"] = position.column;
            characterData["stamina"] = character->getStamina();
            characterData["strength"] = character->getStrength();
            characterData["hitpoints"] = character->getHitpoints();

            characterArray.push_back(characterData);
        }
    }

    levelJson["characters"] = characterArray;

    levelArray.push_back(levelJson);
}

void LevelExporter::dumpMainCharacter(MainCharacter* mainCharacter) {
    nlohmann::json mainCharacterData;

    RowColumn position = mainCharacter->getRowColumn();

    mainCharacterData["row"] = position.row;
    mainCharacterData["column"] = position.column;
    mainCharacterData["stamina"] = mainCharacter->getStamina();
    mainCharacterData["strength"] = mainCharacter->getStrength();
    mainCharacterData["hitpoints"] = mainCharacter->getHitpoints();

    jsonExport["mainCharacter"] = mainCharacterData;
}

void LevelExporter::createMetadata(bool validSave) {
    jsonExport["meta"]["info"] = "this file is created by DungeonCrawler";
    jsonExport["meta"]["validSave"] = validSave;
}
