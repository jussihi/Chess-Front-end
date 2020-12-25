#pragma once


#include "Piece.hpp"

class King : public Piece
{
public:
King(Piece::Color w_color = None);
~King();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};