#include "attackingnonplayercharacter.h"
#include "../management/level.h"

AttackingNonPlayerCharacter::AttackingNonPlayerCharacter(int strength, int stamina, int hitpoints) :
    Character(std::make_shared<AttackController>(), strength, stamina, hitpoints, CharacterTextures::ENEMY_TEXTURE, nullptr) {
    characterIndex = rand()%CharacterTypes::CHARACTER_COUNT;
    textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START;
}

AttackingNonPlayerCharacter::AttackingNonPlayerCharacter(const AttackingNonPlayerCharacter& other) :
    Character(std::make_shared<AttackController>(), other.strength, other.stamina, other.hitpoints, other.texture), characterIndex(other.characterIndex) {
    textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START;
}

void AttackingNonPlayerCharacter::setDestination(const RowColumn& destination, const RowColumn& second) {
    auto attackController = dynamic_cast<AttackController*>(controller.get());
    attackController->updateDirection(tile->getRowColumn(), destination);
}

void AttackingNonPlayerCharacter::stayOnTile() {
    auto attackController = dynamic_cast<AttackController*>(controller.get());
    attackController->updateDirection(tile->getRowColumn(), tile->getRowColumn());
}

void AttackingNonPlayerCharacter::updateTextureIndex() {
    if (isTopMovement()) {
        textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::BACK_START + stepNumber;
    } else if (isBottomMovement()) {
        textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START + stepNumber;
    } else if (isLeftMovement()) {
        textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::LEFT_START + stepNumber;
    } else if (isRightMovement()) {
        textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::RIGHT_START + stepNumber;
    }
    stepNumber = ++stepNumber%CharacterTexturesIndex::STEP_NUMBER;
}

void AttackingNonPlayerCharacter::killed() {
    Character::killed();
}
