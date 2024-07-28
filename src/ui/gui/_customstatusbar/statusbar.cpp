#include "statusbar.h"

StatusBar::StatusBar(int sizeH, int maxValue, QWidget* parent) :
    QProgressBar(parent), maxValue(maxValue) {
    setFixedSize(sizeH, sizeH/8);
    setTextVisible(false);
    setRange(0, maxValue);
}

void StatusBar::setValue(int value) {
    float percent = float(value)/float(maxValue);

    if(percent < 0.25) {
        setStyleSheet("QProgressBar{"
                      "border: 0px solid transparent;"
                      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));"
                          "}"
                      "QProgressBar::chunk{"
                      "background-color: rgba(255,0,0,255);"
                      "}");
    } else if (percent < 0.5) {
        setStyleSheet("QProgressBar{"
                      "border: 0px solid transparent;"
                      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));"
                          "}"
                      "QProgressBar::chunk{"
                      "background-color: rgba(255,128,0,255);"
                      "}");
    } else if (percent < 0.75) {
        setStyleSheet("QProgressBar{"
                      "border: 0px solid transparent;"
                      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));"
                          "}"
                      "QProgressBar::chunk{"
                      "background-color: rgba(255,255,0,255);"
                      "}");
    } else {
        setStyleSheet("QProgressBar{"
                      "border: 0px solid transparent;"
                      "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));"
                          "}"
                      "QProgressBar::chunk{"
                      "background-color: rgba(0,255,0,255);"
                      "}");
    }
    QProgressBar::setValue(value);
}
