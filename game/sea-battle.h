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
  // two players
  std::vector<std::shared_ptr<player_interface_t>> players;

  // two fields
  std::vector<field_t> fields;

  // current turn
  turn_t current = FIRST_PLAYER;

  // replace all ships cells with empty cells
  static field_t hide_ships(field_t field);

  // try to find ship cell attached to given cell
  bool find_attached_ship_cell(field_t &field, int x, int y, int ignore_x = -1, int ignore_y = -1);

  // try to find ship anywhere on the field
  static bool find_any_ship_cell(field_t &field);
};
