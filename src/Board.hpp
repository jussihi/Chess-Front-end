#pragma once

#include "Piece.hpp"
#include "Pawn.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Queen.hpp"
#include "King.hpp"

class Board
{
public:
  Board();
  ~Board();
  void InitBoard();
  Piece* GetPieces();

private:
  Piece _pieces[64];

};