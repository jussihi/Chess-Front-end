#pragma once


#include "Piece.hpp"

class Knight : public Piece
{
public:
Knight(Piece::Color w_color = None);
~Knight();

virtual std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const;

private:

};