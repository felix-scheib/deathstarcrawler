#ifndef STATIONARYCONTROLLER_H
#define STATIONARYCONTROLLER_H

#include "controller.h"
#include "../../../_config/settings.h"

class StationaryController : public Controller {
public:
    StationaryController() = default;
    ~StationaryController() = default;

    char move() override;
};

#endif // STATIONARYCONTROLLER_H
