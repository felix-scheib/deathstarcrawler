//------------------------------------------------------------------------------
//-----terminal user interface--------------------------------------------------
//------------------------------------------------------------------------------

#include "terminalui.h"
#include "../engine/management/level.h"

//constructors
TerminalUi::TerminalUi() {
}

//gameplay
void TerminalUi::draw(std::shared_ptr<Level> currentLevel) {
    auto tilesVector = currentLevel->getTileVector();
    for(auto& row : tilesVector) {
        for(auto& column : row) {
            std::cout << column->getAppearance();
        }
        std::cout << std::endl;
    }
}

char TerminalUi::move() {
    char input;
    std::cout << "Enter next move: ";
    std::cin >> input;
    if(isValidInput(input)) {
        return input;
    } else {
        return this->move();
    }
}

//private methods
bool TerminalUi::isValidInput(char input) {
    if(UserInput::INPUT_SIGNALS.find(tolower(input)) != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

