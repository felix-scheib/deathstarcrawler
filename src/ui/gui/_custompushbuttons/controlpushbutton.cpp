#include "controlpushbutton.h"

ControlPushButton::ControlPushButton(std::shared_ptr<QPixmap> defaultPixmap, std::shared_ptr<QPixmap> hoverPixmap, char movementDirection, QWidget* parent) :
    HoverPushButton(defaultPixmap, hoverPixmap, parent), movementDirection(movementDirection) {
    connect(this, &QPushButton::clicked, this, &ControlPushButton::onClicked);
}

void ControlPushButton::onClicked() {
    emit sendMovementDirection(movementDirection);
}
