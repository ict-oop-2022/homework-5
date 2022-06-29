#include "game/sea-battle.h"

sea_battle_t::turn_t sea_battle_t::change_turn(turn_t current_turn) {
    return current_turn == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER;
}

std::string sea_battle_t::get_player_name(turn_t turn) {
    return turn == FIRST_PLAYER ? "First" : "Second";
}

sea_battle_t::sea_battle_t(std::shared_ptr<player_interface_t> player1, field_t field1,
                           std::shared_ptr<player_interface_t> player2, field_t field2) {
    // add players and fields to vectors
    players.push_back(player1);
    players.push_back(player2);
    fields.push_back(field1);
    fields.push_back(field2);
}

void sea_battle_t::play() {
    while (true) {
        // current player makes a move
        std::pair<int, int> pos = players[current]->make_move(fields[current], hide_ships(fields[(current + 1) % 2]));

        // check if move is correct
        if (!field_t::is_cell_valid(pos.first, pos.second)) {
            players[current]->on_incorrect_move(pos.first, pos.second);
            continue;
        }

        // check if move is duplicate
        if (fields[(current + 1) % 2][pos.first][pos.second] == field_t::MISS_CELL ||
            fields[(current + 1) % 2][pos.first][pos.second] == field_t::HIT_CELL) {
            players[current]->on_duplicate_move(pos.first, pos.second);
            continue;
        }

        // check if move is a hit or a kill
        if (fields[(current + 1) % 2][pos.first][pos.second] == field_t::SHIP_CELL) {
            fields[(current + 1) % 2][pos.first][pos.second] = field_t::HIT_CELL;
            // check of move is a kill
            if (!find_attached_ship_cell(fields[(current + 1) % 2], pos.first, pos.second)) {
                players[current]->on_kill(pos.first, pos.second);
                // check victory
                if (!find_any_ship_cell(fields[(current + 1) % 2])) {
                    break;
                }
            } else {
                players[current]->on_hit(pos.first, pos.second);
            }
            continue;
        }

        // if move is a miss
        fields[(current + 1) % 2][pos.first][pos.second] = field_t::MISS_CELL;
        players[current]->on_miss(pos.first, pos.second);
        current = change_turn(current);
    }
    players[current]->on_win();
    players[(current + 1) % 2]->on_lose();
}

field_t sea_battle_t::hide_ships(field_t field) {
    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
        for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
            if (field[i][j] == field_t::SHIP_CELL) {
                field[i][j] = field_t::EMPTY_CELL;
            }
        }
    }
    return field;
}

bool sea_battle_t::find_attached_ship_cell(field_t &field, int x, int y, int ignore_x, int ignore_y) {
    // check all directions recursively
    for (auto d : field_t::DIRECTIONS) {
        if (((x + d.first != ignore_x) || (y + d.second != ignore_y)) &&
            field_t::is_cell_valid(x + d.first, y + d.second) &&
            (field[x + d.first][y + d.second] == field_t::SHIP_CELL ||
             ((field[x + d.first][y + d.second] == field_t::HIT_CELL) &&
              find_attached_ship_cell(field, x + d.first, y + d.second, x, y)))) {
            return true;
        }
    }
    return false;
}

bool sea_battle_t::find_any_ship_cell(field_t &field) {
    // check every cell
    for (int i = 0; i < field_t::FIELD_SIZE; ++i) {
        for (int j = 0; j < field_t::FIELD_SIZE; ++j) {
            if (field[i][j] == field_t::SHIP_CELL) {
                return true;
            }
        }
    }
    return false;
}