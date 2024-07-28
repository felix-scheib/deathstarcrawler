//------------------------------------------------------------------------------
//-----graphical user interface-------------------------------------------------
//------------------------------------------------------------------------------

#ifndef GRAPHICALUI_H
#define GRAPHICALUI_H

#include "../abstractui.h"
#include "../../engine/management/controller.h"
#include "../../../_config/textures.h"
#include "startscreen/startscreen.h"
#include "mainwindow/mainwindow.h"

#include <QPixmap>
#include <QTest>
#include <memory>
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <chrono>

class Level;
class DungeonCrawler;

class GraphicalUi : public AbstractUi {
public:
    //constructors
    explicit GraphicalUi(DungeonCrawler* dungeonCrawler);
    ~GraphicalUi() = default;

    //gameplay
    void draw(std::shared_ptr<Level> currentLevel) override;
    char move() override;
    void wait() override;

    void showGame();
    void showStartScreen();

    void newGame();
    void reloadGame();

    void exitGame();

    void setLastInput(char lastInput);

    void slotReveiveMovementDirection();

    void showMessage(bool winning);

    std::vector<std::shared_ptr<QPixmap>> startScreenTextures;
    std::vector<std::shared_ptr<QPixmap>> titleBarTextures;
    std::vector<std::shared_ptr<QPixmap>> mainWindowTextures;
    std::vector<std::shared_ptr<QPixmap>> overlayTextures;
    std::vector<std::shared_ptr<QPixmap>> controlButtonTextures;
    std::vector<std::shared_ptr<QPixmap>> tileTextures;
    std::vector<std::shared_ptr<QPixmap>> characterTextures;

    MainWindow* getMainWindow();
private:
    char lastInput = UserInput::NO_INPUT;
    std::shared_ptr<StartScreen> startScreen;
    std::shared_ptr<MainWindow> mainWindow;

    DungeonCrawler* dungeonCrawler;

    void setStartScreenTextures();
    void setTitleBarTextures();
    void setMainWindowTextures();
    void setOverlayTextures();
    void setControlButtonTextures();
    void setTileTextures();
    void setMainCharacterTextures();
    void setCharacterTextures();
};

#endif // GRAPHICALUI_H
