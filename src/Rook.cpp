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