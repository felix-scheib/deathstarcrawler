#ifndef ATTACKCONTROLLER_H
#define ATTACKCONTROLLER_H

#include "controller.h"
#include "../../_utilities/tilegraph.h"
#include "level.h"

class Character;

class AttackController : public Controller {
public:
    AttackController();
    ~AttackController() = default;
    AttackController(const AttackController& other);

    char move() override;

    void updateDirection(const RowColumn& origin, const RowColumn& destination);
private:
    char movementDirection;

    int stepsBeforeBreak;
    int currentStep;

    RowColumn oldPosition;
};

#endif // ATTACKCONTROLLER_H
