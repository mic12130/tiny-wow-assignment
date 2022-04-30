#include "character/DragonCharacter.h"

#include "Configuration.h"
#include "message/Messenger.h"
#include "weapon/WeaponFactory.h"

DragonCharacter::DragonCharacter(std::string name, int id, int location) {
  this->name = name;
  this->id = id;
  this->location = location;
  health = Configuration::kDragonInitHealth;
  damage = Configuration::kDragonDamage;

  std::vector<Weapon> weapons = {WeaponFactory::Make(id % 3)};
  weapon_manager = std::make_unique<WeaponManager>(weapons);

  Messenger::Send(name + " born");
}

void DragonCharacter::Attack(Character& target, int weapon_index) {
  Character::Attack(target, weapon_index);

  if (!IsDead()) {
    Messenger::Send(name + " yelled in city " + std::to_string(location));
  }
}