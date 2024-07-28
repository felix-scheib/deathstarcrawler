//------------------------------------------------------------------------------
//-----paths for textures-------------------------------------------------------
//------------------------------------------------------------------------------

#ifndef TEXTURES_H
#define TEXTURES_H

#include <QString>

namespace TitleBarLabels  {
    static const QString STARTSCREEN_LABEL = "Menu";
    static const QString MAINWINDOW_LABEL = "Deathstar Crawler";
}

enum TitleBarTexturesIndex {STARTTITLEBAR_TEXTURE = 0, GAMETITLEBAR_TEXTURE = 1};

namespace TitleBarTextures {
    static const QString STARTTITLEBAR_TEXTURE = "://textures/titlebar/t_start_title_32.png";
    static const QString GAMETITLEBAR_TEXTURE = "://textures/titlebar/t_game_title_32.png";
}

enum StartScreenTexturesIndex {BACKGROUND_TEXTURE = 0, STARTBUTTON_DEFAULT_TEXTURE = 1, STARTBUTTON_HOVER_TEXTURE = 2, CONTINUEBUTTON_DEFAULT_TEXTURE = 3, CONTINUEBUTTON_HOVER_TEXTURE = 4};

namespace StartScreenTextures {
    static const QString BACKGROUND_TEXTURE = "://textures/ui/startscreen/t_startscreen_background_1280_720.png";
    static const QString STARTBUTTON_DEFAULT_TEXTURE = "://textures/ui/startscreen/t_startbutton_inactive_330_55.png";
    static const QString STARTBUTTON_HOVER_TEXTURE = "://textures/ui/startscreen/t_startbutton_active_330_55.png";
    static const QString CONTINUEBUTTON_DEFAULT_TEXTURE = "://textures/ui/startscreen/t_continuebutton_inactive_330_55.png";
    static const QString CONTINUEBUTTON_HOVER_TEXTURE = "://textures/ui/startscreen/t_continuebutton_active_330_55.png";
}

enum MainWindowTexturesIndex {
    MAINWINDOW_BACKGROUND_TEXTURE = 0,
    MAINWINDOW_OVERLAY_TEXTURE = 1
};

namespace OverlayTextures {
    static const QString WINNING_OVERLAY_TEXTURE = "://textures/ui/popups/t_winning_overlay_1280_720.png";
    static const QString LOOSING_OVERLAY_TEXTURE = "://textures/ui/popups/t_loosing_overlay_1280_720.png";
}

enum OverlayTexturesIndex {WINNING_OVERLAY = 0, LOOSING_OVERLAY = 1};


namespace MainWindowTextures {
    static const QString MAINWINDOW_BACKGROUND_TEXTURE = "://textures/ui/mainwindow/t_mainwindow_background_1280_720.png";
    static const QString MAINWINDOW_OVERLAY_TEXTURE = "://textures/ui/mainwindow/t_mainwindow_overlay_1280_720.png";
}

enum ControlButtonTexturesIndex {
    CONTROLBUTTON_UPLEFT_DEFAULT_TEXTURE = 0,
    CONTROLBUTTON_UP_DEFAULT_TEXTURE = 1,
    CONTROLBUTTON_UPRIGHT_DEFAULT_TEXTURE = 2,
    CONTROLBUTTON_LEFT_DEFAULT_TEXTURE = 3,
    CONTROLBUTTON_SKIP_DEFAULT_TEXTURE = 4,
    CONTROLBUTTON_RIGHT_DEFAULT_TEXTURE = 5,
    CONTROLBUTTON_DOWNLEFT_DEFAULT_TEXTURE = 6,
    CONTROLBUTTON_DOWN_DEFAULT_TEXTURE = 7,
    CONTROLBUTTON_DOWNRIGHT_DEFAULT_TEXTURE = 8,

    CONTROLBUTTON_UPLEFT_HOVER_TEXTURE = 9,
    CONTROLBUTTON_UP_HOVER_TEXTURE = 10,
    CONTROLBUTTON_UPRIGHT_HOVER_TEXTURE = 11,
    CONTROLBUTTON_LEFT_HOVER_TEXTURE = 12,
    CONTROLBUTTON_SKIP_HOVER_TEXTURE = 13,
    CONTROLBUTTON_RIGHT_HOVER_TEXTURE = 14,
    CONTROLBUTTON_DOWNLEFT_HOVER_TEXTURE = 15,
    CONTROLBUTTON_DOWN_HOVER_TEXTURE = 16,
    CONTROLBUTTON_DOWNRIGHT_HOVER_TEXTURE = 17
};

namespace ControlButtonTextures {
    static const QString CONTROLBUTTON_UPLEFT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_01_button_upleft_inactive_96_96.png";
    static const QString CONTROLBUTTON_UP_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_02_button_up_inactive_60_96.png";
    static const QString CONTROLBUTTON_UPRIGHT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_03_button_upright_inactive_96_96.png";
    static const QString CONTROLBUTTON_LEFT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_04_button_left_inactive_96_60.png";
    static const QString CONTROLBUTTON_SKIP_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_05_button_skip_inactive_60_60.png";
    static const QString CONTROLBUTTON_RIGHT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_06_button_right_inactive_96_60.png";
    static const QString CONTROLBUTTON_DOWNLEFT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_07_button_downleft_inactive_96_96.png";
    static const QString CONTROLBUTTON_DOWN_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_08_button_down_inactive_60_96.png";
    static const QString CONTROLBUTTON_DOWNRIGHT_DEFAULT_TEXTURE = "://textures/ui/mainwindow/buttons/t_09_button_downright_inactive_96_96.png";

    static const QString CONTROLBUTTON_UPLEFT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_01_button_upleft_active_96_96.png";
    static const QString CONTROLBUTTON_UP_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_02_button_up_active_60_96.png";
    static const QString CONTROLBUTTON_UPRIGHT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_03_button_upright_active_96_96.png";
    static const QString CONTROLBUTTON_LEFT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_04_button_left_active_96_60.png";
    static const QString CONTROLBUTTON_SKIP_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_05_button_skip_active_60_60.png";
    static const QString CONTROLBUTTON_RIGHT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_06_button_right_active_96_60.png";
    static const QString CONTROLBUTTON_DOWNLEFT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_07_button_downleft_active_96_96.png";
    static const QString CONTROLBUTTON_DOWN_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_08_button_down_active_60_96.png";
    static const QString CONTROLBUTTON_DOWNRIGHT_HOVER_TEXTURE = "://textures/ui/mainwindow/buttons/t_09_button_downright_active_96_96.png";
}

enum TileTexturesIndex {
    FLOOR_START = 0,
    FLOOR_01 = 0,
    FLOOR_02 = 1,
    FLOOR_03 = 2,
    FLOOR_04 = 3,
    FLOOR_05 = 4,

    PIT_START = 5,
    PIT_01 = 5,
    PIT_02 = 6,
    PIT_03 = 7,
    PIT_04 = 8,
    PIT_05 = 9,

    PORTAL_START = 10,
    PORTAL_01 = 10,
    PORTAL_02 = 11,
    PORTAL_03 = 12,

    DOOR_CLOSED = 13,
    DOOR_OPEN = 14,

    RAMP_UP = 15,
    RAMP_DOWN = 16,
    RAMP_OVERLAY = 17,

    WALL_START = 18,
    WALL_01 = 18,
    WALL_02 = 19,
    WALL_03 = 20,
    WALL_04 = 21,

    SWITCH_INACTIVE = 22,
    SWITCH_ACTIVE = 23,

    LEVEL_CHANGER = 24,

    CHEST = 25
};

namespace TileTextures {
    static const QString FLOOR_01 = "://textures/tiles/01_floor/t_floor01_128_128.png";
    static const QString FLOOR_02 = "://textures/tiles/01_floor/t_floor02_128_128.png";
    static const QString FLOOR_03 = "://textures/tiles/01_floor/t_floor03_128_128.png";
    static const QString FLOOR_04 = "://textures/tiles/01_floor/t_floor04_128_128.png";
    static const QString FLOOR_05 = "://textures/tiles/01_floor/t_floor05_128_128.png";

    static const QString PIT_01 = "://textures/tiles/02_pits/t_pit01_128_128.png";
    static const QString PIT_02 = "://textures/tiles/02_pits/t_pit02_128_128.png";
    static const QString PIT_03 = "://textures/tiles/02_pits/t_pit03_128_128.png";
    static const QString PIT_04 = "://textures/tiles/02_pits/t_pit04_128_128.png";
    static const QString PIT_05 = "://textures/tiles/02_pits/t_pit05_128_128.png";

    static const QString PORTAL_01 = "://textures/tiles/03_portals/t_portal01_128_128.png";
    static const QString PORTAL_02 = "://textures/tiles/03_portals/t_portal02_128_128.png";
    static const QString PORTAL_03 = "://textures/tiles/03_portals/t_portal03_128_128.png";

    static const QString DOOR_CLOSED = "://textures/tiles/04_doors/t_door_closed_128_128.png";
    static const QString DOOR_OPEN = "://textures/tiles/04_doors/t_door_open_128_128.png";

    static const QString RAMP_UP = "://textures/tiles/05_ramp/t_ramp_up_128_128.png";
    static const QString RAMP_DOWN = "://textures/tiles/05_ramp/t_ramp_down_128_128.png";
    static const QString RAMP_OVERLAY = "://textures/tiles/05_ramp/t_ramp_overlay_128_128.png";

    static const QString WALL_01 = "://textures/tiles/06_wall/t_wall01_128_128.png";
    static const QString WALL_02 = "://textures/tiles/06_wall/t_wall02_128_128.png";
    static const QString WALL_03 = "://textures/tiles/06_wall/t_wall03_128_128.png";
    static const QString WALL_04 = "://textures/tiles/06_wall/t_wall04_128_128.png";

    static const QString SWITCH_INACTIVE = "://textures/tiles/07_switch/t_switch_inactive_128_128.png";
    static const QString SWITCH_ACTIVE = "://textures/tiles/07_switch/t_switch_active_128_128.png";

    static const QString LEVEL_CHANGER = "://textures/tiles/08_levelchanger/t_levelchanger_128_128.png";

    static const QString CHEST = "://textures/tiles/09_chest/t_chest_128_128.png";
}

enum CharacterTexturesIndex {
    BACK_START = 0,
    BACK_01 = 0,
    BACK_02 = 1,
    BACK_03 = 2,
    BACK_04 = 3,

    FRONT_START = 4,
    FRONT_01 = 4,
    FRONT_02 = 5,
    FRONT_03 = 6,
    FRONT_04 = 7,

    LEFT_START = 8,
    LEFT_01 = 8,
    LEFT_02 = 9,
    LEFT_03 = 10,
    LEFT_04 = 11,

    RIGHT_START = 12,
    RIGHT_01 = 12,
    RIGHT_02 = 13,
    RIGHT_03 = 14,
    RIGHT_04 = 15,

    STEP_NUMBER = 4,
    SPRITE_COUNT = 16,
    TOTAL_SPRITE_COUNT = 80
};

enum CharacterTypes {
    CHARACTER_01 = 0,
    CHARACTER_02 = 1,
    CHARACTER_03 = 2,
    CHARACTER_04 = 3,

    CHARACTER_COUNT = 4
};

namespace MainCharacterTextures {
    static const QString BACK_01_03 = "://textures/characters/darthvader/t_darthvader_back01_03_64_64.png";
    static const QString BACK_02 = "://textures/characters/darthvader/t_darthvader_back02_64_64.png";
    static const QString BACK_04 = "://textures/characters/darthvader/t_darthvader_back04_64_64.png";

    static const QString FRONT_01_03 = "://textures/characters/darthvader/t_darthvader_front01_03_64_64.png";
    static const QString FRONT_02 = "://textures/characters/darthvader/t_darthvader_front02_64_64.png";
    static const QString FRONT_04 = "://textures/characters/darthvader/t_darthvader_front04_64_64.png";

    static const QString LEFT_01_03 = "://textures/characters/darthvader/t_darthvader_left01_03_64_64.png";
    static const QString LEFT_02 = "://textures/characters/darthvader/t_darthvader_left02_64_64.png";
    static const QString LEFT_04 = "://textures/characters/darthvader/t_darthvader_left04_64_64.png";

    static const QString RIGHT_01_03 = "://textures/characters/darthvader/t_darthvader_right01_03_64_64.png";
    static const QString RIGHT_02 = "://textures/characters/darthvader/t_darthvader_right02_64_64.png";
    static const QString RIGHT_04 = "://textures/characters/darthvader/t_darthvader_right04_64_64.png";
}

namespace Character1Textures {
    static const QString BACK_01_03 = "://textures/characters/character01/t_character01_back01_03_64_64.png";
    static const QString BACK_02 = "://textures/characters/character01/t_character01_back02_64_64.png";
    static const QString BACK_04 = "://textures/characters/character01/t_character01_back04_64_64.png";

    static const QString FRONT_01_03 = "://textures/characters/character01/t_character01_front01_03_64_64.png";
    static const QString FRONT_02 = "://textures/characters/character01/t_character01_front02_64_64.png";
    static const QString FRONT_04 = "://textures/characters/character01/t_character01_front04_64_64.png";

    static const QString LEFT_01_03 = "://textures/characters/character01/t_character01_left01_03_64_64.png";
    static const QString LEFT_02 = "://textures/characters/character01/t_character01_left02_64_64.png";
    static const QString LEFT_04 = "://textures/characters/character01/t_character01_left04_64_64.png";

    static const QString RIGHT_01_03 = "://textures/characters/character01/t_character01_right01_03_64_64.png";
    static const QString RIGHT_02 = "://textures/characters/character01/t_character01_right02_64_64.png";
    static const QString RIGHT_04 = "://textures/characters/character01/t_character01_right04_64_64.png";
}

namespace Character2Textures {
    static const QString BACK_01_03 = "://textures/characters/character02/t_character02_back01_03_64_64.png";
    static const QString BACK_02 = "://textures/characters/character02/t_character02_back02_64_64.png";
    static const QString BACK_04 = "://textures/characters/character02/t_character02_back04_64_64.png";

    static const QString FRONT_01_03 = "://textures/characters/character02/t_character02_front01_03_64_64.png";
    static const QString FRONT_02 = "://textures/characters/character02/t_character02_front02_64_64.png";
    static const QString FRONT_04 = "://textures/characters/character02/t_character02_front04_64_64.png";

    static const QString LEFT_01_03 = "://textures/characters/character02/t_character02_left01_03_64_64.png";
    static const QString LEFT_02 = "://textures/characters/character02/t_character02_left02_64_64.png";
    static const QString LEFT_04 = "://textures/characters/character02/t_character02_left04_64_64.png";

    static const QString RIGHT_01_03 = "://textures/characters/character02/t_character02_right01_03_64_64.png";
    static const QString RIGHT_02 = "://textures/characters/character02/t_character02_right02_64_64.png";
    static const QString RIGHT_04 = "://textures/characters/character02/t_character02_right04_64_64.png";
}

namespace Character3Textures {
    static const QString BACK_01_03 = "://textures/characters/character03/t_character03_back01_03_64_64.png";
    static const QString BACK_02 = "://textures/characters/character03/t_character03_back02_64_64.png";
    static const QString BACK_04 = "://textures/characters/character03/t_character03_back04_64_64.png";

    static const QString FRONT_01_03 = "://textures/characters/character03/t_character03_front01_03_64_64.png";
    static const QString FRONT_02 = "://textures/characters/character03/t_character03_front02_64_64.png";
    static const QString FRONT_04 = "://textures/characters/character03/t_character03_front04_64_64.png";

    static const QString LEFT_01_03 = "://textures/characters/character03/t_character03_left01_03_64_64.png";
    static const QString LEFT_02 = "://textures/characters/character03/t_character03_left02_64_64.png";
    static const QString LEFT_04 = "://textures/characters/character03/t_character03_left04_64_64.png";

    static const QString RIGHT_01_03 = "://textures/characters/character03/t_character03_right01_03_64_64.png";
    static const QString RIGHT_02 = "://textures/characters/character03/t_character03_right02_64_64.png";
    static const QString RIGHT_04 = "://textures/characters/character03/t_character03_right04_64_64.png";
}

namespace Character4Textures {
    static const QString BACK_01_03 = "://textures/characters/character04/t_character04_back01_03_64_64.png";
    static const QString BACK_02 = "://textures/characters/character04/t_character04_back02_64_64.png";
    static const QString BACK_04 = "://textures/characters/character04/t_character04_back04_64_64.png";

    static const QString FRONT_01_03 = "://textures/characters/character04/t_character04_front01_03_64_64.png";
    static const QString FRONT_02 = "://textures/characters/character04/t_character04_front02_64_64.png";
    static const QString FRONT_04 = "://textures/characters/character04/t_character04_front04_64_64.png";

    static const QString LEFT_01_03 = "://textures/characters/character04/t_character04_left01_03_64_64.png";
    static const QString LEFT_02 = "://textures/characters/character04/t_character04_left02_64_64.png";
    static const QString LEFT_04 = "://textures/characters/character04/t_character04_left04_64_64.png";

    static const QString RIGHT_01_03 = "://textures/characters/character04/t_character04_right01_03_64_64.png";
    static const QString RIGHT_02 = "://textures/characters/character04/t_character04_right02_64_64.png";
    static const QString RIGHT_04 = "://textures/characters/character04/t_character04_right04_64_64.png";
}

namespace QtStyleSheet {
    static const QString TRANSPARENT = "background-color: rgba(0,0,0,0%)";
    static const QString BLACK = "background-color: rgba(0,0,0,100%)";
    static const QString NOBORDER = "QGroupBox {  border: 0px;}";
}

#endif // TEXTURES_H
