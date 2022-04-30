#pragma once

#include <memory>

#include "character/Character.h"
#include "headquarter/SpawnConfiguration.h"

class Spawner {
 public:
  virtual ~Spawner() = default;
  virtual auto Spawn(const SpawnConfiguration& configuration)
      -> std::shared_ptr<Character> = 0;
};