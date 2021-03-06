#pragma once

#include <vector>
#include <iostream>
#include <array>
#include <memory>


class Piece
{
public:
  enum Color{
    Black = -1,
    None = 0,
    White = 1
  };

  enum Type{
    Empty = 0,
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
    Piece::Type type;
    Piece::Type overriddenPieceType;
    Piece::Color overriddenPieceColor;
  };

  typedef int PiecePosition;
  

  Piece(Piece::Color w_color = None);
  ~Piece();

  Color GetColor() const;
  Type GetType() const;
  bool IsFloating() const;

  void SetFloating(bool w_floating = false);


  virtual std::vector<int> GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const { std::cout << "parent" << std::endl; return std::vector<int>(); }

protected:
  Color _color;
  Type _type;
  bool _floating;
};