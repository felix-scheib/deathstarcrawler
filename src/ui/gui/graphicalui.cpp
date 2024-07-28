//------------------------------------------------------------------------------
//-----graphical user interface-------------------------------------------------
//------------------------------------------------------------------------------

#include "graphicalui.h"
#include "../../engine/management/level.h"
#include "../../engine/management/dungeoncrawler.h"

//constructors
GraphicalUi::GraphicalUi(DungeonCrawler* dungeonCrawler) :
    dungeonCrawler(dungeonCrawler) {
    setStartScreenTextures();
    setTitleBarTextures();
    setMainWindowTextures();
    setOverlayTextures();
    setControlButtonTextures();
    setTileTextures();
    setMainCharacterTextures();

    startScreen = std::make_shared<StartScreen>(this);
    mainWindow = std::make_shared<MainWindow>(this);

    startScreen->show();
}

//gameplay
void GraphicalUi::draw(std::shared_ptr<Level> currentLevel) {
    auto startTime = std::chrono::steady_clock::now();
    mainWindow->drawLevel(currentLevel);
    auto endTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = endTime-startTime;
    std::cout << "[ENGINE]: Frame rendered: " << elapsed_seconds.count() << "s" << std::endl;
}

char GraphicalUi::move() {
    while(lastInput == UserInput::NO_INPUT) {
        QTest::qWait(50);
        QCoreApplication::processEvents();
    }

    char returnValue = lastInput;
    if(lastInput != UserInput::TRIGGER_EXIT) {
        lastInput = UserInput::NO_INPUT;
    }

    return returnValue;
}

void GraphicalUi::wait() {
    while(lastInput != UserInput::TRIGGER_EXIT) {
        QTest::qWait(50);
        QCoreApplication::processEvents();
    }
}

void GraphicalUi::showGame(){
    startScreen->hide();
    mainWindow->show();
}

void GraphicalUi::showStartScreen(){
    startScreen->show();
    mainWindow->hide();
}

void GraphicalUi::newGame() {
    dungeonCrawler->newGame();
    showGame();
    dungeonCrawler->play();
}

void GraphicalUi::reloadGame() {
    dungeonCrawler->reloadGame();
    showGame();
    dungeonCrawler->play();
}

void GraphicalUi::setLastInput(char lastInput) {
    this->lastInput = lastInput;
}

MainWindow* GraphicalUi::getMainWindow() {
    return mainWindow.get();
}

void GraphicalUi::showMessage(bool winning) {
    mainWindow->createOverlay(winning);
    while(lastInput != UserInput::TRIGGER_EXIT) {
        QTest::qWait(50);
        QCoreApplication::processEvents();
    }
}

void GraphicalUi::setStartScreenTextures() {
    startScreenTextures.resize(5);

    startScreenTextures.at(StartScreenTexturesIndex::BACKGROUND_TEXTURE) = std::make_shared<QPixmap>(StartScreenTextures::BACKGROUND_TEXTURE);
    startScreenTextures.at(StartScreenTexturesIndex::STARTBUTTON_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(StartScreenTextures::STARTBUTTON_DEFAULT_TEXTURE);
    startScreenTextures.at(StartScreenTexturesIndex::STARTBUTTON_HOVER_TEXTURE) = std::make_shared<QPixmap>(StartScreenTextures::STARTBUTTON_HOVER_TEXTURE);
    startScreenTextures.at(StartScreenTexturesIndex::CONTINUEBUTTON_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(StartScreenTextures::CONTINUEBUTTON_DEFAULT_TEXTURE);
    startScreenTextures.at(StartScreenTexturesIndex::CONTINUEBUTTON_HOVER_TEXTURE) = std::make_shared<QPixmap>(StartScreenTextures::CONTINUEBUTTON_HOVER_TEXTURE);
}

void GraphicalUi::setTitleBarTextures() {
    titleBarTextures.resize(2);

    titleBarTextures.at(TitleBarTexturesIndex::STARTTITLEBAR_TEXTURE) = std::make_shared<QPixmap>(TitleBarTextures::STARTTITLEBAR_TEXTURE);
    titleBarTextures.at(TitleBarTexturesIndex::GAMETITLEBAR_TEXTURE) = std::make_shared<QPixmap>(TitleBarTextures::GAMETITLEBAR_TEXTURE);
}

void GraphicalUi::setMainWindowTextures() {
    mainWindowTextures.resize(2);

    mainWindowTextures.at(MainWindowTexturesIndex::MAINWINDOW_BACKGROUND_TEXTURE) = std::make_shared<QPixmap>(MainWindowTextures::MAINWINDOW_BACKGROUND_TEXTURE);
    mainWindowTextures.at(MainWindowTexturesIndex::MAINWINDOW_OVERLAY_TEXTURE) = std::make_shared<QPixmap>(MainWindowTextures::MAINWINDOW_OVERLAY_TEXTURE);
}

void GraphicalUi::setOverlayTextures() {
    overlayTextures.resize(2);

    overlayTextures.at(OverlayTexturesIndex::WINNING_OVERLAY) = std::make_shared<QPixmap>(OverlayTextures::WINNING_OVERLAY_TEXTURE);
    overlayTextures.at(OverlayTexturesIndex::LOOSING_OVERLAY) = std::make_shared<QPixmap>(OverlayTextures::LOOSING_OVERLAY_TEXTURE);
}

void GraphicalUi::setControlButtonTextures() {
    controlButtonTextures.resize(18);

    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UPLEFT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UPLEFT_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UP_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UP_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UPRIGHT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UPRIGHT_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_LEFT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_LEFT_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_SKIP_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_SKIP_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_RIGHT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_RIGHT_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWNLEFT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWNLEFT_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWN_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWN_DEFAULT_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWNRIGHT_DEFAULT_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWNRIGHT_DEFAULT_TEXTURE);

    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UPLEFT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UPLEFT_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UP_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UP_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_UPRIGHT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_UPRIGHT_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_LEFT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_LEFT_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_SKIP_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_SKIP_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_RIGHT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_RIGHT_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWNLEFT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWNLEFT_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWN_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWN_HOVER_TEXTURE);
    controlButtonTextures.at(ControlButtonTexturesIndex::CONTROLBUTTON_DOWNRIGHT_HOVER_TEXTURE) = std::make_shared<QPixmap>(ControlButtonTextures::CONTROLBUTTON_DOWNRIGHT_HOVER_TEXTURE);
}

void GraphicalUi::setTileTextures() {
    tileTextures.resize(26);

    tileTextures.at(TileTexturesIndex::FLOOR_01) = std::make_shared<QPixmap>(TileTextures::FLOOR_01);
    tileTextures.at(TileTexturesIndex::FLOOR_02) = std::make_shared<QPixmap>(TileTextures::FLOOR_02);
    tileTextures.at(TileTexturesIndex::FLOOR_03) = std::make_shared<QPixmap>(TileTextures::FLOOR_03);
    tileTextures.at(TileTexturesIndex::FLOOR_04) = std::make_shared<QPixmap>(TileTextures::FLOOR_04);
    tileTextures.at(TileTexturesIndex::FLOOR_05) = std::make_shared<QPixmap>(TileTextures::FLOOR_05);

    tileTextures.at(TileTexturesIndex::PIT_01) = std::make_shared<QPixmap>(TileTextures::PIT_01);
    tileTextures.at(TileTexturesIndex::PIT_02) = std::make_shared<QPixmap>(TileTextures::PIT_02);
    tileTextures.at(TileTexturesIndex::PIT_03) = std::make_shared<QPixmap>(TileTextures::PIT_03);
    tileTextures.at(TileTexturesIndex::PIT_04) = std::make_shared<QPixmap>(TileTextures::PIT_04);
    tileTextures.at(TileTexturesIndex::PIT_05) = std::make_shared<QPixmap>(TileTextures::PIT_05);

    tileTextures.at(TileTexturesIndex::PORTAL_01) = std::make_shared<QPixmap>(TileTextures::PORTAL_01);
    tileTextures.at(TileTexturesIndex::PORTAL_02) = std::make_shared<QPixmap>(TileTextures::PORTAL_02);
    tileTextures.at(TileTexturesIndex::PORTAL_03) = std::make_shared<QPixmap>(TileTextures::PORTAL_03);

    tileTextures.at(TileTexturesIndex::DOOR_CLOSED) = std::make_shared<QPixmap>(TileTextures::DOOR_CLOSED);
    tileTextures.at(TileTexturesIndex::DOOR_OPEN) = std::make_shared<QPixmap>(TileTextures::DOOR_OPEN);

    tileTextures.at(TileTexturesIndex::RAMP_UP) = std::make_shared<QPixmap>(TileTextures::RAMP_UP);
    tileTextures.at(TileTexturesIndex::RAMP_DOWN) = std::make_shared<QPixmap>(TileTextures::RAMP_DOWN);
    tileTextures.at(TileTexturesIndex::RAMP_OVERLAY) = std::make_shared<QPixmap>(TileTextures::RAMP_OVERLAY);

    tileTextures.at(TileTexturesIndex::WALL_01) = std::make_shared<QPixmap>(TileTextures::WALL_01);
    tileTextures.at(TileTexturesIndex::WALL_02) = std::make_shared<QPixmap>(TileTextures::WALL_02);
    tileTextures.at(TileTexturesIndex::WALL_03) = std::make_shared<QPixmap>(TileTextures::WALL_03);
    tileTextures.at(TileTexturesIndex::WALL_04) = std::make_shared<QPixmap>(TileTextures::WALL_04);

    tileTextures.at(TileTexturesIndex::SWITCH_INACTIVE) = std::make_shared<QPixmap>(TileTextures::SWITCH_INACTIVE);
    tileTextures.at(TileTexturesIndex::SWITCH_ACTIVE) = std::make_shared<QPixmap>(TileTextures::SWITCH_ACTIVE);

    tileTextures.at(TileTexturesIndex::LEVEL_CHANGER) = std::make_shared<QPixmap>(TileTextures::LEVEL_CHANGER);

    tileTextures.at(TileTexturesIndex::CHEST) = std::make_shared<QPixmap>(TileTextures::CHEST);
}

void GraphicalUi::setMainCharacterTextures() {
    characterTextures.resize(CharacterTexturesIndex::TOTAL_SPRITE_COUNT);

    characterTextures.at(CharacterTexturesIndex::BACK_01) = std::make_shared<QPixmap>(MainCharacterTextures::BACK_01_03);
    characterTextures.at(CharacterTexturesIndex::BACK_02) = std::make_shared<QPixmap>(MainCharacterTextures::BACK_02);
    characterTextures.at(CharacterTexturesIndex::BACK_03) = characterTextures.at(CharacterTexturesIndex::BACK_01);
    characterTextures.at(CharacterTexturesIndex::BACK_04) = std::make_shared<QPixmap>(MainCharacterTextures::BACK_04);

    characterTextures.at(CharacterTexturesIndex::FRONT_01) = std::make_shared<QPixmap>(MainCharacterTextures::FRONT_01_03);
    characterTextures.at(CharacterTexturesIndex::FRONT_02) = std::make_shared<QPixmap>(MainCharacterTextures::FRONT_02);
    characterTextures.at(CharacterTexturesIndex::FRONT_03) = characterTextures.at(CharacterTexturesIndex::FRONT_01);
    characterTextures.at(CharacterTexturesIndex::FRONT_04) = std::make_shared<QPixmap>(MainCharacterTextures::FRONT_04);

    characterTextures.at(CharacterTexturesIndex::LEFT_01) = std::make_shared<QPixmap>(MainCharacterTextures::LEFT_01_03);
    characterTextures.at(CharacterTexturesIndex::LEFT_02) = std::make_shared<QPixmap>(MainCharacterTextures::LEFT_02);
    characterTextures.at(CharacterTexturesIndex::LEFT_03) = characterTextures.at(CharacterTexturesIndex::LEFT_01);
    characterTextures.at(CharacterTexturesIndex::LEFT_04) = std::make_shared<QPixmap>(MainCharacterTextures::LEFT_04);

    characterTextures.at(CharacterTexturesIndex::RIGHT_01) = std::make_shared<QPixmap>(MainCharacterTextures::RIGHT_01_03);
    characterTextures.at(CharacterTexturesIndex::RIGHT_02) = std::make_shared<QPixmap>(MainCharacterTextures::RIGHT_02);
    characterTextures.at(CharacterTexturesIndex::RIGHT_03) = characterTextures.at(CharacterTexturesIndex::RIGHT_01);
    characterTextures.at(CharacterTexturesIndex::RIGHT_04) = std::make_shared<QPixmap>(MainCharacterTextures::RIGHT_04);

    int character1 = (CharacterTypes::CHARACTER_01 + 1) * CharacterTexturesIndex::SPRITE_COUNT;

    characterTextures.at(character1 + CharacterTexturesIndex::BACK_01) = std::make_shared<QPixmap>(Character1Textures::BACK_01_03);
    characterTextures.at(character1 + CharacterTexturesIndex::BACK_02) = std::make_shared<QPixmap>(Character1Textures::BACK_02);
    characterTextures.at(character1 + CharacterTexturesIndex::BACK_03) =  characterTextures.at(character1 + CharacterTexturesIndex::BACK_01);
    characterTextures.at(character1 + CharacterTexturesIndex::BACK_04) = std::make_shared<QPixmap>(Character1Textures::BACK_04);

    characterTextures.at(character1 + CharacterTexturesIndex::FRONT_01) = std::make_shared<QPixmap>(Character1Textures::FRONT_01_03);
    characterTextures.at(character1 + CharacterTexturesIndex::FRONT_02) = std::make_shared<QPixmap>(Character1Textures::FRONT_02);
    characterTextures.at(character1 + CharacterTexturesIndex::FRONT_03) = characterTextures.at(character1 + CharacterTexturesIndex::FRONT_01);
    characterTextures.at(character1 + CharacterTexturesIndex::FRONT_04) = std::make_shared<QPixmap>(Character1Textures::FRONT_04);

    characterTextures.at(character1 + CharacterTexturesIndex::LEFT_01) = std::make_shared<QPixmap>(Character1Textures::LEFT_01_03);
    characterTextures.at(character1 + CharacterTexturesIndex::LEFT_02) = std::make_shared<QPixmap>(Character1Textures::LEFT_02);
    characterTextures.at(character1 + CharacterTexturesIndex::LEFT_03) =  characterTextures.at(character1 + CharacterTexturesIndex::LEFT_01);
    characterTextures.at(character1 + CharacterTexturesIndex::LEFT_04) = std::make_shared<QPixmap>(Character1Textures::LEFT_04);

    characterTextures.at(character1 + CharacterTexturesIndex::RIGHT_01) = std::make_shared<QPixmap>(Character1Textures::RIGHT_01_03);
    characterTextures.at(character1 + CharacterTexturesIndex::RIGHT_02) = std::make_shared<QPixmap>(Character1Textures::RIGHT_02);
    characterTextures.at(character1 + CharacterTexturesIndex::RIGHT_03) = characterTextures.at(character1 + CharacterTexturesIndex::RIGHT_01);
    characterTextures.at(character1 + CharacterTexturesIndex::RIGHT_04) = std::make_shared<QPixmap>(Character1Textures::RIGHT_04);

    int character2 = (CharacterTypes::CHARACTER_02 + 1) * CharacterTexturesIndex::SPRITE_COUNT;

    characterTextures.at(character2 + CharacterTexturesIndex::BACK_01) = std::make_shared<QPixmap>(Character2Textures::BACK_01_03);
    characterTextures.at(character2 + CharacterTexturesIndex::BACK_02) = std::make_shared<QPixmap>(Character2Textures::BACK_02);
    characterTextures.at(character2 + CharacterTexturesIndex::BACK_03) = characterTextures.at(character2 + CharacterTexturesIndex::BACK_01);
    characterTextures.at(character2 + CharacterTexturesIndex::BACK_04) = std::make_shared<QPixmap>(Character2Textures::BACK_04);

    characterTextures.at(character2 + CharacterTexturesIndex::FRONT_01) = std::make_shared<QPixmap>(Character2Textures::FRONT_01_03);
    characterTextures.at(character2 + CharacterTexturesIndex::FRONT_02) = std::make_shared<QPixmap>(Character2Textures::FRONT_02);
    characterTextures.at(character2 + CharacterTexturesIndex::FRONT_03) = characterTextures.at(character2 + CharacterTexturesIndex::FRONT_01);
    characterTextures.at(character2 + CharacterTexturesIndex::FRONT_04) = std::make_shared<QPixmap>(Character2Textures::FRONT_04);

    characterTextures.at(character2 + CharacterTexturesIndex::LEFT_01) = std::make_shared<QPixmap>(Character2Textures::LEFT_01_03);
    characterTextures.at(character2 + CharacterTexturesIndex::LEFT_02) = std::make_shared<QPixmap>(Character2Textures::LEFT_02);
    characterTextures.at(character2 + CharacterTexturesIndex::LEFT_03) = characterTextures.at(character2 + CharacterTexturesIndex::LEFT_01);
    characterTextures.at(character2 + CharacterTexturesIndex::LEFT_04) = std::make_shared<QPixmap>(Character2Textures::LEFT_04);

    characterTextures.at(character2 + CharacterTexturesIndex::RIGHT_01) = std::make_shared<QPixmap>(Character2Textures::RIGHT_01_03);
    characterTextures.at(character2 + CharacterTexturesIndex::RIGHT_02) = std::make_shared<QPixmap>(Character2Textures::RIGHT_02);
    characterTextures.at(character2 + CharacterTexturesIndex::RIGHT_03) = characterTextures.at(character2 + CharacterTexturesIndex::RIGHT_01);
    characterTextures.at(character2 + CharacterTexturesIndex::RIGHT_04) = std::make_shared<QPixmap>(Character2Textures::RIGHT_04);

    int character3 = (CharacterTypes::CHARACTER_03 + 1) * CharacterTexturesIndex::SPRITE_COUNT;

    characterTextures.at(character3 + CharacterTexturesIndex::BACK_01) = std::make_shared<QPixmap>(Character3Textures::BACK_01_03);
    characterTextures.at(character3 + CharacterTexturesIndex::BACK_02) = std::make_shared<QPixmap>(Character3Textures::BACK_02);
    characterTextures.at(character3 + CharacterTexturesIndex::BACK_03) = characterTextures.at(character3 + CharacterTexturesIndex::BACK_01);
    characterTextures.at(character3 + CharacterTexturesIndex::BACK_04) = std::make_shared<QPixmap>(Character3Textures::BACK_04);

    characterTextures.at(character3 + CharacterTexturesIndex::FRONT_01) = std::make_shared<QPixmap>(Character3Textures::FRONT_01_03);
    characterTextures.at(character3 + CharacterTexturesIndex::FRONT_02) = std::make_shared<QPixmap>(Character3Textures::FRONT_02);
    characterTextures.at(character3 + CharacterTexturesIndex::FRONT_03) = characterTextures.at(character3 + CharacterTexturesIndex::FRONT_01);
    characterTextures.at(character3 + CharacterTexturesIndex::FRONT_04) = std::make_shared<QPixmap>(Character3Textures::FRONT_04);

    characterTextures.at(character3 + CharacterTexturesIndex::LEFT_01) = std::make_shared<QPixmap>(Character3Textures::LEFT_01_03);
    characterTextures.at(character3 + CharacterTexturesIndex::LEFT_02) = std::make_shared<QPixmap>(Character3Textures::LEFT_02);
    characterTextures.at(character3 + CharacterTexturesIndex::LEFT_03) = characterTextures.at(character3 + CharacterTexturesIndex::LEFT_01);
    characterTextures.at(character3 + CharacterTexturesIndex::LEFT_04) = std::make_shared<QPixmap>(Character3Textures::LEFT_04);

    characterTextures.at(character3 + CharacterTexturesIndex::RIGHT_01) = std::make_shared<QPixmap>(Character3Textures::RIGHT_01_03);
    characterTextures.at(character3 + CharacterTexturesIndex::RIGHT_02) = std::make_shared<QPixmap>(Character3Textures::RIGHT_02);
    characterTextures.at(character3 + CharacterTexturesIndex::RIGHT_03) = characterTextures.at(character3 + CharacterTexturesIndex::RIGHT_01);
    characterTextures.at(character3 + CharacterTexturesIndex::RIGHT_04) = std::make_shared<QPixmap>(Character3Textures::RIGHT_04);

    int character4 = (CharacterTypes::CHARACTER_04 + 1) * CharacterTexturesIndex::SPRITE_COUNT;

    characterTextures.at(character4 + CharacterTexturesIndex::BACK_01) = std::make_shared<QPixmap>(Character4Textures::BACK_01_03);
    characterTextures.at(character4 + CharacterTexturesIndex::BACK_02) = std::make_shared<QPixmap>(Character4Textures::BACK_02);
    characterTextures.at(character4 + CharacterTexturesIndex::BACK_03) = characterTextures.at(character4 + CharacterTexturesIndex::BACK_01);
    characterTextures.at(character4 + CharacterTexturesIndex::BACK_04) = std::make_shared<QPixmap>(Character4Textures::BACK_04);

    characterTextures.at(character4 + CharacterTexturesIndex::FRONT_01) = std::make_shared<QPixmap>(Character4Textures::FRONT_01_03);
    characterTextures.at(character4 + CharacterTexturesIndex::FRONT_02) = std::make_shared<QPixmap>(Character4Textures::FRONT_02);
    characterTextures.at(character4 + CharacterTexturesIndex::FRONT_03) = characterTextures.at(character4 + CharacterTexturesIndex::FRONT_01);
    characterTextures.at(character4 + CharacterTexturesIndex::FRONT_04) = std::make_shared<QPixmap>(Character4Textures::FRONT_04);

    characterTextures.at(character4 + CharacterTexturesIndex::LEFT_01) = std::make_shared<QPixmap>(Character4Textures::LEFT_01_03);
    characterTextures.at(character4 + CharacterTexturesIndex::LEFT_02) = std::make_shared<QPixmap>(Character4Textures::LEFT_02);
    characterTextures.at(character4 + CharacterTexturesIndex::LEFT_03) = characterTextures.at(character4 + CharacterTexturesIndex::LEFT_01);
    characterTextures.at(character4 + CharacterTexturesIndex::LEFT_04) = std::make_shared<QPixmap>(Character4Textures::LEFT_04);

    characterTextures.at(character4 + CharacterTexturesIndex::RIGHT_01) = std::make_shared<QPixmap>(Character4Textures::RIGHT_01_03);
    characterTextures.at(character4 + CharacterTexturesIndex::RIGHT_02) = std::make_shared<QPixmap>(Character4Textures::RIGHT_02);
    characterTextures.at(character4 + CharacterTexturesIndex::RIGHT_03) = characterTextures.at(character4 + CharacterTexturesIndex::RIGHT_01);
    characterTextures.at(character4 + CharacterTexturesIndex::RIGHT_04) = std::make_shared<QPixmap>(Character4Textures::RIGHT_04);

}
