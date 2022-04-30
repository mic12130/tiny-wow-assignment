#include "world/World.h"

#include "Configuration.h"
#include "headquarter/BlueSpawner.h"
#include "headquarter/RedSpawner.h"
#include "performer/AttackPerformer.h"
#include "performer/EscapePerformer.h"
#include "performer/MovePerformer.h"
#include "performer/PreAttackPerformer.h"
#include "performer/ReportPerformer.h"
#include "performer/SpawnPerformer.h"

World::World() {
  location_count = Configuration::kCityCount + 2;

  red_hq = std::make_unique<Headquarter>(
      std::make_unique<RedSpawner>(),
      "red headquarter",
      Configuration::kHqInitHealth,
      0);

  blue_hq = std::make_unique<Headquarter>(
      std::make_unique<BlueSpawner>(),
      "blue headquarter",
      Configuration::kHqInitHealth,
      Configuration::kCityCount + 1);

  world_context = std::make_shared<WorldContext>(
      ended_flag, location_count,
      *red_hq, *blue_hq,
      red_characters, blue_characters);

  timed_event_dispatcher.AddHandler(
      std::make_shared<AttackPerformer>(world_context));
  timed_event_dispatcher.AddHandler(
      std::make_shared<EscapePerformer>(world_context));
  timed_event_dispatcher.AddHandler(
      std::make_shared<MovePerformer>(world_context));
  timed_event_dispatcher.AddHandler(
      std::make_shared<PreAttackPerformer>(world_context));
  timed_event_dispatcher.AddHandler(
      std::make_shared<ReportPerformer>(world_context));
  timed_event_dispatcher.AddHandler(
      std::make_shared<SpawnPerformer>(world_context));
}

void World::Run() {
  for (int min = 0; min < Configuration::kTotalMinutes; min++) {
    Messenger::UpdateTime(min);

    timed_event_dispatcher.OnTick(min);

    if (ended_flag) {
      break;
    }
  }
}