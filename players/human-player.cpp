#include "players/human-player.h"

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  output_stream << "Your field:" << std::endl << my_field << std::endl;
  output_stream << "Enemy's field" << std::endl << enemy_field << std::endl;
  // Get move from human
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;
  while (true) {
    std::string s;
    // Read move from input stream
    std::getline(input_stream, s);
    if (move_from_string(s) != std::pair<int, int> {-1, -1}) {
      return move_from_string(s);
    }
    // If string is invalid
    output_stream << "Incorrect move! [Correct example 1A or 10B or 6J]" << std::endl;
  }
}

void human_player_t::on_duplicate_move(int x, int y) {
  output_stream << move_to_string(x, y) << " DUPLICATE! Repeat move!" << std::endl;
}

void human_player_t::on_miss(int x, int y) {
  output_stream << move_to_string(x, y) << " MISS! Enemy's turn!" << std::endl;
}

void human_player_t::on_hit(int x, int y) {
  output_stream << move_to_string(x, y) << " HIT! Your next move!" << std::endl;
}

void human_player_t::on_kill(int x, int y) {
  output_stream << move_to_string(x, y) << " KILL! Your next move!" << std::endl;
}

void human_player_t::on_win() {
  output_stream << "You WIN!" << std::endl;
}

void human_player_t::on_lose() {
  output_stream << "You LOSE!" << std::endl;
}

std::string human_player_t::move_to_string(int i, int j) {
  // Convert first number to string number and second to letter
  return std::to_string(i + 1) + (char)(j + 'A');
}

std::pair<int, int> human_player_t::move_from_string(const std::string& s) {
  // Find suitable string representation
  for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
    for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
      if (move_to_string(i, j) == s) {
        return {i, j};
      }
    }
  }
  return {-1, -1}; // If string is invalid
}
