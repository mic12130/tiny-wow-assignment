#include "headquarter/RedSpawner.h"

#include "Configuration.h"
#include "character/DragonCharacter.h"
#include "character/IcemanCharacter.h"
#include "character/LionCharacter.h"
#include "character/NinjaCharacter.h"
#include "character/WolfCharacter.h"

auto RedSpawner::Spawn(const SpawnConfiguration& configuration)
    -> std::shared_ptr<Character> {
  int seq = spawned_count % 5;
  int id = spawned_count + 1;
  int required_health = CalcRequeiredHealth(seq);
  int total_health = configuration.total_health;
  int location = configuration.location;
  std::string id_str = std::to_string(id);

  if (required_health > total_health) {
    return nullptr;
  }

  spawned_count++;

  if (seq == 0) {
    return std::make_shared<IcemanCharacter>(
        "red iceman " + id_str,
        id, location);
  } else if (seq == 1) {
    int loyalty = total_health - Configuration::kLionInitHealth;

    return std::make_shared<LionCharacter>(
        "red lion " + id_str,
        id,
        loyalty,
        location);
  } else if (seq == 2) {
    return std::make_shared<WolfCharacter>(
        "red wolf " + id_str,
        id, location);
  } else if (seq == 3) {
    return std::make_shared<NinjaCharacter>(
        "red ninja " + id_str,
        id, location);
  } else if (seq == 4) {
    return std::make_shared<DragonCharacter>(
        "red dragon " + id_str,
        id, location);
  }

  return nullptr;
}

int RedSpawner::CalcRequeiredHealth(int sequence) {
  if (sequence == 0) {
    return Configuration::kIcemanInitHealth;
  } else if (sequence == 1) {
    return Configuration::kLionInitHealth;
  } else if (sequence == 2) {
    return Configuration::kWolfInitHealth;
  } else if (sequence == 3) {
    return Configuration::kNinjaInitHealth;
  } else if (sequence == 4) {
    return Configuration::kDragonInitHealth;
  }

  return 0;
}