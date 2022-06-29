#pragma once

#include <memory>

#include "game/field.h"
#include "players/player-interface.h"

class sea_battle_t {
public:
  enum turn_t { FIRST_PLAYER = 0, SECOND_PLAYER = 1 };

  sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2,
               field_t field2);

  ~sea_battle_t() = default;

  void play();

  static turn_t change_turn(turn_t current_turn);
  static std::string get_player_name(turn_t turn);

private:
  turn_t turn{FIRST_PLAYER};                   // Current turn
  std::shared_ptr<player_interface_t> player1; // First player
  field_t field1;                              // First field
  std::shared_ptr<player_interface_t> player2; // Second player
  field_t field2;                              // Second field

  static field_t hide_ship_cells(field_t field);
};
