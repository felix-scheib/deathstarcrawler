//------------------------------------------------------------------------------
//-----dialog as StartScreen----------------------------------------------------
//------------------------------------------------------------------------------

#include "startscreen.h"
#include "ui_startscreen.h"
#include "../graphicalui.h"

StartScreen::StartScreen(GraphicalUi* graphicalUi, QWidget *parent) :
    QDialog(parent), ui(new Ui::StartScreen), graphicalUi(graphicalUi) {
    ui->setupUi(this);

    setupDialog();
    setupButtons();

    connect(startButton, &QPushButton::clicked, this, &StartScreen::slotSwitchWindow);
    connect(continueButton, &QPushButton::clicked, this, &StartScreen::slotReloadGame);
}

StartScreen::~StartScreen() {
    delete ui;
}

void StartScreen::setupDialog() {
        backgroundPixmap = graphicalUi->startScreenTextures.at(StartScreenTexturesIndex::BACKGROUND_TEXTURE);
        titleBarPixmap = graphicalUi->titleBarTextures.at(TitleBarTexturesIndex::STARTTITLEBAR_TEXTURE);

        setWindowTitle(TitleBarLabels::STARTSCREEN_LABEL);
        setWindowIcon(*(titleBarPixmap.get()));

        setFixedSize(QSize(backgroundPixmap->width(), backgroundPixmap->height()));

        backgroundLabel = new QLabel(this);

        ui->dialogGridLayout->addWidget(backgroundLabel, 0 , 0, UiDimensions::STARTSCREEN_ROWS, UiDimensions::STARTSCREEN_COLUMNS);

        backgroundLabel->setStyleSheet(QtStyleSheet::BLACK);
        backgroundLabel->setPixmap(*(backgroundPixmap.get()));
}

void StartScreen::setupButtons() {
    auto defaultPixmap = graphicalUi->startScreenTextures.at(StartScreenTexturesIndex::STARTBUTTON_DEFAULT_TEXTURE);
    auto hoverPixmap = graphicalUi->startScreenTextures.at(StartScreenTexturesIndex::STARTBUTTON_HOVER_TEXTURE);

    startButton = new HoverPushButton(defaultPixmap, hoverPixmap, this);
    ui->dialogGridLayout->addWidget(startButton, UiDimensions::STARTBUTTON_ROW, UiDimensions::STARTBUTTON_COLUMN);

    defaultPixmap = graphicalUi->startScreenTextures.at(StartScreenTexturesIndex::CONTINUEBUTTON_DEFAULT_TEXTURE);
    hoverPixmap = graphicalUi->startScreenTextures.at(StartScreenTexturesIndex::CONTINUEBUTTON_HOVER_TEXTURE);

    continueButton = new HoverPushButton(defaultPixmap, hoverPixmap, this);
    ui->dialogGridLayout->addWidget(continueButton, UiDimensions::CONTINUEBUTTON_ROW, UiDimensions::CONTINUEBUTTON_COLUMN);
}

void StartScreen::reject() {
    emit graphicalUi->getMainWindow()->sendMovementDirection(UserInput::TRIGGER_EXIT);
}

void StartScreen::slotSwitchWindow() const {
    graphicalUi->newGame();
}

void StartScreen::slotReloadGame() const {
    graphicalUi->reloadGame();
}
