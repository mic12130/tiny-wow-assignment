#pragma once

struct SpawnConfiguration {
  int total_health;
  int location;

  SpawnConfiguration(int total_health, int location)
      : total_health(total_health), location(location) {}
};