#pragma once
#include <unordered_map>
#include <iostream>
#include <cassert>

#include "players/player-interface.h"

class human_player_t : public player_interface_t {
public:
  human_player_t(std::istream &input_stream, std::ostream &output_stream)
      : input_stream(input_stream), output_stream(output_stream) {
    std::string col = "123456789";
    std::string row = "ABCDEFGHIJ";
    for (int i = 0; i < col.size(); i++) {
      for (int j = 0; j < field_t::FIELD_SIZE; j++){
        std::string temp = std::string(1, col[i])+std::string(1,row[j]);
        indexes_map.emplace(std::make_pair(temp, std::make_pair(i,j)));
      }
    }
    for (int i = 0; i < field_t::FIELD_SIZE; i++){
      std::string temp = "10"+ std::string(1,row[i]);
      indexes_map.emplace(std::make_pair(temp, std::make_pair(9,i)));
    }
  }
  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;
  void on_incorrect_move(int x, int y) override;
  void on_duplicate_move(int x, int y) override;
  void on_miss(int x, int y) override;
  void on_hit(int x, int y) override;
  void on_kill(int x, int y) override;
  void on_win() override;
  void on_lose() override;


private:
  std::unordered_map<std::string, std::pair<int, int>> indexes_map;
  std::istream &input_stream;
  std::ostream &output_stream;

};