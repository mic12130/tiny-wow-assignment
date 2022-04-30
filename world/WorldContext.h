#pragma once

#include "character/Character.h"
#include "headquarter/Headquarter.h"

class WorldContext {
 public:
  WorldContext(
      bool& ended_flag,
      int location_count,
      Headquarter& red_hq,
      Headquarter& blue_hq,
      std::vector<std::shared_ptr<Character>>& red_characters,
      std::vector<std::shared_ptr<Character>>& blue_characters)
      : ended_flag(ended_flag),
        location_count(location_count),
        red_hq(red_hq),
        blue_hq(blue_hq),
        red_characters(red_characters),
        blue_characters(blue_characters) {
  }

  void set_ended() {
    ended_flag = true;
  }

  int location_count;
  Headquarter& red_hq;
  Headquarter& blue_hq;
  std::vector<std::shared_ptr<Character>>& red_characters;
  std::vector<std::shared_ptr<Character>>& blue_characters;

 private:
  bool& ended_flag;
};