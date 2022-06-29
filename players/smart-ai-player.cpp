#include "players/smart-ai-player.h"

std::pair<int, int> smart_ai_player_t::make_move(const field_t &my_field, const field_t &enemy_field) {
  step_map.erase(start);
  return start;
}

void smart_ai_player_t::on_miss(int x, int y) {

  if (hit == 1){
    //промах при условии того что мы попали в корабль
    start = empty_node.back();
    empty_node.pop_back();
  }else{
    //обычный промах
    while (step_map.count(start) == 0){
      if (start.first == 9) {
        start.second += 1;
        start.first = 0;
      }else{
        start.first += 1;
      }
    }
  }
}
void smart_ai_player_t::on_hit(int x , int y) {

  hit += 1;
  if (hit == 1){
    freez_poz = start;
    //исключаем повторения при первой пристрелки
    std::pair<int, int> checker = start;
    for(std::pair<int,int> b: field_t::DIRECTIONS) {
      checker.first += b.first;
      checker.second += b.second;
      if (step_map.count(checker) != 0){
        empty_node.push_back(checker);
      }
      checker = start;
    }
    start = empty_node.back();
    empty_node.pop_back();
  }else if (hit == 2){
    basis.first = start.first - freez_poz.first;
    basis.second = start.second - freez_poz.second;
    // удалить для предыдущего шага
    del_node(step_map,freez_poz,basis);
    // удалять для этого шага
    del_node(step_map,start,basis);
    start.first += basis.first;
    start.second += basis.second;
  }else{
    // удалять слева и справа
    start.first += basis.first;
    start.second += basis.second;
    del_node(step_map,start,basis);
  }
}

void smart_ai_player_t::on_kill(int x, int y) {

  if (hit == 0){
    std::pair<int,int> temp = start;
    for(std::pair<int,int> node_1: field_t::DIRECTIONS){
      temp.first += node_1.first;
      temp.second += node_1.second;
      if (step_map.count(temp) > 0){
        step_map.erase(temp);
      }
      temp = start;
    }
  }
  else if (hit == 1){
    basis.first = start.first - freez_poz.first;
    basis.second = start.second - freez_poz.second;
    // удалить для предыдущего шага
    del_node(step_map,freez_poz,basis);
    // удалять для этого шага
    del_node(step_map,start,basis);
    del_edge(start,freez_poz,basis);
  }else{
    del_node(step_map,start,basis);
    del_edge(start,freez_poz,basis);
  }

  hit = 0;
  basis = {0,0};
  empty_node.clear();
  start = {0,0};
  freez_poz =  {0,0};

  while (step_map.count(start) == 0){
    if (start.second > 9){
      return;
    }
    if (start.first == 9) {
      start.second += 1;
      start.first = 0;
    }else{
      start.first += 1;
    }
  }
}



void smart_ai_player_t::del_node(std::set<std::pair<int, int>> & map, std::pair<int, int> poz, std::pair<int, int> b) {
  // удалять справа и слева

  if (b.first == 1){
    std::pair<int,int> block_node = poz;
    block_node.second += 1;
    if (map.count(block_node) > 0){
      map.erase(block_node);
    }
    block_node.second -= 2;
    if (map.count(block_node) > 0){
      map.erase(block_node);
    }
  }
  // удалять cверху и снизу
  else if (b.first == 0){
    std::pair<int,int> block_node = poz;
    block_node.first += 1;
    if (map.count(block_node) > 0){
      map.erase(block_node);
    }
    block_node.first -= 2;
    if (map.count(block_node)  > 0){
      map.erase(block_node);
    }
  }
  return;
}
void smart_ai_player_t::del_edge(std::pair<int, int> head, std::pair<int, int> tail, std::pair<int, int> & b) {
  head.first += b.first;
  head.second += b.second;
  tail.first -= b.first;
  tail.second -= b.second;
  if (step_map.count(head) != 0){
    step_map.erase(head);
  }
  if (step_map.count(tail) != 0){
    step_map.erase(tail);
  }
}