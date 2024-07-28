#include "levelimporter.h"

#include "../ui/abstractui.h"
#include "../engine/observer/passive.h"
#include "../engine/character/maincharacter.h"
#include "../engine/character/attackingnonplayercharacter.h"
#include "../engine/character/dynamicnonplayercharacter.h"
#include "../engine/character/staticnonplayercharacter.h"
#include "../engine/management/level.h"


LevelImporter::LevelImporter(std::shared_ptr<AbstractUi> userInterface, Passive *passive) :
    userInterface(userInterface), passive(passive) {
}

std::pair<List<std::shared_ptr<Level>>, MainCharacter*>& LevelImporter::importFile(const std::string& fileName) {
    //file import
    std::ifstream inputFile(fileName);

    if(!inputFile.good()) { //file is not good
        throw std::domain_error("corrupted file");
    }

    inputFile >> jsonImport;    //push data into json

    printMetadata(jsonImport["meta"]);  //print some nice information


    //abort if file has no entries
    bool validFile = jsonImport["meta"]["validSave"].get<bool>();
    if (!validFile) {
        std::cout << "[WARNING]: old save is not valid" << std::endl;
        returnPair.second = nullptr;
        return returnPair;
    }

    returnPair.second = createMainCharacter();
    createLevels();
    connectLevelChangers();


    inputFile.close();
    return returnPair;
}

void LevelImporter::printMetadata(const nlohmann::json& json) const {
    std::cout << "[LEVEL_IMPORTER]: import levels from file" << std::endl;
    std::cout << "[INFO]: " << json["info"].get<std::string>() << std::endl;
    std::cout << "[VALID_SAVE]: " << json["validSave"] << std::endl;
}

MainCharacter* LevelImporter::createMainCharacter() {
    int stamina = jsonImport["mainCharacter"]["stamina"].get<int>();
    int strength = jsonImport["mainCharacter"]["strength"].get<int>();
    int hitpoints = jsonImport["mainCharacter"]["hitpoints"].get<int>();
    RowColumn startingPosition(jsonImport["mainCharacter"]["row"].get<int>(), jsonImport["mainCharacter"]["column"].get<int>());

    return MainCharacter::createMainCharacter(userInterface, strength, stamina, hitpoints, passive, startingPosition);
}

void LevelImporter::connectLevelChangers() {
    auto iterator = returnPair.first.begin();
    auto endIterator = returnPair.first.end();

    while(iterator != endIterator) {
        auto currentLevel = *iterator;

        ++iterator;

        std::shared_ptr<Level> nextLevel;

        if(iterator == endIterator) {
            nextLevel = *returnPair.first.begin();
        } else {
            nextLevel = *iterator;
        }

        currentLevel->setLevelChangerDestination(nextLevel->getSpawnDestination());
    }
}

void LevelImporter::createLevels() {
    auto levelArray = jsonImport["levels"];
    MainCharacter* mainCharacter = returnPair.second;
    for(auto& level : levelArray) {
        //create level
        RowColumn levelDimensions(level["rows"].get<int>(), level["columns"].get<int>());
        RowColumn spawnDestination(level["spawnRow"].get<int>(), level["spawnColumn"].get<int>());

        std::shared_ptr<Level> currentLevel = std::make_shared<Level>(userInterface, levelDimensions, spawnDestination, mainCharacter);

        //place tiles
        auto tileArray = level["specialTiles"];
        for(auto& tile : tileArray) {
            std::string type = tile["type"].get<std::string>();
            RowColumn position(tile["row"].get<int>(), tile["column"].get<int>());

            if(type == "wall") {
                currentLevel->placeWall(position);
            } else if(type == "pit") {
                currentLevel->placePit(position);
            } else if(type == "ramp") {
                currentLevel->placeRamp(position);
            } else if(type == "lootChest") {
                currentLevel->placeLootChest(position);
            } else if(type == "door") {
                RowColumn switchPosition(tile["switchRow"].get<int>(), tile["switchColumn"].get<int>());
                bool isOpen = tile["isOpen"].get<bool>();
                currentLevel->placeDoor(position, switchPosition, isOpen);
            } else if(type == "portal") {
                RowColumn destinationPosition(tile["destinationRow"].get<int>(), tile["destinationColumn"].get<int>());
                if(dynamic_cast<Portal*>(currentLevel->getTileVector().at(position.row).at(position.column))) {
                } else {
                    currentLevel->placePortals(position, destinationPosition);
                }
            } else if(type == "levelChanger") {
                currentLevel->placeLevelChanger(position, passive);

            } else {
                std::cout << "[WARNING]: "<< type << " is an invalid tile type" << std::endl;
            }
        }

         //place characters
        auto characterArray = level["characters"];
        for(auto& character : characterArray) {
            std::string type = character["type"].get<std::string>();
            int stamina = character["stamina"].get<int>();
            int strength = character["strength"].get<int>();
            int hitpoints = character["hitpoints"].get<int>();
            RowColumn position(character["row"].get<int>(), character["column"].get<int>());

            if(type == "static") {
                currentLevel->placeCharacter(new StaticNonPlayerCharacter(strength,stamina, hitpoints), position);
            } else if(type == "dynamic") {
                std::size_t currentIndex = character["currentIndex"].get<std::size_t>();
                std::string path = character["path"].get<std::string>();
                currentLevel->placeCharacter(new DynamicNonPlayerCharacter(strength,stamina, hitpoints, path, currentIndex), position);
            } else if(type == "attack") {
                currentLevel->placeCharacter(new AttackingNonPlayerCharacter(strength,stamina, hitpoints), position);
            } else {
                std::cout << "[WARNING]: "<< type << " is an invalid character type" << std::endl;
            }
        }

        //level imported
        returnPair.first.pushBack(currentLevel);
    }
}
