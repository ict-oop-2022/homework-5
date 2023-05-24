#include "players/human-player.h"

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl;
  output_stream << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl;
  output_stream << enemy_field << std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;
  std::pair<int, int> move{-1, -1};
  bool first_iteration = true;
  while (!field_t::is_cell_valid(move.first, move.second)) {
    // try to extract valid position
    if (!first_iteration) {
      output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
    } else {
      first_iteration = false;
    }
    std::string s;
    std::getline(input_stream, s);
    move = get_int_pos(s);
  }
  return move;
}

void human_player_t::on_incorrect_move(int x, int y) {}

void human_player_t::on_duplicate_move(int x, int y) {
  output_stream << get_string_pos(x, y) << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  output_stream << get_string_pos(x, y) << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  output_stream << get_string_pos(x, y) << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int x, int y) {
  output_stream << get_string_pos(x, y) << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}

std::string human_player_t::get_string_pos(int x, int y) {
  std::string number_part = std::to_string(x + 1);
  char letter_part = (char)('A' + y);
  return number_part + letter_part;
}

std::pair<int, int> human_player_t::get_int_pos(const std::string &s) {
  if (s.length() < 2) {
    return {-1, -1};
  }
  std::string number_part = s.substr(0, s.length() - 1); // all letters but last
  char letter_part = s[s.length() - 1];                  // last letter
  int x = -1;
  int y = -1;
  // try to convert number part
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    if (number_part == std::to_string(i + 1)) {
      x = i;
    }
  }
  // try to convert letter part
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    if (letter_part == (char)('A' + i)) {
      y = i;
    }
  }
  return {x, y};
}
