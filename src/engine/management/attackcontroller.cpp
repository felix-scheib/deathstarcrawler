#include "attackcontroller.h"

AttackController::AttackController() :
    stepsBeforeBreak(GameSettings::ATTACKING_STEPS) {
    currentStep = rand() % stepsBeforeBreak;
}

AttackController::AttackController(const AttackController& other) :
    stepsBeforeBreak(other.stepsBeforeBreak) {
    currentStep = rand() % stepsBeforeBreak;
}

char AttackController::move() {
    currentStep = ++currentStep % stepsBeforeBreak;
    if(currentStep) {
        return movementDirection;
    } else {
        return UserInput::TRIGGER_CENTER_CENTER;
    }
}

void AttackController::updateDirection (const RowColumn& origin, const RowColumn& destination) {
    RowColumn delta = destination;// origin;
    delta -= origin;

    if(delta == RowColumn(-1, -1)) {
        movementDirection = UserInput::TRIGGER_TOP_LEFT;
    } else if(delta == RowColumn(-1, 0)) {
        movementDirection = UserInput::TRIGGER_TOP_CENTER;
    } else if(delta == RowColumn(-1, 1)) {
        movementDirection = UserInput::TRIGGER_TOP_RIGHT;
    }
    else if(delta == RowColumn(0, -1)) {
        movementDirection = UserInput::TRIGGER_CENTER_LEFT;
    }
    else if(delta == RowColumn(0, 0)) {
        movementDirection = UserInput::TRIGGER_CENTER_CENTER;
    }
    else if(delta == RowColumn(0, 1)) {
        movementDirection = UserInput::TRIGGER_CENTER_RIGHT;
    }
    else if(delta == RowColumn(1, -1)) {
        movementDirection = UserInput::TRIGGER_BOTTOM_LEFT;
    }
    else if(delta == RowColumn(1, 0)) {
        movementDirection = UserInput::TRIGGER_BOTTOM_CENTER;
    }
    else if(delta == RowColumn(1, 1)) {
        movementDirection = UserInput::TRIGGER_BOTTOM_RIGHT;
    }
}
