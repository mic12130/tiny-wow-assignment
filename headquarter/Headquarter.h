#pragma once

#include <memory>

#include "headquarter/Spawner.h"

class Headquarter {
 public:
  Headquarter(std::unique_ptr<Spawner> spawner, std::string name,
              int init_health, int location);

  // If health is not enough to produce a character,
  // nullptr will be returned
  auto Spawn() -> std::shared_ptr<Character>;

  int get_total_health() const;
  int get_location() const;
  std::string get_name() const;

 private:
  std::unique_ptr<Spawner> spawner;
  std::string name;
  int total_health;
  int location;
};