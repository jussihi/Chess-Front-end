#pragma once


#include "Piece.hpp"

class Queen : public Piece
{
public:
Queen(Piece::Color w_color = None);
~Queen();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};