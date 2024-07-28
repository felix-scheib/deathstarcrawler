#include "dynamicnonplayercharacter.h"

DynamicNonPlayerCharacter::DynamicNonPlayerCharacter(int strength, int stamina, int hitpoints, const std::string& movementString, std::size_t currentIndex) :
    Character(std::make_shared<GuardController>(movementString, currentIndex), strength, stamina, hitpoints, CharacterTextures::ENEMY_TEXTURE, nullptr) {
    characterIndex = rand()%CharacterTypes::CHARACTER_COUNT;
    textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START;
}

DynamicNonPlayerCharacter::DynamicNonPlayerCharacter(const DynamicNonPlayerCharacter &other) :
    Character(std::make_shared<GuardController>(*(std::dynamic_pointer_cast<GuardController>(other.controller).get())), other.strength, other.stamina, other.hitpoints, other.texture), characterIndex(other.characterIndex) {
    textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START;
}

const std::string &DynamicNonPlayerCharacter::getPath() const {
    GuardController* guardController = dynamic_cast<GuardController*>(controller.get());
    return guardController->getPath();
}

size_t DynamicNonPlayerCharacter::getPathIndex() const {
    GuardController* guardController = dynamic_cast<GuardController*>(controller.get());
    return guardController->getIndex();
}

void DynamicNonPlayerCharacter::updateTextureIndex() {
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

void DynamicNonPlayerCharacter::killed() {
    Character::killed();
}
