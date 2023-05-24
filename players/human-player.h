#pragma once

#include <iostream>

#include "players/player-interface.h"

class human_player_t : public player_interface_t {
public:
  human_player_t(std::istream &input_stream, std::ostream &output_stream)
      : input_stream(input_stream), output_stream(output_stream) {}

  // override methods from parent class
  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;

  void on_incorrect_move(int x, int y) override;

  void on_duplicate_move(int x, int y) override;

  void on_miss(int x, int y) override;

  void on_hit(int x, int y) override;

  void on_kill(int x, int y) override;

  void on_win() override;

  void on_lose() override;

private:
  std::istream &input_stream;
  std::ostream &output_stream;

  // convert int position to string
  static std::string get_string_pos(int x, int y);

  // convert string position to int
  static std::pair<int, int> get_int_pos(const std::string &s);
};
