#pragma once


#include "Piece.hpp"

class Queen : public Piece
{
public:
Queen(Piece::Color w_color = None);
~Queen();

virtual std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const;

private:

};