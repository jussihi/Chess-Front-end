#include "Queen.hpp"
#include <iostream>

Queen::Queen(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Queen;
  std::cout << "Created new Queen with color " << _color << std::endl;
}

Queen::~Queen()
{

}

std::vector<int> Queen::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}