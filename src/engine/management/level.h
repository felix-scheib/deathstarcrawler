//------------------------------------------------------------------------------
//-----level--------------------------------------------------------------------
//------------------------------------------------------------------------------

//TODO

#ifndef LEVEL_H
#define LEVEL_H

#include "../../../_config/settings.h"
#include "../../_utilities/rowcolumn.h"
#include "../../_utilities/tilegraph.h"
#include "../character/maincharacter.h"
#include "../character/staticnonplayercharacter.h"
#include "../character/dynamicnonplayercharacter.h"
#include "../character/attackingnonplayercharacter.h"
#include "../../ui/terminalui.h"
#include "../../ui/gui/graphicalui.h"
#include "../tile/children/floor.h"
#include "../tile/children/portal.h"
#include "../tile/children/wall.h"
#include "../tile/children/door.h"
#include "../tile/children/switch.h"
#include "../tile/children/pit.h"
#include "../tile/children/ramp.h"
#include "../tile/children/levelchanger.h"
#include "../tile/children/lootchest.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <list>

class Passive;

class Level {
public:
    //friend methods
    friend void swap(Level& lhs, Level& rhs);

    //constructors
    Level(std::shared_ptr<AbstractUi> userInterface, const RowColumn& levelDimensions, const RowColumn& spawnPosition, MainCharacter* mainCharacter = nullptr);
    Level(const Level& other);
    ~Level();

    //operators
    Level& operator=(Level other);

    //getter
    Tile* getTile(RowColumn rowColumn) const;
    Tile* getTile(int row, int column) const;
    const std::vector<std::vector<Tile*>>& getTileVector() const;
    const std::vector<Character*>& getCharacterVector() const;

    RowColumn getRowColumns() const;
    LevelChanger* getLevelChanger() const;

    //move
    bool moveAllCharacters();

    //methods for placing tiles
    void placeWall(const RowColumn& wallPosition);
    void placePit(const RowColumn& pitPosition);
    void placeRamp(const RowColumn& rampPosition);
    void placeLootChest(const RowColumn& position);
    void placeDoor(RowColumn doorPosition, RowColumn switchPosition, bool isOpen);
    void placePortals(RowColumn portal1Position, RowColumn portal2Position);
    void placeLevelChanger(RowColumn position, Passive* passive);

    void placeCharacter(Character* c, RowColumn rowColumn);
    void placeCharacter(Character* c, int row, int column);

    void setLevelChangerDestination(Tile* Destination);

    void spawnMainCharacter();

    Tile* getSpawnDestination() const;
    const RowColumn& getSpawnPosition() const;

    bool insideLevel(const RowColumn& rowColumn) const;

    void initGraph() {tileGraph->initializeGraph();}

private:
    //member variables
    RowColumn levelDimensions;
    std::vector<std::vector<Tile*>> tileVector;
    std::vector<Character*> characterVector;
    std::shared_ptr<AbstractUi> userInterface;

    std::unique_ptr<TileGraph> tileGraph;

    Tile* spawnDestination;
    RowColumn spawnPosition;

    LevelChanger* levelChanger;
    bool hasLevelChanger = false;

    //move
    bool isInsideLevelDimensions(RowColumn rowColumn) const;
    RowColumn inputToPosition(char input);
    bool moveCharacter(Character* character, bool doorClosed = false);

    std::list<RowColumn>& getPath(Tile* fromTile, Tile* toTile);

    //initialization methods
    void initializeTiles();
    bool isBorderWall(RowColumn rowColumn);
    void resizeTileVector();
    void placeTiles();
};

#endif // LEVEL_H
