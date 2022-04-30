#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Configuration.h"
#include "world/World.h"

using namespace std;

int main() {
  cin >> Configuration::kHqInitHealth;
  cin >> Configuration::kCityCount;
  cin >> Configuration::kLionLoyaltyDelta;
  cin >> Configuration::kTotalMinutes;

  cin >> Configuration::kDragonInitHealth;
  cin >> Configuration::kNinjaInitHealth;
  cin >> Configuration::kIcemanInitHealth;
  cin >> Configuration::kLionInitHealth;
  cin >> Configuration::kWolfInitHealth;

  cin >> Configuration::kDragonDamage;
  cin >> Configuration::kNinjaDamage;
  cin >> Configuration::kIcemanDamage;
  cin >> Configuration::kLionDamage;
  cin >> Configuration::kWolfDamage;

  // Configurations must be filled before we can construct the world
  World world;
  world.Run();

  return 0;
}