#include "Queen.hpp"
#include <iostream>

Queen::Queen(Piece::Color w_color) :
Piece(w_color),
_r(_color),
_b(_color)
{
  _type = Piece::Type::Queen;
  std::cout << "Created new Queen with color " << _color << std::endl;
}

Queen::~Queen()
{

}

std::vector<int> Queen::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{

  std::vector<int> rook_moves = _r.GetLegalMoves(w_board, w_pos, w_last_move);
  std::vector<int> bishop_moves = _b.GetLegalMoves(w_board, w_pos, w_last_move);

  std::move(rook_moves.begin(), rook_moves.end(), std::back_inserter(bishop_moves));

  return bishop_moves;
}