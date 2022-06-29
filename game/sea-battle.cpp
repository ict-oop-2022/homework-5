#include "game/sea-battle.h"

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
  return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
  return turn == FIRST_PLAYER ? "First" : "Second";
}
void sea_battle_t::play() {
  turn_t current_turn = FIRST_PLAYER;
  while (true){
      if (get_player_name(current_turn)=="First"){
        field_t copy_filed = field2;
        erase_inform(copy_filed);
        std::pair<int, int> coord = player1->make_move(field1, copy_filed);
        while (coord.first > 9 || coord.first < 0 || coord.second > 9 || coord.second < 0){
          player1->on_incorrect_move(coord.first,coord.second);
          coord = player1->make_move(field1, copy_filed);
        }
        while (field2[coord.first][coord.second] == field_t::MISS_CELL ||
               field2[coord.first][coord.second] == field_t::HIT_CELL
               ){
            player1->on_duplicate_move(coord.first,coord.second);
            coord = player1->make_move(field1, copy_filed);
        }

        if (field2[coord.first][coord.second] == field_t::EMPTY_CELL){
          field2[coord.first][coord.second] = field_t::MISS_CELL;
          player1->on_miss(coord.first,coord.second);
          current_turn = change_turn(FIRST_PLAYER);
          continue;
        }
        if (field2[coord.first][coord.second] == field_t::SHIP_CELL){
            field2[coord.first][coord.second] = field_t::HIT_CELL;
            point1--;
            if (check_ship(field2, coord.first, coord.second)){
              player1->on_kill(coord.first, coord.second);
            }else{
              player1->on_hit(coord.first, coord.second);
            }
        }
        if (point1 == 0){
          player1->on_win();
          player2->on_lose();
          return;
        }

      }
    if (get_player_name(current_turn)=="Second"){
      field_t copy_filed = field1;
      erase_inform(copy_filed);
      std::pair<int, int> coord = player2->make_move(field2, copy_filed);
      while (coord.first > 9 || coord.first < 0 || coord.second > 9 || coord.second < 0){
        player2->on_incorrect_move(coord.first,coord.second);
        coord = player2->make_move(field1, copy_filed);
      }
      while (field1[coord.first][coord.second] == field_t::MISS_CELL ||
             field1[coord.first][coord.second] == field_t::HIT_CELL
          ){
        player2->on_duplicate_move(coord.first,coord.second);
        coord = player2->make_move(field2, copy_filed);
      }

      if (field1[coord.first][coord.second] == field_t::EMPTY_CELL){
        field1[coord.first][coord.second] = field_t::MISS_CELL;
        player2->on_miss(coord.first,coord.second);
        current_turn = change_turn(SECOND_PLAYER);
        continue;
      }
      if (field1[coord.first][coord.second] == field_t::SHIP_CELL){
        field1[coord.first][coord.second] = field_t::HIT_CELL;
        point2--;
        if (check_ship(field1, coord.first, coord.second)){
          player2->on_kill(coord.first, coord.second);
        }else{
          player2->on_hit(coord.first, coord.second);
        }
      }
      if (point2 == 0){
        player2->on_win();
        player1->on_lose();
        return;
      }

    }
  }
  return;
}

void sea_battle_t::erase_inform(field_t& enemy_field) {
  for (int i = 0 ; i < field_t::FIELD_SIZE; i ++){
    for (int j = 0; j < field_t::FIELD_SIZE;j ++){
      if (enemy_field[i][j]==field_t::SHIP_CELL){
        enemy_field[i][j] = field_t::EMPTY_CELL;
      }
    }
  }
}
bool sea_battle_t::check_ship(field_t& enemy_field, int x, int y) {
    for (std::pair<int,int> node: field_t::DIRECTIONS){
      for (int i = 1; i < field_t::FIELD_SIZE; i++){
        if ((node.first * i + x < 0 ) || (node.second * i + y < 0)){
          break;
        }
      // exit check
      if ((field_t::FIELD_SIZE > node.first * i + x) && (field_t::FIELD_SIZE > node.second * i + y)) {
        if (enemy_field[node.first * i + x][node.second * i + y] == field_t::EMPTY_CELL) {
          break;
        }
        if (enemy_field[node.first * i + x][node.second * i + y] == field_t::MISS_CELL) {
          break;
        }
        if (enemy_field[node.first * i + x][node.second * i + y] == field_t::SHIP_CELL) {
          return false;
        }
      }else{
        break;
      }
    }
  }
  return true;
}