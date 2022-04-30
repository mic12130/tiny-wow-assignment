#include "character/NinjaCharacter.h"

#include "Configuration.h"
#include "weapon/WeaponFactory.h"
#include "message/Messenger.h"

NinjaCharacter::NinjaCharacter(std::string name, int id, int location) {
  this->name = name;
  this->id = id;
  this->location = location;
  health = Configuration::kNinjaInitHealth;
  damage = Configuration::kNinjaDamage;

  std::vector<Weapon> weapons = {
      WeaponFactory::Make(id % 3),
      WeaponFactory::Make((id + 1) % 3)};
  weapon_manager = std::make_unique<WeaponManager>(weapons);
  
  Messenger::Send(name + " born");
}

void NinjaCharacter::Attack(Character& target, int weapon_index) {
  if (weapon_manager->count() == 0) {
    return;
  }

  auto& weapon = weapon_manager->get_weapon(weapon_index);
  int previous_health = health;

  Character::Attack(target, weapon_index);

  // Restore source's health if bomb was used
  if (weapon.id == kWeaponIdBomb) {
    health = previous_health;
  }
}
