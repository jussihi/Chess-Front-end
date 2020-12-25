#pragma once


#include "Piece.hpp"

class Rook : public Piece
{
public:
Rook(Piece::Color w_color = None);
~Rook();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};