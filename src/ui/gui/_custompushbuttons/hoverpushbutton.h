#ifndef HOVERPUSHBUTTON_H
#define HOVERPUSHBUTTON_H

#include "../../../../_config/textures.h"

#include <QPushButton>
#include <QEvent>
#include <QPixmap>
#include <memory>


class HoverPushButton : public QPushButton {
public:
    HoverPushButton(std::shared_ptr<QPixmap> defaultPixmap, std::shared_ptr<QPixmap> hoverPixmap, QWidget* parent = nullptr);
    virtual ~HoverPushButton() = default;

protected:
    void enterEvent(QEnterEvent* e) override;
    void leaveEvent(QEvent *event) override;
private:
    std::shared_ptr<QPixmap> defaultPixmap;
    std::shared_ptr<QPixmap> hoverPixmap;


    //void leaveEvent(QEnterEvent* e);
};

#endif // HOVERPUSHBUTTON_H
