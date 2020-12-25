#pragma once


#include "Piece.hpp"

class Bishop : public Piece
{
public:
Bishop(Piece::Color w_color = None);
~Bishop();

std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

private:

};