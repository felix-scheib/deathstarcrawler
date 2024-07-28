//------------------------------------------------------------------------------
//-----dungeon crawler----------------------------------------------------------
//------------------------------------------------------------------------------

#include "dungeoncrawler.h"

//constructors
DungeonCrawler::DungeonCrawler() : currentLevelIterator(nullptr, nullptr) {
    userInterface = std::make_shared<GraphicalUi>(this);
    levelImporter = std::make_shared<LevelImporter>(userInterface, this);
    levelExporter = std::make_shared<LevelExporter>();
}

DungeonCrawler::~DungeonCrawler() {
    if(!hasPrinted) {   //exporting level data
        levelExporter->dumpMetaData(true);
        levelExporter->dumpMainCharacter(mainCharacter);

        auto cmpLevelIterator = currentLevelIterator;

        do {
            auto level = *currentLevelIterator;
            levelExporter->dumpLevel(level.get());

            ++currentLevelIterator;

            if(currentLevelIterator == levelList.end()) {
                currentLevelIterator = levelList.begin();
            }

        } while(currentLevelIterator != cmpLevelIterator);

        levelExporter->exportLevelFile();
    }
    delete mainCharacter;
}



//play
void DungeonCrawler::play() {
    gameActive = true;

    currentLevel = *currentLevelIterator;
    while (gameActive) {
        if(mainCharacterActive) {
            userInterface->draw(currentLevel);
            gameActive = currentLevel->moveAllCharacters();
        } else {
            userInterface->draw(currentLevel);
            GraphicalUi* graphicalUi = dynamic_cast<GraphicalUi*>(userInterface.get());
            graphicalUi->showMessage(mainCharacter->getAliveState());
            gameActive = false;
        }
    }
}

void DungeonCrawler::active() {
    userInterface->wait();
}

//observer
void DungeonCrawler::notify(Active* active) {
    if(dynamic_cast<LevelChanger*>(active)) {
            changeLevel();
    }
    MainCharacter* mainCharacter = dynamic_cast<MainCharacter*>(active);
    if(mainCharacter) {
        if(mainCharacter->getAliveState()) {
            mainCharacterActive = false;

            levelExporter->exportEmptyFile();
            hasPrinted = true;
        } else {
            mainCharacterActive = false;

            levelExporter->exportEmptyFile();
            hasPrinted = true;
        }
    }
}

void DungeonCrawler::changeLevel() {
    ++currentLevelIterator;

    if(currentLevelIterator == levelList.end()) {
        currentLevelIterator = levelList.begin();
    }
    currentLevel = *currentLevelIterator;
    currentLevel->initGraph();
}

Tile* DungeonCrawler::getOtherLevelSpawnDestination() {
    return currentLevel->getSpawnDestination();
}

void DungeonCrawler::reloadGame() {
    auto returnPair = levelImporter->importFile(JsonPaths::STORE_PATH);    //import level

    if(returnPair.second) {
        levelList = returnPair.first;
        mainCharacter = returnPair.second;

        mainCharacterActive = true;

        currentLevelIterator = levelList.begin();

        auto level1 = *currentLevelIterator;

        level1->spawnMainCharacter();
        level1->initGraph();
    } else {
        newGame();
    }
}

void DungeonCrawler::newGame() {
    auto returnPair = levelImporter->importFile(JsonPaths::DEFAULT_PATH);    //import level

    levelList = returnPair.first;
    mainCharacter = returnPair.second;

    mainCharacterActive = true;

    currentLevelIterator = levelList.begin();

    auto level1 = *currentLevelIterator;

    level1->spawnMainCharacter();
    level1->initGraph();
}
