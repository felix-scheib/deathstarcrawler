//------------------------------------------------------------------------------
//-----global settings for gameplay---------------------------------------------
//------------------------------------------------------------------------------

#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace JsonPaths {
    static const std::string DEFAULT_PATH = "../../_jsonFiles/defaultLevels.json";
    static const std::string STORE_PATH = "../../_jsonFiles/savedLevels.json";

    //paths if relative paths won't work
    //static const std::string DEFAULT_PATH = "defaultLevels.json";
    //static const std::string STORE_PATH = "savedLevels.json";
}

namespace GameSettings {
    static const int ATTACKING_STEPS = 4;   //steps after attacker takes a break
}

namespace TileAppearances {
    static const std::string FLOOR_TEXTURE = " . ";
    static const std::string PORTAL_TEXTURE = " O ";
    static const std::string WALL_TEXTURE = " # ";
    static const std::string SWITCH_TEXTURE = " ? ";
    static const std::string DOOR_OPEN_TEXTURE = " / ";
    static const std::string DOOR_CLOSED_TEXTURE = " X ";
    static const std::string PIT_TEXTURE = " P ";
    static const std::string RAMP_TEXTURE = " R ";
    static const std::string LEVEL_CHANGER_TEXTURE = " L ";
}

namespace CharacterTextures {
    static const std::string CHARACTER_TEXTURE = " C ";
    static const std::string ENEMY_TEXTURE = " E ";
}

namespace UserInput {
    static const std::string INPUT_SIGNALS = "qweasdyxcm";

    static const char TRIGGER_EXIT = 'm';

    static const char NO_INPUT = 'N';

    static const char TRIGGER_TOP_LEFT = 'q';
    static const char TRIGGER_TOP_CENTER = 'w';
    static const char TRIGGER_TOP_RIGHT = 'e';
    static const char TRIGGER_CENTER_LEFT = 'a';
    static const char TRIGGER_CENTER_CENTER = 's';
    static const char TRIGGER_CENTER_RIGHT = 'd';
    static const char TRIGGER_BOTTOM_LEFT = 'y';
    static const char TRIGGER_BOTTOM_CENTER = 'x';
    static const char TRIGGER_BOTTOM_RIGHT = 'c';

    static const char TRIGGER_ARRAY[9] {'q', 'w', 'e', 'a', 's', 'd', 'y', 'x', 'c'};
}

enum MovementDirection {DECREMENT = -1, CENTER = 0, INCREMENT = 1};

#endif // SETTINGS_H
