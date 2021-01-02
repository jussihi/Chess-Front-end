#include "Engine.hpp"

#include <memory>
#include <algorithm>
#include <thread>
#include <chrono>


Engine::Engine(Board& w_board) :
_board(w_board)
{

}


Engine::~Engine()
{

}

int Engine::EvaluatePositionStatic(Board& w_board)
{
  int res = 0;
  Board::BoardArray& boardArr = w_board.GetPieces();
  for(int i = 0; i < 64; i++)
  {
    // std::cout << "Evaluating color: " << boardArr[i]->GetColor() << " type: " << boardArr[i]->GetType() << std::endl;
    switch(boardArr[i]->GetType())
    {
      case Piece::Type::Pawn:
        res += (PiecePoints::Pawn * boardArr[i]->GetColor());
        break;
      case Piece::Type::Rook:
        res += (PiecePoints::Rook * boardArr[i]->GetColor());
        break;
      case Piece::Type::Knight:
        res += (PiecePoints::Knight * boardArr[i]->GetColor());
        break;
      case Piece::Type::Bishop:
        res += (PiecePoints::Bishop * boardArr[i]->GetColor());
        break;
      case Piece::Type::King:
        res += (PiecePoints::King * boardArr[i]->GetColor());
        break;
      case Piece::Type::Queen:
        res += (PiecePoints::Queen * boardArr[i]->GetColor());
        break;
      default:
        break;
    }
  }
  //std::cout << res << std::endl;
  return res;
}

// This function also server as minimax root function
Engine::EvaluationResult Engine::EvaluateBestMove(int w_depth)
{
  // The eval result
  EvaluationResult bestMoveFound{{0, 0, Piece::Type::Empty}, -99999};

  Piece::Color currTurn = _board.GetCurrentTurn();
  std::vector<std::thread> workers;
  auto allLegalMoves = GetAllLegalMoves(_board, currTurn);

  constexpr int nthreads = 12;

  for (int i = 0; i < nthreads; i++) {
    workers.push_back(std::thread([&, i]() 
    {
      // make a local copy of the board
      Board newBoard = _board;
      
      for(int j = i; j < allLegalMoves.size(); j += nthreads)
      {
        if(newBoard.MakeMove(allLegalMoves[j].start, allLegalMoves[j].end) == Board::MoveStatus::Illegal)
        {
          std::cout << "BAD FAIL in MiniMaxAlg() root eval" << std::endl;
          continue;
        }
        auto newEval = currTurn * MiniMaxAlg(newBoard, w_depth - 1, -13333337, 13333337, (Piece::Color) (currTurn * -1));
        newBoard.UndoMove();

        _evalMutex.lock();
        if(newEval >= bestMoveFound.evaluation)
        {
          bestMoveFound.evaluation = newEval;
          bestMoveFound.bestMove = allLegalMoves[j];
        }
        _evalMutex.unlock();
      }
    }));
  }

  std::for_each(workers.begin(), workers.end(), [](std::thread &t) 
  {
      t.join();
  });

  

  // Normalize evaluation so that black == minus
  bestMoveFound.evaluation = currTurn * bestMoveFound.evaluation;
  
  return bestMoveFound;
}

int Engine::MiniMaxAlg(Board& w_board, int w_depth, int w_alpha, int w_beta, Piece::Color w_colorToEvaluate)
{
  if(w_depth == 0)
  {
    return EvaluatePositionStatic(w_board);
  }

  if(w_colorToEvaluate == Piece::Color::White)
  {
    auto allLegalMoves = GetAllLegalMoves(w_board, Piece::Color::White);
    int maxEval = -13333337;
    for(auto move : allLegalMoves)
    {
      if(w_board.MakeMove(move.start, move.end) == Board::MoveStatus::Illegal)
      {
        std::cout << "BAD FAIL in MiniMaxAlg() white eval" << std::endl;
        continue;
      }
        
      auto newEval = MiniMaxAlg(w_board, w_depth - 1, w_alpha, w_beta, Piece::Color::Black);
      w_board.UndoMove();

      maxEval = std::max(newEval, maxEval);
      w_alpha = std::max(w_alpha, newEval);
      if(w_beta <= w_alpha)
        break;
    }
    return maxEval;
  }
  else if(w_colorToEvaluate == Piece::Color::Black)
  {
    auto allLegalMoves = GetAllLegalMoves(w_board, Piece::Color::Black);
    int minEval = 13333337;
    for(auto move : allLegalMoves)
    {
      if(w_board.MakeMove(move.start, move.end) == Board::MoveStatus::Illegal)
      {
        std::cout << "BAD FAIL in MiniMaxAlg() black eval" << std::endl;
        continue;
      }

      auto newEval = MiniMaxAlg(w_board, w_depth - 1, w_alpha, w_beta, Piece::Color::White);
      w_board.UndoMove();

      minEval = std::min(newEval, minEval);
      w_beta = std::min(w_beta, newEval);
      if(w_beta <= w_alpha)
        break;
    }
    return minEval;
  }
  return -11100000;
}

std::vector<Piece::PieceMove> Engine::GetAllLegalMoves(Board& w_board, Piece::Color w_color)
{
  std::vector<Piece::PieceMove> allLegalMoves;
  Board uusBoardi = w_board;
  Board::BoardArray& a = w_board.GetPieces();
  for(int i = 0; i < 64; i++)
  {
    if(a[i]->GetColor() == w_color)
    {
      auto currPieceLegalMoves = w_board.GetLegalMoves(i);
      for(auto move : currPieceLegalMoves)
      {
        allLegalMoves.push_back({i, move, a[i]->GetType()});
      }
    }
  }

  return allLegalMoves;
}