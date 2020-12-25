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