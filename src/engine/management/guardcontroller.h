#ifndef GUARDCONTROLLER_H
#define GUARDCONTROLLER_H

#include "controller.h"

#include <string>

class GuardController : public Controller {
public:
    GuardController(const std::string& movementString, std::size_t currentIndex);
    GuardController(const GuardController& other);
    ~GuardController() = default;

    char move() override;

    const std::string& getPath() const;
    size_t getIndex() const;

private:
    std::string movementString;
    std::size_t currentIndex;
};

#endif // GUARDCONTROLLER_H
