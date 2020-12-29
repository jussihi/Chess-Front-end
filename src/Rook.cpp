#include "Rook.hpp"
#include <iostream>

Rook::Rook(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Rook;
  std::cout << "Created new Rook with color " << _color << std::endl;
}

Rook::~Rook()
{

}

std::vector<int> Rook::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}