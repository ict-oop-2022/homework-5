#pragma once
#include <iostream>
#include <cassert>

#include "players/player-interface.h"

class human_player_t : public player_interface_t {
public:
  human_player_t(std::istream &input_stream, std::ostream &output_stream)
      : input_stream(input_stream), output_stream(output_stream) {}

  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;

  void on_incorrect_move(int, int) override {
    assert(false);
  }

  void on_duplicate_move(int x, int y) override;

  void on_miss(int x, int y) override;

  void on_hit(int x, int y) override;

  void on_kill(int x, int y) override;

  void on_win() override;

  void on_lose() override;

private:
  std::istream &input_stream;
  std::ostream &output_stream;

  // Convert move from two ints to std::string
  static std::string move_to_string(int i, int j);

  // Convert move from std::string to two ints
  static std::pair<int, int> move_from_string(const std::string& s);
};