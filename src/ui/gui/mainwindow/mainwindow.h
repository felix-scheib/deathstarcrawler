#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../../../_config/guisettings.h"
#include "../../../../_config/textures.h"
#include "../_custompushbuttons/controlpushbutton.h"
#include "../../../_utilities/rowcolumn.h"

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QGridLayout>
#include <memory>
#include <array>
#include <vector>
#include <QGroupBox>
#include <QPoint>
#include <QKeyEvent>
#include <QProgressBar>
#include <QCloseEvent>
#include <utility>

#include <iostream>

//forward declarations
class GraphicalUi;
class Level;
class Character;
class StatusBar;
class Tile;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    //cunstructors
    explicit MainWindow(GraphicalUi* graphicalUi, std::shared_ptr<Level> currentLevel = nullptr, QWidget* parent = nullptr);
    ~MainWindow();

    //public methods
    void drawLevel(std::shared_ptr<Level> currentLevel);
    void changeLevel(std::shared_ptr<Level> newLevel);

    void createOverlay(bool winning);
private:
    //member variables
    bool hasContent;

    int tileSize;
    RowColumn levelDimensions;

    QGridLayout* levelGridLayout;
    QGridLayout* buttonGridLayout;

    QGroupBox* buttonGroupBox;

    Ui::MainWindow* ui;
    GraphicalUi* graphicalUi;

    QLabel* backgroundLabel;
    QLabel* overlayLabel;

    std::shared_ptr<QPixmap> titleBarPixmap;
    std::shared_ptr<QPixmap> mainWindowBackground;
    std::shared_ptr<QPixmap> mainWindowOverlay;

    std::vector<std::vector<std::pair<Tile*, QLabel*>>> tileVector;

    std::array<std::shared_ptr<ControlPushButton>, 9> controlButtons;

    std::shared_ptr<Level> currentLevel;

    struct characterLabel {
        QLabel* characterLabel;
        QLabel* rampLabel;
        StatusBar* lifeBar;
    };

    std::vector<std::pair<Character*, characterLabel>> characterVector;

    //setup methods
    void setupMainWindow();
    void setupButtonGridLayout();
    void setupOverlay();
    void calculateTileSize();

    void keyPressEvent(QKeyEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
public slots:
    void moveSlot(char movementDirection);

signals:
    void sendMovementDirection(char movementDirection);
};

#endif // MAINWINDOW_H
