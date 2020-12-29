#include "King.hpp"
#include <iostream>

King::King(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::King;
  std::cout << "Created new King with color " << _color << std::endl;
}

King::~King()
{

}

std::vector<int> King::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}