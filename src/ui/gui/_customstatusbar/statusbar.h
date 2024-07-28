#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QProgressBar>

#include <iostream>


class StatusBar : public QProgressBar{
public:
    StatusBar(int sizeH, int maxValue, QWidget* parent = nullptr);
    void setValue(int value);

private:
    int maxValue;
};

#endif // STATUSBAR_H
