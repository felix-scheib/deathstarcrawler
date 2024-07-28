#include "guardcontroller.h"

GuardController::GuardController(const std::string &movementString, std::size_t currentIndex) :
    movementString(movementString), currentIndex(currentIndex) {
}

GuardController::GuardController(const GuardController& other) :
    movementString(other.movementString), currentIndex(other.currentIndex) {
}

char GuardController::move() {
    if(++currentIndex >= movementString.size()) {
        currentIndex = 0;
    }
    return movementString.at(currentIndex);
}

const std::string &GuardController::getPath() const {
    return movementString;
}

size_t GuardController::getIndex() const {
    return currentIndex;
}
