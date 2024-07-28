#ifndef CONTROLPUSHBUTTON_H
#define CONTROLPUSHBUTTON_H

#include "hoverpushbutton.h"

class ControlPushButton : public HoverPushButton {
    Q_OBJECT
public:
    ControlPushButton(std::shared_ptr<QPixmap> defaultPixmap, std::shared_ptr<QPixmap> hoverPixmap, char movementDirection, QWidget* parent = nullptr);
    ~ControlPushButton() = default;
private:
    const char movementDirection;
public slots:
    void onClicked();
signals:
    void sendMovementDirection(char movementDirection);
};

#endif // CONTROLPUSHBUTTON_H
