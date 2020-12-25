#include "Piece.hpp"


Piece::Piece(Piece::Color w_color) :
_color(w_color),
_type(Piece::Type::Empty),
_floating(false)
{

}

Piece::~Piece()
{

}


Piece::Color Piece::GetColor() const
{
  return _color;
}

Piece::Type Piece::GetType() const
{
  return _type;
}

bool Piece::IsFloating() const
{
 return _floating;
}

void Piece::SetFloating(bool w_floating)
{
  _floating = w_floating;
}

std::vector<int> Piece::GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const
{
  return std::vector<int>();
}