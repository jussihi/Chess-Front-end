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

  typedef std::array<std::unique_ptr<Piece>, 64> BoardArray;

  enum MoveStatus {
    Illegal,
    Legal
  };

  Board();
  Board(const Board& other);
  ~Board();
  void InitBoard();
  std::array<std::unique_ptr<Piece>, 64>& GetPieces();
  Piece::Color GetCurrentTurn() { return _currentTurn; }
  std::vector<Piece::PieceMove>& GetMoveHistory() { return _moveHistory; }
  std::vector<int> GetLegalMoves(int w_piece);
  int GetChecks(Piece::Color w_color);
  MoveStatus MakeMove(int w_srcTile, int w_destTile);
  MoveStatus UndoMove();

private:
  BoardArray _pieces;
  std::vector<Piece::PieceMove> _moveHistory;
  Piece::Color _currentTurn;
  std::unique_ptr<Piece> _lastRemovedPiece;
};