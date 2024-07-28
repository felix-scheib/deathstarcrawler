//------------------------------------------------------------------------------
//-----singleton for MainCharacter----------------------------------------------
//------------------------------------------------------------------------------

#include "maincharacter.h"
#include "../tile/tile.h"
#include "../observer/passive.h"
#include "../tile/children/lootchest.h"
#include "../tile/children/portal.h"
#include "../tile/children/levelchanger.h"

bool MainCharacter::isInstaciated = false;

MainCharacter::MainCharacter(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, const RowColumn& startingPosition) :
        Character(controller, strength, stamina, hitpoints, CharacterTextures::CHARACTER_TEXTURE, nullptr), startingPosition(startingPosition) {
}

void MainCharacter::activate() {
    Active::activate();
}

MainCharacter::~MainCharacter() {
    isInstaciated = false;
}

MainCharacter* MainCharacter::createMainCharacter(std::shared_ptr<Controller> controller, int strength, int stamina, int hitpoints, Passive* passive, const RowColumn& startingPosition) {
    if(isInstaciated) {
        throw std::domain_error("MainCharacter is instanciated");
    }

   MainCharacter* returnCharacter = new MainCharacter(controller, strength, stamina, hitpoints, startingPosition);
   isInstaciated = true;

   returnCharacter->attach(passive);

   return returnCharacter;
}

void MainCharacter::killed() {
    Character::killed();
    activate();
}

void MainCharacter::won() {
    activate();
}
