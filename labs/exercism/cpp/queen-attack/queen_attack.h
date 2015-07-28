#include <vector>
#include <bits/stl_pair.h>

namespace queen_attack {

    typedef std::pair<int, int> position;

    enum QueenColor {kWhite, kBlack};

    class chess_board {
    private:
        position white_queen_;
        position black_queen_;
        void place_queen(QueenColor queen, std::pair<int, int>);

    public:
        chess_board();
        chess_board(position white_queen, position black_queen);
        std::pair<int, int> white() const;
        std::pair<int, int> black() const;

    };



}