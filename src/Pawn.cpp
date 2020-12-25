#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Pawn;
  std::cout << "Created new pawn with color " << _color << std::endl;
}

Pawn::~Pawn()
{

}