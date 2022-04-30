#pragma once

#include "headquarter/Spawner.h"

class BlueSpawner : public Spawner {
 public:
  auto Spawn(const SpawnConfiguration& configuration)
      -> std::shared_ptr<Character> override;

 private:
  int CalcRequeiredHealth(int sequence);

  int spawned_count = 0;
};