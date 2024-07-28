//------------------------------------------------------------------------------
//-----dungeon crawler----------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "../../ui/terminalui.h"
#include "../../ui/gui/graphicalui.h"
#include "level.h"
#include "../../../_config/settings.h"
#include "../../_utilities/levelexporter.h"
#include "../../_utilities/levelimporter.h"
#include "../observer/passive.h"
#include "../character/maincharacter.h"
#include "stationarycontroller.h"
#include "../../../_config/settings.h"

#include <memory>

class Active;

class DungeonCrawler : public Passive {
public:
    //constructors
    DungeonCrawler();
    ~DungeonCrawler();

    //play
    void play();
    void active();

    //observer
    void notify(Active* active) override;

    Tile* getOtherLevelSpawnDestination();

    void reloadGame();
    void newGame();
private:
    //member variables
    bool hasPrinted = false;
    bool gameActive;
    bool mainCharacterActive;
    std::shared_ptr<AbstractUi> userInterface;
    std::shared_ptr<Level> currentLevel;
    List<std::shared_ptr<Level>> levelList;
    List<std::shared_ptr<Level>>::Iterator currentLevelIterator;

    std::shared_ptr<LevelImporter> levelImporter;
    std::shared_ptr<LevelExporter> levelExporter;

    MainCharacter* mainCharacter;

    void changeLevel();
};

#endif // DUNGEONCRAWLER_H
