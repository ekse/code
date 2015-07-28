#include <stdexcept>
#include "queen_attack.h"

namespace queen_attack {


    chess_board::chess_board() {
        white_queen_ = position(0, 3);
        black_queen_ = position(7, 3);
    }

    void chess_board::place_queen(QueenColor queen, position pos) {
        if (pos.first < 0 or pos.second < 0) {
            throw std::domain_error("outside of board");
        }

        if (pos.first > 7 or pos.second > 7) {
            throw std::domain_error("outside of board");
        }

        if (queen == QueenColor::kWhite) {
            if (black_queen_ == pos) {
                throw std::domain_error("position already occupied");
            } else {
                white_queen_ = pos;
            }
        } else {
            if (white_queen_ == pos) {
                throw std::domain_error("position already occupied");
            } else {
                black_queen_ = pos;
            }
        }
    }

        std::pair<int, int> chess_board::white() const {
            return white_queen_;
        }

        std::pair<int, int> chess_board::black() const {
            return black_queen_;
        }

    chess_board::chess_board(position white_queen, position black_queen) {
        place_queen(QueenColor::kWhite, white_queen);
        place_queen(QueenColor::kBlack, black_queen);
    }
}