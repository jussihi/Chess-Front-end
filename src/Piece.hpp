#pragma once

#include <vector>


class Piece
{
public:
  enum Color{
    None,
    White,
    Black
  };

  enum Type{
    Empty,
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
  };

  struct PieceMove
  {
    int start;
    int end;
  };

  typedef int PiecePosition;
  

  Piece(Piece::Color w_color = None);
  ~Piece();

  Color GetColor() const;
  Type GetType() const;
  bool IsFloating() const;

  void SetFloating(bool w_floating = false);


  std::vector<int> GetLegalMoves(Piece w_board[64], PiecePosition w_pos, PieceMove w_last_move) const;

protected:
  Color _color;
  Type _type;
  bool _floating;
};