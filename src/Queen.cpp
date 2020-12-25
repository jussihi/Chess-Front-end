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