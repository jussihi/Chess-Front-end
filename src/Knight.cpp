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