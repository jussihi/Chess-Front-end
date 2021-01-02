#pragma once

#include "Board.hpp"
#include "Pawn.hpp"
#include "Piece.hpp"

#include <mutex>

class Engine
{
public:
  struct EvaluationResult {
    Piece::PieceMove bestMove;
    int evaluation;
  };

  Engine(Board& w_board);
  ~Engine();

  int EvaluatePositionStatic(Board& w_board);

  EvaluationResult EvaluateBestMove(int w_depth);
  int MiniMaxAlg(Board& w_board, int w_depth, int w_alpha, int w_beta, Piece::Color w_colorToEvaluate);

private:

  std::vector<Piece::PieceMove> GetAllLegalMoves(Board& w_board, Piece::Color w_color);

  enum PiecePoints {
    Pawn = 10,
    Knight = 30,
    Bishop = 30,
    Rook = 50,
    Queen = 90,
    King = 500
  };

  Board& _board;

  std::mutex _evalMutex;

};