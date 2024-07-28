#ifndef LEVELIMPORTER_H
#define LEVELIMPORTER_H

#include "../_extern/json.hpp"
#include "list.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>

class AbstractUi;
class Passive;
class MainCharacter;
class Level;

class LevelImporter {
public:
    LevelImporter(std::shared_ptr<AbstractUi> userInterface, Passive* passive);

    std::pair<List<std::shared_ptr<Level>>, MainCharacter*>& importFile(const std::string& fileName);

private:
    nlohmann::json jsonImport;

    std::shared_ptr<AbstractUi> userInterface;
    Passive* passive;

    std::pair<List<std::shared_ptr<Level>>, MainCharacter*> returnPair;

    void printMetadata(const nlohmann::json& json) const;
    void printLevels(const nlohmann::json& json) const;

    void createLevels();
    MainCharacter* createMainCharacter();

    void connectLevelChangers();
};

#endif // LEVELIMPORTER_H
