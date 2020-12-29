#include "Knight.hpp"
#include <iostream>

Knight::Knight(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Knight;
  std::cout << "Created new Knight with color " << _color << std::endl;
}

Knight::~Knight()
{

}

std::vector<int> Knight::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}