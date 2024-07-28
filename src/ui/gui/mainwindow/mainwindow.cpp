#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../graphicalui.h"
#include "../../../engine/management/level.h"
#include "../../../engine/tile/tile.h"
#include "../../../engine/character/character.h"
#include "../_customstatusbar/statusbar.h"
#include "../startscreen/startscreen.h"

//constructors
MainWindow::MainWindow(GraphicalUi* graphicalUi, std::shared_ptr<Level> currentLevel, QWidget* parent) :
    QMainWindow(parent), hasContent(false), ui(new Ui::MainWindow), graphicalUi(graphicalUi), currentLevel(currentLevel) {
    ui->setupUi(this);

    setupMainWindow();
    setupButtonGridLayout();
}

MainWindow::~MainWindow() {
    delete ui;
    delete levelGridLayout;
}

//setup methods
void MainWindow::setupMainWindow() {
    titleBarPixmap = graphicalUi->titleBarTextures.at(TitleBarTexturesIndex::GAMETITLEBAR_TEXTURE);
    mainWindowBackground = graphicalUi->mainWindowTextures.at(MainWindowTexturesIndex::MAINWINDOW_BACKGROUND_TEXTURE);
    mainWindowOverlay = graphicalUi->mainWindowTextures.at(MainWindowTexturesIndex::MAINWINDOW_OVERLAY_TEXTURE);


    setWindowTitle(TitleBarLabels::MAINWINDOW_LABEL);
    setWindowIcon(*(titleBarPixmap.get()));

    setFixedSize(QSize(mainWindowOverlay->width(), mainWindowOverlay->height()));

    backgroundLabel = new QLabel(this);
    backgroundLabel->setStyleSheet(QtStyleSheet::BLACK);
    backgroundLabel->setPixmap(*(mainWindowBackground.get()));

    ui->centralGridLayout->addWidget(backgroundLabel, 0, 0, UiDimensions::MAINWINDOW_ROWS, UiDimensions::MAINWINDOW_COLUMNS);

    overlayLabel = new QLabel(this);

    overlayLabel->setStyleSheet(QtStyleSheet::TRANSPARENT);
    overlayLabel->setPixmap(*(mainWindowOverlay.get()));

    ui->centralGridLayout->addWidget(overlayLabel, 0, 0, UiDimensions::MAINWINDOW_ROWS, UiDimensions::MAINWINDOW_COLUMNS);

    connect(this, &MainWindow::sendMovementDirection, this, &MainWindow::moveSlot);
}

void MainWindow::setupButtonGridLayout() {
    buttonGroupBox = new QGroupBox(this);

    buttonGroupBox->setFixedSize(QSize(UiDimensions::CONTROLBUTTON_AREA_SIZE, UiDimensions::CONTROLBUTTON_AREA_SIZE));

    buttonGroupBox->setStyleSheet(QtStyleSheet::NOBORDER);

    buttonGridLayout = new QGridLayout(buttonGroupBox);

    ui->centralGridLayout->addWidget(buttonGroupBox, UiDimensions::CONTROLBUTTON_GROUP_POSITION_ROW, UiDimensions::CONTROLBUTTON_GROUP_POSITION_COLUMN);


    int activeImageOffset = 9;

    for(size_t i = 0; i < 9; ++i) {
        controlButtons.at(i) = std::make_shared<ControlPushButton>(graphicalUi->controlButtonTextures.at(i), graphicalUi->controlButtonTextures.at(i + activeImageOffset), UserInput::TRIGGER_ARRAY[i], this);
        connect(controlButtons.at(i).get(), &ControlPushButton::sendMovementDirection, this, &MainWindow::moveSlot);
    }

    int counter = 0;
    for (size_t i = 0; i < 3 ; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            QPushButton* castedButton = dynamic_cast<QPushButton*>(controlButtons.at(counter).get());
            if (castedButton) {
                buttonGridLayout->addWidget(castedButton, i, j);
            }
            ++counter;
        }
    }
}

//gameplay
void MainWindow::drawLevel(std::shared_ptr<Level> currentLevel) {
    if (this->currentLevel.get() != currentLevel.get()) {   //check if level is loaded
        changeLevel(currentLevel);  //load newLevel
    }

    auto& tileTextures = graphicalUi->tileTextures;

    for(int i = 0; i < levelDimensions.row; ++i) {
        for(int j = 0; j < levelDimensions.column; ++j) {
            int textureIndex = tileVector.at(i).at(j).first->getTextureIndex();
            tileVector.at(i).at(j).second->setPixmap(*(tileTextures.at(textureIndex).get()));
        }
    }

    auto& characterTextures = graphicalUi->characterTextures;

    for(size_t i = 0; i < characterVector.size(); ++i) {
        if(characterVector.at(i).first->getAliveState()) {
            auto currentTile = characterVector.at(i).first->getRowColumn();

            auto destinationLabel = tileVector.at(currentTile.row).at(currentTile.column).second;

            characterVector.at(i).second.characterLabel->setPixmap(*(characterTextures.at(characterVector.at(i).first->getTextureIndex()).get()));
            characterVector.at(i).second.characterLabel->setParent(destinationLabel);
            characterVector.at(i).second.characterLabel->show();

            if (dynamic_cast<Ramp*>(tileVector.at(currentTile.row).at(currentTile.column).first)) {
                characterVector.at(i).second.rampLabel->show();
            } else {
                if (characterVector.at(i).second.rampLabel->isVisible()) {
                    characterVector.at(i).second.rampLabel->hide();
                }
            }
            characterVector.at(i).second.lifeBar->setValue(characterVector.at(i).first->getHitpoints());;
        } else {
            characterVector.at(i).second.lifeBar->hide();
            characterVector.at(i).second.rampLabel->hide();
            characterVector.at(i).second.characterLabel->hide();
        }
    }

    overlayLabel->raise();
    buttonGroupBox->raise();
}

void MainWindow::changeLevel(std::shared_ptr<Level> newLevel) {
    std::cout << "[ENGINE]: new level initialized" << std::endl;

    if(hasContent) {
        QLayoutItem* item;
        while ((item = levelGridLayout->takeAt(0))) {
            QWidget* widget = item->widget();
            if(widget) {
                widget->deleteLater();
            }
            delete item;
        }

        for(auto& character : characterVector) {
            delete character.second.lifeBar;
            delete character.second.rampLabel;
            delete character.second.characterLabel;
        }
    }

    currentLevel = newLevel;

    levelDimensions = currentLevel->getRowColumns();

    levelGridLayout = new QGridLayout();

    ui->centralGridLayout->addLayout(levelGridLayout, 1 ,4);

    levelGridLayout->setSpacing(0);

    tileVector.resize(levelDimensions.row);
    for(auto& subvector : tileVector) {
        subvector.resize(levelDimensions.column);
    }

    auto otherTileVector = currentLevel->getTileVector();

    calculateTileSize();

    for(int i = 0; i < levelDimensions.row; ++i) {
        for(int j = 0; j < levelDimensions.column; ++j) {

            //crash when resize
            auto& element = tileVector.at(i).at(j);
            element.first = otherTileVector.at(i).at(j); //set Tile*

            element.second = new QLabel(this);
            element.second->setFixedSize(tileSize, tileSize);
            element.second->setScaledContents(true);

            levelGridLayout->addWidget(element.second, i, j);
        }
    }

    //adding characters
    auto otherCharacterVector = currentLevel->getCharacterVector();
    characterVector.resize(otherCharacterVector.size());

    for(size_t i = 0; i < characterVector.size(); ++i) {
        auto& element =  characterVector.at(i);
        element.first = otherCharacterVector.at(i);

        element.second.characterLabel = new QLabel(this);
        element.second.characterLabel->setFixedSize(tileSize, tileSize);
        element.second.characterLabel->setScaledContents(true);

        element.second.rampLabel = new QLabel(element.second.characterLabel);
        element.second.rampLabel->setFixedSize(tileSize, tileSize);
        element.second.rampLabel->setScaledContents(true);
        element.second.rampLabel->setPixmap(*(graphicalUi->tileTextures.at(TileTexturesIndex::RAMP_OVERLAY).get()));

        element.second.rampLabel->setStyleSheet(QtStyleSheet::TRANSPARENT);
        element.second.rampLabel->hide();

        element.second.lifeBar = new StatusBar(tileSize, element.first->getMaxHitpoints(), element.second.characterLabel);
    }

    hasContent = true;
}

void MainWindow::createOverlay(bool winning) {
    QLabel* overlay = new QLabel(this);

    ui->centralGridLayout->addWidget(overlay, 0, 0, UiDimensions::MAINWINDOW_ROWS, UiDimensions::MAINWINDOW_COLUMNS);

    overlay->setStyleSheet(QtStyleSheet::TRANSPARENT);
    overlay->setScaledContents(true);

    if (winning) {
        overlay->setPixmap(*(graphicalUi->overlayTextures.at(OverlayTexturesIndex::WINNING_OVERLAY).get()));
    } else {
        overlay->setPixmap(*(graphicalUi->overlayTextures.at(OverlayTexturesIndex::LOOSING_OVERLAY).get()));
    }
}

void MainWindow::calculateTileSize() {
    if((levelDimensions.row * float(UiDimensions::LEVEL_MAXWIDTH/float(UiDimensions::LEVEL_MAXHEIGHT))) > levelDimensions.column) {
        tileSize = UiDimensions::LEVEL_MAXHEIGHT/levelDimensions.row;
    } else {
        tileSize = UiDimensions::LEVEL_MAXWIDTH/levelDimensions.column;
    }
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    char movementDirection = event->text().at(0).toLatin1();
    emit sendMovementDirection(movementDirection);
}

void MainWindow::closeEvent(QCloseEvent* event) {
    emit sendMovementDirection(UserInput::TRIGGER_EXIT);
}

//slots
void MainWindow::moveSlot(char movementDirection) {
    graphicalUi->setLastInput(movementDirection);
}
