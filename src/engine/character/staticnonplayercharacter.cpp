#include "staticnonplayercharacter.h"

StaticNonPlayerCharacter::StaticNonPlayerCharacter(int strength, int stamina, int hitpoints) :
    Character(std::make_shared<StationaryController>(), strength, stamina, hitpoints, CharacterTextures::ENEMY_TEXTURE, nullptr) {
    characterIndex = rand()%CharacterTypes::CHARACTER_COUNT;
    updateTextureIndex();
}

StaticNonPlayerCharacter::StaticNonPlayerCharacter(const StaticNonPlayerCharacter &other) :
    Character(other.controller, other.strength, other.stamina, other.hitpoints, other.texture), characterIndex(other.characterIndex) {
    updateTextureIndex();
}

void StaticNonPlayerCharacter::updateTextureIndex() {
    textureIndex = (characterIndex + 1) * CharacterTexturesIndex::SPRITE_COUNT + CharacterTexturesIndex::FRONT_START;
}

void StaticNonPlayerCharacter::killed() {
    Character::killed();
}
