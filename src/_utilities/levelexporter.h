#ifndef LEVELEXPORTER_H
#define LEVELEXPORTER_H

#include "../_extern/json.hpp"
#include "../../_config/settings.h"

#include <string>
#include <fstream>
#include <iostream>

class MainCharacter;
class Level;

class LevelExporter {
public:
    LevelExporter() = default;

    void exportEmptyFile();
    void exportLevelFile();

    void dumpMetaData(bool validSave);
    void dumpLevel(Level* level);
    void dumpMainCharacter(MainCharacter* mainCharacter);
private:
    nlohmann::json jsonExport;
    nlohmann::json levelArray;

    void createMetadata(bool validSave);
};

#endif // LEVELEXPORTER_H
