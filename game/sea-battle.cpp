#include "game/sea-battle.h"

#include <utility>

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}

sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1,
                           std::shared_ptr<player_interface_t> player2, field_t field2)
    : player1(std::move(player1)), field1(std::move(field1)), player2(std::move(player2)), field2(std::move(field2)) {}

void sea_battle_t::play() {
  while (true) {
    // Pointers to players and fields are generated based on current turn
    std::shared_ptr<player_interface_t> *active_player_ptr;
    std::shared_ptr<player_interface_t> *enemy_player_ptr;
    field_t *active_field_ptr;
    field_t *enemy_field_ptr;
    if (turn == FIRST_PLAYER) {
      active_player_ptr = &player1;
      enemy_player_ptr = &player2;
      active_field_ptr = &field1;
      enemy_field_ptr = &field2;
    } else {
      active_player_ptr = &player2;
      enemy_player_ptr = &player1;
      active_field_ptr = &field2;
      enemy_field_ptr = &field1;
    }
    // Get move from active player
    std::pair<int, int> pos = (*active_player_ptr)->make_move(*active_field_ptr, hide_ship_cells(*enemy_field_ptr));
    // Check if move is invalid
    if (!field_t::is_cell_valid(pos.first, pos.second)) {
      (*active_player_ptr)->on_incorrect_move(pos.first, pos.second);
      continue;
    }
    // Check if move is duplicate
    if ((*enemy_field_ptr)[pos.first][pos.second] == field_t::HIT_CELL ||
        (*enemy_field_ptr)[pos.first][pos.second] == field_t::MISS_CELL) {
      (*active_player_ptr)->on_duplicate_move(pos.first, pos.second);
      continue;
    }
    // Check if move is a miss
    if ((*enemy_field_ptr)[pos.first][pos.second] == field_t::EMPTY_CELL) {
      (*active_player_ptr)->on_miss(pos.first, pos.second);
      (*enemy_field_ptr)[pos.first][pos.second] = field_t::MISS_CELL;
      turn = change_turn(turn);
      continue;
    }
    // Check if move is a hit or kill
    (*enemy_field_ptr)[pos.first][pos.second] = field_t::HIT_CELL;
    bool kill = true; // Flag to indicate that no ships cells were found
    for (auto dir : field_t::DIRECTIONS) {
      // Check cross around pos for ship cells
      int move_x = 0;
      int move_y = 0;
      while (true) {
        move_x += dir.first;
        move_y += dir.second;
        // Check if cell is inside field
        if (!field_t::is_cell_valid(pos.first + move_x, pos.second + move_y)) {
          break;
        }
        // Check if cell is not ship or hit
        if ((*enemy_field_ptr)[pos.first + move_x][pos.second + move_y] == field_t::EMPTY_CELL ||
            (*enemy_field_ptr)[pos.first + move_x][pos.second + move_y] == field_t::MISS_CELL) {
          break;
        }
        // Check if cell is a ship
        if ((*enemy_field_ptr)[pos.first + move_x][pos.second + move_y] == field_t::SHIP_CELL) {
          kill = false;
          break;
        }
      }
      if (!kill) {
        break;
      }
    }
    // Hit
    if (!kill) {
      (*active_player_ptr)->on_hit(pos.first, pos.second);
      continue;
    }
    // Kill
    (*active_player_ptr)->on_kill(pos.first, pos.second);
    // Check win
    bool win = true;
    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
      for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
        // Check if cell is ship cell
        if ((*enemy_field_ptr)[i][j] == field_t::SHIP_CELL) {
          win = false;
          break;
        }
      }
      if (!win) {
        break;
      }
    }
    // Win
    if (win) {
      (*active_player_ptr)->on_win();
      (*enemy_player_ptr)->on_lose();
      break;
    }
  }
}

field_t sea_battle_t::hide_ship_cells(field_t field) {
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
      if (field[i][j] == field_t::SHIP_CELL) {
        field[i][j] = field_t::EMPTY_CELL;
      }
    }
  }
  return field;
}
