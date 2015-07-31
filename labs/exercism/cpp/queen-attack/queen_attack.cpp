#include <stdexcept>
#include <string>
#include <iostream>
#include "queen_attack.h"

namespace queen_attack {

    chess_board::chess_board() {
        white_queen_ = position(0, 3);
        black_queen_ = position(7, 3);
    }

    chess_board::chess_board(position white_queen, position black_queen) {
        place_queen(QueenColor::White, white_queen);
        place_queen(QueenColor::Black, black_queen);
    }

    void chess_board::place_queen(QueenColor queen, position pos) {
        if (pos.first < 0 or pos.second < 0 or
            pos.first > 7 or pos.second > 7) {
            throw std::domain_error("outside of board");
        }

        auto& current_queen = (queen == QueenColor::White) ? white_queen_ : black_queen_;
        auto& other_queen = (queen == QueenColor::White) ? black_queen_ : white_queen_;
        if (other_queen == pos) {
            throw std::domain_error("position already occupied");
        } else {
            current_queen = pos;
        }
    }

    std::pair<int, int> chess_board::white() const {
        return white_queen_;
    }

    std::pair<int, int> chess_board::black() const {
        return black_queen_;
    }

    chess_board::operator std::string() const {
        std::string result =
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n"
                "_ _ _ _ _ _ _ _\n";
        result[white_queen_.first * 16 + white_queen_.second * 2] = 'W';
        result[black_queen_.first * 16 + black_queen_.second * 2] = 'B';
        return result;
    }

    bool chess_board::can_attack() const {

        return     white_queen_.first  == black_queen_.first // same horizontal
                or white_queen_.second == black_queen_.second // same vertical
                or are_on_diagonal(white_queen_, black_queen_);

    }

    bool chess_board::are_on_diagonal(position white, position black) const {
        int diff_x = std::abs(white.first - black.first);
        int diff_y = std::abs(white.second - black.second);
        return diff_x == diff_y;
    }
}