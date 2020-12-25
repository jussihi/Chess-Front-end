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