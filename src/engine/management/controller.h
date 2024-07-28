#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
public:
    //constructors
    Controller();
    virtual ~Controller() = default;

    //move
    virtual char move() = 0;
};

#endif // CONTROLLER_H
