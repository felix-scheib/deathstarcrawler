#include "hoverpushbutton.h"

HoverPushButton::HoverPushButton(std::shared_ptr<QPixmap> defaultPixmap, std::shared_ptr<QPixmap> hoverPixmap, QWidget* parent) :
    QPushButton(parent), defaultPixmap(defaultPixmap), hoverPixmap(hoverPixmap) {
    int buttonWidth = defaultPixmap->width();
    int buttonHeigt = defaultPixmap->height();

    setFixedSize(buttonWidth, buttonHeigt);

    setStyleSheet(QtStyleSheet::TRANSPARENT);

    setIcon(*(defaultPixmap.get()));
    setIconSize(QSize(buttonWidth, buttonHeigt));
}


void HoverPushButton::enterEvent(QEnterEvent* e) {
    setIcon(*(hoverPixmap.get()));
}


void HoverPushButton::leaveEvent(QEvent *event) {
    setIcon(*(defaultPixmap.get()));
}
