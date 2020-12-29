#pragma once

#include "Piece.hpp"

/* Borrow legal move checking algos from rook and bishop */
#include "Rook.hpp"
#include "Bishop.hpp"

class Queen : public Piece
{
public:
Queen(Piece::Color w_color = None);
~Queen();

std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const;

private:
::Rook _r;
::Bishop _b;
};