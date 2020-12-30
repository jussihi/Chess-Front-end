#pragma once

#include <vector>
#include <array>
#include <memory>

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

  enum MoveStatus {
    Illegal,
    Legal
  };

  Board();
  ~Board();
  void InitBoard();
  std::array<std::unique_ptr<Piece>, 64>& GetPieces();
  std::vector<int> GetLegalMoves(int w_piece);
  int GetChecks(Piece::Color w_color);
  MoveStatus MakeMove(int w_srcTile, int w_destTile);

private:
  std::array<std::unique_ptr<Piece>, 64> _pieces;
  std::vector<Piece::PieceMove> _moveHistory;
  Piece::Color _currentTurn;
};