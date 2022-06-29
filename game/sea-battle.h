#pragma once

#include <memory>
#include <utility>

#include "game/field.h"
#include "players/player-interface.h"

class sea_battle_t {
public:
  enum turn_t { FIRST_PLAYER = 0, SECOND_PLAYER = 1 };

  sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1, std::shared_ptr<player_interface_t> player2,
               field_t field2): player1(std::move(player1)), player2(std::move(player2)),
                                field1(field1), field2(field2),point1(0),point2(0) {
                                       for (int i = 0; i<field_t::FIELD_SIZE; i++){
                                         for (auto node1: field1[i]){
                                           if (node1 == field_t::SHIP_CELL){
                                             point2++;
                                           }
                                         }
                                         for (auto node2: field2[i]){
                                           if (node2 == field_t::SHIP_CELL){
                                             point1++;
                                           }
                                         }
                                       }
  };


  ~sea_battle_t() = default;

  void play();

  static turn_t change_turn(turn_t current_turn);
  static std::string get_player_name(turn_t turn);

private:
  bool check_ship(field_t&, int x, int y);
  void erase_inform(field_t&);

  std::shared_ptr<player_interface_t> player1;
  int point1;
  field_t field1;
  std::shared_ptr<player_interface_t> player2;
  int point2;
  field_t field2;

};