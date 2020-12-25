#pragma once


#include "Piece.hpp"

class Knight : public Piece
{
public:
Knight(Piece::Color w_color = None);
~Knight();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};