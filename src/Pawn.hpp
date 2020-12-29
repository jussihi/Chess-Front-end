#pragma once


#include "Piece.hpp"

class Pawn : public Piece
{
public:
Pawn(Piece::Color w_color = None);
~Pawn();

std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const;

private:

};