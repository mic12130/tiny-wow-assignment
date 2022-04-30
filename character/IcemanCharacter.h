#pragma once

#include "character/Character.h"

class IcemanCharacter : public Character {
 public:
  IcemanCharacter(std::string name, int id, int location);
  void Move(bool is_east) override;
};