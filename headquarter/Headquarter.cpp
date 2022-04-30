#include "headquarter/Headquarter.h"

Headquarter::Headquarter(
    std::unique_ptr<Spawner> spawner,
    std::string name,
    int init_health,
    int location)
    : spawner(std::move(spawner)),
      name(name),
      total_health(init_health),
      location(location) {
}

auto Headquarter::Spawn() -> std::shared_ptr<Character> {
  SpawnConfiguration config(total_health, location);
  auto character = spawner->Spawn(config);

  if (character != nullptr) {
    total_health -= character->health;
  }

  return character;
}

int Headquarter::get_total_health() const {
  return total_health;
}

int Headquarter::get_location() const {
  return location;
}

std::string Headquarter::get_name() const {
  return name;
}