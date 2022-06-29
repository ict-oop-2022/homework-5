#include "players/human-player.h"

std::pair<int, int> human_player_t::make_move(const field_t &my_field, const field_t &enemy_field){
  output_stream << "Your field:"<< std::endl << my_field<<std::endl;
  output_stream << "Enemy's field"<< std::endl << enemy_field<<std::endl;
  output_stream << "Input you turn! [Example 1A or 10B or 6J]" << std::endl;

  while (true){
    std::string coord;
    getline(input_stream, coord);
    if (indexes_map.count(coord) > 0){
      return indexes_map.find(coord)->second;
    }
    else{
      output_stream <<"Incorrect move! [Correct example 1A or 10B or 6J]"<<std::endl;
    }
  }
}
void human_player_t::on_incorrect_move(int x, int y) {assert(false);}

void human_player_t::on_duplicate_move(int x, int y) {
  std::string col = "123456789";
  std::string row = "ABCDEFGHIJ";
  std::string num =  (x == 9)? "10": std::string(1,col[x]);
  output_stream << num+std::string(1,row[y])+" DUPLICATE! Repeat move!"<< std::endl;
}
void human_player_t::on_miss(int x, int y) {
  std::string col = "123456789";
  std::string row = "ABCDEFGHIJ";
  std::string temp =  (x == 9)? "10": std::string(1,col[x]);
  output_stream << temp+std::string(1,row[y])+" MISS! Enemy's turn!" << std::endl;
}
void human_player_t::on_hit(int x, int y) {
  std::string col = "123456789";
  std::string row = "ABCDEFGHIJ";
  std::string temp =  (x == 9)? "10": std::string(1,col[x]);
  output_stream << temp+std::string(1,row[y])+" HIT! Your next move!" << std::endl;
}
void human_player_t::on_kill(int x, int y) {
  std::string col = "123456789";
  std::string row = "ABCDEFGHIJ";
  std::string temp =  (x == 9)? "10": std::string(1,col[x]);
  output_stream << temp+std::string(1,row[y])+" KILL! Your next move!" << std::endl;
}
void human_player_t::on_win() {
  output_stream << "You WIN!"<< std::endl;
}
void human_player_t::on_lose() {
  output_stream << "You LOSE!"<<std::endl;
}