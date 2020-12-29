#include "Bishop.hpp"
#include <iostream>

Bishop::Bishop(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Bishop;
  std::cout << "Created new Bishop with color " << _color << std::endl;
}

Bishop::~Bishop()
{

}

std::vector<int> Bishop::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}