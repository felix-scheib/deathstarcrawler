//------------------------------------------------------------------------------
//-----dialog as StartScreen----------------------------------------------------
//------------------------------------------------------------------------------

#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "../../../../_config/guisettings.h"
#include "../../../../_config/textures.h"
#include "../_custompushbuttons/hoverpushbutton.h"
#include "../mainwindow/mainwindow.h"

#include <QDialog>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QEvent>

#include <memory>

class GraphicalUi;
class Level;

namespace Ui { class StartScreen; }

class StartScreen : public QDialog {
    Q_OBJECT
public:
    //constructors
    explicit StartScreen(GraphicalUi* graphicalUi, QWidget* parent = nullptr);
    ~StartScreen();

private:
    Ui::StartScreen* ui;

    QPushButton* startButton;   //start button
    QPushButton* continueButton;   //start button
    QLabel *backgroundLabel;    //label for QPixmap Background

    GraphicalUi* graphicalUi;

    std::shared_ptr<QPixmap> backgroundPixmap;  //Pixmap for Background Texture
    std::shared_ptr<QPixmap> titleBarPixmap;  //Pixmap for Icon Texture

    void setupDialog();
    void setupButtons();

    void reject() override;
private slots:
    void slotSwitchWindow() const;
    void slotReloadGame() const;

signals:
    void sendExitTrigger(char movementDirection);
};

#endif // STARTSCREEN_H
