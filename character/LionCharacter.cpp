#include "character/LionCharacter.h"

#include "Configuration.h"
#include "message/Messenger.h"
#include "weapon/WeaponFactory.h"

LionCharacter::LionCharacter(std::string name, int id, int loyalty, int location) {
  this->name = name;
  this->id = id;
  this->location = location;
  this->loyalty = loyalty;
  health = Configuration::kLionInitHealth;
  damage = Configuration::kLionDamage;

  std::vector<Weapon> weapons = {WeaponFactory::Make(id % 3)};
  weapon_manager = std::make_unique<WeaponManager>(weapons);

  Messenger::Send(
      name + " born" + "\n" +
      "Its loyalty is " + std::to_string(loyalty));
}

void LionCharacter::Move(bool is_east) {
  Character::Move(is_east);

  loyalty -= Configuration::kLionLoyaltyDelta;
}