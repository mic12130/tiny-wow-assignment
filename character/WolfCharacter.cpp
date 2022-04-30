#include "character/WolfCharacter.h"

#include "Configuration.h"
#include "message/Messenger.h"
#include "weapon/Expelliarmus.h"
#include "weapon/WeaponFactory.h"

WolfCharacter::WolfCharacter(std::string name, int id, int location) {
  this->name = name;
  this->id = id;
  this->location = location;
  health = Configuration::kWolfInitHealth;
  damage = Configuration::kWolfDamage;

  // Wolf has no weapon by default
  weapon_manager = std::make_unique<WeaponManager>();

  Messenger::Send(name + " born");
}

void WolfCharacter::PreAttack(Character& target) {
  Character::PreAttack(target);

  while (get_weapon_manager().count() < kMaxWeaponAllowed) {
    int targetWeaponIndex =
        Expelliarmus::GetTargetWeaponIndex(target.get_weapon_manager());

    if (targetWeaponIndex == kWeaponTransferNotAllowed) {
      break;
    }

    Messenger::Send(
        name + " took 1 " +
        target.get_weapon_manager().get_weapon(targetWeaponIndex).Name() +
        " from " + target.name + " in city " + std::to_string(location));

    Expelliarmus::TransferWeapon(
        get_weapon_manager(), target.get_weapon_manager(), targetWeaponIndex);
  }
}