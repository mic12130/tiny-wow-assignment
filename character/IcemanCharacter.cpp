#include "character/IcemanCharacter.h"

#include "Configuration.h"
#include "weapon/WeaponFactory.h"
#include "message/Messenger.h"

IcemanCharacter::IcemanCharacter(std::string name, int id, int location) {
  this->name = name;
  this->id = id;
  this->location = location;
  health = Configuration::kIcemanInitHealth;
  damage = Configuration::kIcemanDamage;

  std::vector<Weapon> weapons = {WeaponFactory::Make(id % 3)};
  weapon_manager = std::make_unique<WeaponManager>(weapons);
  
  Messenger::Send(name + " born");
}

void IcemanCharacter::Move(bool is_east) {
  Character::Move(is_east);

  health -= int(health / 10);
}