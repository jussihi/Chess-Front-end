#pragma once


#include "Piece.hpp"

class King : public Piece
{
public:
King(Piece::Color w_color = None);
~King();

virtual std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const;

private:

};