#include <vector>
#include <string>
#include <bits/stl_pair.h>

namespace queen_attack {

    typedef std::pair<int, int> position;

    class chess_board {
    private:
        position white_queen_;
        position black_queen_;

    public:
        chess_board();
        chess_board(position white_queen, position black_queen);
        std::pair<int, int> white() const;
        std::pair<int, int> black() const;
        bool can_attack() const;
        operator std::string() const;

        bool are_on_diagonal(position pair, position queen_) const;
    };



}