//------------------------------------------------------------------------------
//-----level--------------------------------------------------------------------
//------------------------------------------------------------------------------

#include "level.h"
#include "../observer/active.h"
#include "../observer/passive.h"

//friend methods
void swap(Level& lhs, Level& rhs) {
    std::swap(lhs.levelDimensions, rhs.levelDimensions);
    std::swap(lhs.tileVector, rhs.tileVector);
    std::swap(lhs.characterVector, rhs.characterVector);
    std::swap(lhs.userInterface, rhs.userInterface);
}

//constructors
Level::Level(std::shared_ptr<AbstractUi> userInterface, const RowColumn& levelDimensions, const RowColumn& spawnPosition, MainCharacter* mainCharacter) :
    levelDimensions(levelDimensions), userInterface(userInterface), spawnPosition(spawnPosition) {
    initializeTiles();

    characterVector.push_back(mainCharacter);
    spawnDestination = tileVector.at(this->spawnPosition.row).at(this->spawnPosition.column);

    tileGraph = std::make_unique<TileGraph>(this);
}

Level::Level(const Level& other) :
    levelDimensions(other.levelDimensions), userInterface(other.userInterface), hasLevelChanger(other.levelChanger) {
    tileGraph = std::make_unique<TileGraph>(this);
    std::cout << "[DEBUG]: copy operator called" << std::endl;
    resizeTileVector(); //init new tileVector with nullptr

    //Tile copy
    for(int row = 0; row < levelDimensions.row; ++row) {   //copy all tiles
        for(int column = 0; column < levelDimensions.column; ++column) {
            if(tileVector.at(row).at(column) == nullptr) {
                auto& tileType = typeid (*other.tileVector.at(row).at(column));
                if(tileType == typeid (Portal)) {
                    auto destPortal = dynamic_cast<Portal*>(other.tileVector.at(row).at(column));
                    auto destRowColumn = destPortal->getDestination()->getRowColumn();
                    tileVector.at(row).at(column) = new Portal(RowColumn(row, column), destRowColumn);
                    tileVector.at(destRowColumn.row).at(destRowColumn.column) = dynamic_cast<Portal*>(tileVector.at(row).at(column))->getDestination();
                } else if(tileType == typeid (Door)) {
                    tileVector.at(row).at(column) = new Door(RowColumn(row, column));
                } else if(tileType == typeid (Switch)) {
                    tileVector.at(row).at(column) = new Switch(RowColumn(row, column));
                } else if(tileType == typeid (Pit)) {
                    tileVector.at(row).at(column) = new Pit(RowColumn(row, column));
                } else if(tileType == typeid (Ramp)) {
                    tileVector.at(row).at(column) = new Ramp(RowColumn(row, column));
                } else if(tileType == typeid (Wall)) {
                    tileVector.at(row).at(column) = new Wall(RowColumn(row, column));
                } else if(tileType == typeid (LootChest)) {
                    tileVector.at(row).at(column) = new LootChest(RowColumn(row, column));
                } else if(tileType == typeid (LevelChanger)) {
                    levelChanger = new LevelChanger(RowColumn(row, column));
                    tileVector.at(row).at(column) = levelChanger;
                } else {
                    tileVector.at(row).at(column) = new Floor(RowColumn(row, column));
                }
            } else {
                continue;   //portal destination is placed
            }
        }
    }

    //Observer Copy
    for(int row = 0; row < levelDimensions.row; ++row) {
        for(int column = 0; column < levelDimensions.column; ++column) {
            Active* otherActiveClass = dynamic_cast<Active*>(other.tileVector.at(row).at(column));   //upcast active class from other level
            if(otherActiveClass) {   //is active class
                auto& otherPassiveVector = otherActiveClass->getPassiveVector();  //get passive vector from other level

                Active* thisActiveClass = dynamic_cast<Active*>(tileVector.at(row).at(column)); //get activeClass from new level

                if(!dynamic_cast<LevelChanger*>(otherActiveClass)) {    //is no level changer
                    for(auto& passiveClass : otherPassiveVector) {  //attach all passive tiles to tile vector

                        Tile* passiveTile = dynamic_cast<Tile*>(passiveClass);
                        int row = passiveTile->getRowColumn().row;
                        int column = passiveTile->getRowColumn().column;

                        Passive* thisPassiveClass = dynamic_cast<Passive*>(tileVector.at(row).at(column)); //get activeClass from new level

                        thisActiveClass->attach(thisPassiveClass);
                    }
                } else {    //is level changer
                    for(auto& passiveClass : otherPassiveVector) {  //attach all passive tiles to tile vector
                        //levelChanger = dynamic_cast<LevelChanger*>(passiveClass);
                        thisActiveClass->attach(passiveClass);
                    }
                }
            }
        }
    }

    //Character Copy
    for(auto& character : other.characterVector) {  //copy characters
        if(dynamic_cast<MainCharacter*>(character)) {
            characterVector.push_back(character);
        } else {
            StaticNonPlayerCharacter* checkForStatic = dynamic_cast<StaticNonPlayerCharacter*>(character);
            DynamicNonPlayerCharacter* checkForDynamic = dynamic_cast<DynamicNonPlayerCharacter*>(character);
            AttackingNonPlayerCharacter* checkForAttack = dynamic_cast<AttackingNonPlayerCharacter*>(character);

            if(checkForStatic) {
                Character* newCharacter = new StaticNonPlayerCharacter(*checkForStatic);
                RowColumn tileCoordinates = character->getRowColumn();
                newCharacter->setTile(tileVector.at(tileCoordinates.row).at(tileCoordinates.column));
                characterVector.push_back(newCharacter);
            } else if(checkForDynamic)  {
                Character* newCharacter = new DynamicNonPlayerCharacter(*checkForDynamic);
                RowColumn tileCoordinates = character->getRowColumn();
                newCharacter->setTile(tileVector.at(tileCoordinates.row).at(tileCoordinates.column));
                characterVector.push_back(newCharacter);
            } else if(checkForAttack) {
                Character* newCharacter = new AttackingNonPlayerCharacter(*checkForAttack);
                RowColumn tileCoordinates = character->getRowColumn();
                newCharacter->setTile(tileVector.at(tileCoordinates.row).at(tileCoordinates.column));
                characterVector.push_back(newCharacter);
            }
        }
        spawnPosition = other.spawnPosition;
        spawnDestination = tileVector.at(spawnPosition.row).at(spawnPosition.column);
    }
}

Level::~Level() {
    for(auto& character : characterVector) {
        if(!dynamic_cast<MainCharacter*>(character)) {
            delete character;
        }
    }

    for(auto& row : tileVector) {
        for(auto& tile : row) {
            delete tile;
        }
    }
}

Level& Level::operator=(Level other) {
    std::cout << "[DEBUG]: assignment operator called" << std::endl;
    swap(*this, other);
    return *this;
}

//getter
Tile* Level::getTile(RowColumn rowColumn) const {
    if(isInsideLevelDimensions(rowColumn)) {
        return tileVector.at(rowColumn.row).at(rowColumn.column);
    } else {
        return nullptr;
    }
}

Tile* Level::getTile(int row, int column) const {
    return getTile(RowColumn(row, column));
}

const std::vector<std::vector<Tile*>>& Level::getTileVector() const {
    return tileVector;
}

RowColumn Level::getRowColumns() const {
    return levelDimensions;
}

const std::vector<Character*>& Level::getCharacterVector() const {
    return characterVector;
}

//move
bool Level::moveAllCharacters() {
    for(auto& character : characterVector) {
        if(character->getAliveState()) {
            AttackingNonPlayerCharacter* attackingCharacter = dynamic_cast<AttackingNonPlayerCharacter*>(character);
            if(attackingCharacter) {
                auto mainCharacterTile = characterVector.at(0)->getTile();
                auto path = getPath(character->getTile(), mainCharacterTile); //getPath

                if(path.begin() == path.end()) {
                    attackingCharacter->stayOnTile();
                } else {
                    RowColumn begin = *path.begin();
                    path.pop_front();
                    RowColumn second;

                    if(path.begin() != path.end()) {
                        second = *path.begin();
                    } else {
                        second = begin;
                    }

                    attackingCharacter->setDestination(begin, second);
                }
            }
            if(!moveCharacter(character)) {
                return false;
            }
        }
    }
    return true;
}

std::list<RowColumn>& Level::getPath(Tile* fromTile, Tile* toTile) {
    return tileGraph->shortestPath(fromTile, toTile);
}

//place tiles
void Level::placeWall(const RowColumn& wallPosition) {
    delete tileVector.at(wallPosition.row).at(wallPosition.column);
    tileVector.at(wallPosition.row).at(wallPosition.column) = new Wall(wallPosition);
}

void Level::placePit(const RowColumn& pitPosition) {
    delete tileVector.at(pitPosition.row).at(pitPosition.column);
    tileVector.at(pitPosition.row).at(pitPosition.column) = new Pit(pitPosition);
}

void Level::placeRamp(const RowColumn& rampPosition) {
    delete tileVector.at(rampPosition.row).at(rampPosition.column);
    tileVector.at(rampPosition.row).at(rampPosition.column) = new Ramp(rampPosition);
}

void Level::placeLootChest(const RowColumn& lootPosition) {
        delete tileVector.at(lootPosition.row).at(lootPosition.column);
        tileVector.at(lootPosition.row).at(lootPosition.column) = new LootChest(lootPosition);
}

void Level::placeDoor(RowColumn doorPosition, RowColumn switchPosition, bool isOpen) {
    delete tileVector.at(doorPosition.row).at(doorPosition.column);
    delete tileVector.at(switchPosition.row).at(switchPosition.column);

    Door* door = new Door(doorPosition, isOpen);
    Switch* switchTile = new Switch(switchPosition);
    switchTile->attach(door);

    tileVector.at(doorPosition.row).at(doorPosition.column) = door;
    tileVector.at(switchPosition.row).at(switchPosition.column) = switchTile;
}

void Level::placePortals(RowColumn portal1Position, RowColumn portal2Position) {
    delete tileVector.at(portal1Position.row).at(portal1Position.column);
    delete tileVector.at(portal2Position.row).at(portal2Position.column);

    Portal* portal1 = new Portal(portal1Position, portal2Position);
    Portal* portal2 = dynamic_cast<Portal*>(portal1->getDestination());

    tileVector.at(portal1Position.row).at(portal1Position.column) = portal1;
    tileVector.at(portal2Position.row).at(portal2Position.column) = portal2;
}








bool Level::isInsideLevelDimensions(RowColumn rowColumn) const {
    bool isInsideRows = (rowColumn.row >= 0 && rowColumn.row < levelDimensions.row);
    bool isInsideColumns = (rowColumn.column >= 0 && rowColumn.column < levelDimensions.column);
    return (isInsideRows && isInsideColumns);
}

RowColumn Level::inputToPosition(char input) {
    switch (input) {
        case UserInput::TRIGGER_TOP_LEFT : return RowColumn(MovementDirection::DECREMENT, MovementDirection::DECREMENT);
        case UserInput::TRIGGER_TOP_CENTER : return RowColumn(MovementDirection::DECREMENT, MovementDirection::CENTER);
        case UserInput::TRIGGER_TOP_RIGHT : return RowColumn(MovementDirection::DECREMENT,MovementDirection::INCREMENT);
        case UserInput::TRIGGER_CENTER_LEFT : return RowColumn(MovementDirection::CENTER, MovementDirection::DECREMENT);
        case UserInput::TRIGGER_CENTER_CENTER : return RowColumn(MovementDirection::CENTER, MovementDirection::CENTER);
        case UserInput::TRIGGER_CENTER_RIGHT : return RowColumn(MovementDirection::CENTER,MovementDirection::INCREMENT);
        case UserInput::TRIGGER_BOTTOM_LEFT : return RowColumn(MovementDirection::INCREMENT, MovementDirection::DECREMENT);
        case UserInput::TRIGGER_BOTTOM_CENTER : return RowColumn(MovementDirection::INCREMENT,MovementDirection::CENTER);
        case UserInput::TRIGGER_BOTTOM_RIGHT : return RowColumn(MovementDirection::INCREMENT,MovementDirection::INCREMENT);
        default : return RowColumn(MovementDirection::CENTER, MovementDirection::CENTER);
    }
}

bool Level::moveCharacter(Character* character, bool doorClosed) {
    char input;

    if(doorClosed && dynamic_cast<AttackingNonPlayerCharacter*>(character)) {
        input = UserInput::TRIGGER_CENTER_CENTER;
    } else {
            input = character->move();
    }

    if(tolower(input) == UserInput::TRIGGER_EXIT) {
        return false;
    } else {
        RowColumn currentPosition = character->getRowColumn();
        RowColumn destinationPostion = currentPosition + inputToPosition(input);

        Tile* currentTile = character->getTile();
        Tile* destinationTile = tileVector.at(destinationPostion.row).at(destinationPostion.column);

        if(typeid (*currentTile) == typeid (Pit)) {
            if((typeid (*destinationTile) == typeid (Pit)) || (typeid (*destinationTile) == typeid (Ramp))) {
                return currentTile->moveTo(destinationTile, character);
            } else {
                std::cout << "trapped inside a pit" << std::endl;
                return moveCharacter(character);
            }
        }

        if(typeid (*destinationTile) == typeid (Wall)) {
            std::cout << "walked against a wall" << std::endl;
            return moveCharacter(character);
        } else if(typeid (*destinationTile) == typeid (Door)) {
            if(!dynamic_cast<Door*>(destinationTile)->getIsOpen()) {
                std::cout << "walked against a closed Door" << std::endl;
                return moveCharacter(character, true);
            } else {
                return currentTile->moveTo(destinationTile, character);
            }
        } else {
            return currentTile->moveTo(destinationTile, character);
        }
    }
}

//initialization methods
void Level::initializeTiles() {
    resizeTileVector();
    placeTiles();
}

bool Level::isBorderWall(RowColumn rowColumn) {
    bool isRowWall = ((rowColumn.row == 0) || (rowColumn.row == (levelDimensions.row - 1)));
    bool isColumnWall = ((rowColumn.column == 0) || (rowColumn.column == (levelDimensions.column - 1)));
    return (isRowWall || isColumnWall);
}

void Level::resizeTileVector() {
    tileVector.resize(levelDimensions.row, std::vector<Tile*>(levelDimensions.column, nullptr));
}

void Level::placeTiles() {
    for(int i = 0; i < levelDimensions.row; ++i) {
        for(int j = 0; j < levelDimensions.column; ++j) {
            if(isBorderWall(RowColumn(i, j))) {
                tileVector.at(i).at(j) = new Wall(RowColumn(i, j));
            } else {
                tileVector.at(i).at(j) = new Floor(RowColumn(i, j));
            }
        }
    }
}

void Level::placeCharacter(Character* c, RowColumn rowColumn) {
    c->setTile(tileVector.at(rowColumn.row).at(rowColumn.column));
    characterVector.push_back(c);
}

void Level::placeCharacter(Character* c, int row, int column) {
    placeCharacter(c, RowColumn(row, column));
}

void Level::placeLevelChanger(RowColumn position, Passive* passive){
    delete tileVector.at(position.row).at(position.column);

    if(!hasLevelChanger) {
        levelChanger = new LevelChanger(position);

        levelChanger->attach(passive);

        tileVector.at(position.row).at(position.column) = levelChanger;
    }
}

void Level::setLevelChangerDestination(Tile* destination) {
    for(auto& subvector : tileVector) {
        for(auto& tile : subvector) {
            auto castedTile = dynamic_cast<LevelChanger*>(tile);
            if(castedTile) {
                castedTile->setDestinationTile(destination);
            }
        }
    }
}

void Level::spawnMainCharacter() {
    MainCharacter* mainCharacter = dynamic_cast<MainCharacter*>(characterVector.at(0));
    RowColumn startingPosition = mainCharacter->getStartingPosition();

    Tile* startingTile = tileVector.at(startingPosition.row).at(startingPosition.column);
    mainCharacter->setTile(startingTile);
}

Tile* Level::getSpawnDestination() const {
    return spawnDestination;
}

const RowColumn &Level::getSpawnPosition() const {
    return spawnPosition;
}

bool Level::insideLevel(const RowColumn& rowColumn) const {
    bool insideRow = rowColumn.row >= 0 && (rowColumn.row < levelDimensions.row);
    bool insideColumn = rowColumn.column >= 0 && (rowColumn.column < levelDimensions.column);

    return insideRow && insideColumn;
}

LevelChanger* Level::getLevelChanger() const {
    return levelChanger;
}
