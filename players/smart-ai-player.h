#pragma once

#include "players/player-interface.h"
#include "set"
#include <cassert>

class smart_ai_player_t : public player_interface_t {
public:
  smart_ai_player_t(){
    std::pair<int, int> node;
    for (int i = 0; i < field_t::FIELD_SIZE; i ++){
      for (int j = 0; j < field_t::FIELD_SIZE; j ++){
        node = std::make_pair(i,j);
        step_map.emplace(node);
      }
    }
  }
  std::pair<int, int> make_move(const field_t &my_field, const field_t &enemy_field) override;
  void on_incorrect_move(int x, int y) override{
      assert(false);
  };
  void on_duplicate_move(int x, int y) override{
      assert(false);
  };
  void on_miss(int x, int y) override;
  void on_hit(int x, int y) override;
  void on_kill(int x, int y) override;

  void on_win() override{};
  void on_lose() override{};
private:
  void del_edge(std::pair<int, int >, std::pair<int, int>, std::pair<int, int>&);
  void del_node(std::set<std::pair<int, int >>&,std::pair<int, int >, std::pair<int, int>);
  int hit = 0;
  std::pair<int,int> basis = {0,0};
  std::vector<std::pair<int,int>> empty_node;
  std::pair<int, int> start = {0,0};
  std::pair<int,int> freez_poz = {0,0};
  std::set<std::pair<int, int >> step_map;
};