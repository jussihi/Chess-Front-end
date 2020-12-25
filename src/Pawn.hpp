#pragma once


#include "Piece.hpp"

class Pawn : public Piece
{
public:
Pawn(Piece::Color w_color = None);
~Pawn();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};