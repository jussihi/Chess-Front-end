#include "Board.hpp"

#include <algorithm>


Board::Board()
{
  for(int i = 0; i < 64; i++)
  {
    _pieces[i] = std::make_unique<Piece>();
  }
}

Board::~Board()
{

}



void Board::InitBoard()
{
  /* Set empty tiles */
  for(int i = 16; i < 48; i++)
  {
    _pieces[i] = std::make_unique<Piece>();
  }

  /* Set white pawns */
  for(int i = 8; i < 16; i++)
  {
    _pieces[i] = std::make_unique<Pawn>(Piece::Color::White);
  }

  /* Set black pawns */
  for(int i = 48; i < 56; i++)
  {
    _pieces[i] = std::make_unique<Pawn>(Piece::Color::Black);
  }

  /* Set white rooks */
  _pieces[0] = std::make_unique<Rook>(Piece::Color::White);
  _pieces[7] = std::make_unique<Rook>(Piece::Color::White);

  /* Set black rooks */
  _pieces[56] = std::make_unique<Rook>(Piece::Color::Black);
  _pieces[63] = std::make_unique<Rook>(Piece::Color::Black);
  

  /* Set white knights */
  _pieces[1] = std::make_unique<Knight>(Piece::Color::White);
  _pieces[6] = std::make_unique<Knight>(Piece::Color::White);

  /* Set black knights */
  _pieces[57] = std::make_unique<Knight>(Piece::Color::Black);
  _pieces[62] = std::make_unique<Knight>(Piece::Color::Black);
  

  /* Set white bishops */
  _pieces[2] = std::make_unique<Bishop>(Piece::Color::White);
  _pieces[5] = std::make_unique<Bishop>(Piece::Color::White);

  /* Set black bishops */
  _pieces[58] = std::make_unique<Bishop>(Piece::Color::Black);
  _pieces[61] = std::make_unique<Bishop>(Piece::Color::Black);
  

  /* Set white queen */
  _pieces[3] = std::make_unique<Queen>(Piece::Color::White);

  /* Set black queen */
  _pieces[59] = std::make_unique<Queen>(Piece::Color::Black);


  /* Set white king */
  _pieces[4] = std::make_unique<King>(Piece::Color::White);

  /* Set black king */
  _pieces[60] = std::make_unique<King>(Piece::Color::Black);

  /* The game starts by white */
  _currentTurn = Piece::Color::White;

}

std::array<std::unique_ptr<Piece>, 64>& Board::GetPieces()
{
  return _pieces;
}


std::vector<int> Board::GetLegalMoves(int w_piece)
{
  std::vector<int> legal_moves;

  // get the legal moves for the piece
  if(_moveHistory.empty())
  {
    legal_moves = _pieces[w_piece]->GetLegalMoves(_pieces, w_piece, {0, 0, Piece::Type::Empty});
  }
  else
  {
    legal_moves = _pieces[w_piece]->GetLegalMoves(_pieces, w_piece, _moveHistory.back());
  }

  // check if the moves result in / prevent checks
  for(auto it = legal_moves.begin(); it != legal_moves.end();)
  {
    // store current status of the board
    std::unique_ptr<Piece> temp = std::make_unique<Piece>();
    std::swap(temp, _pieces[*it]);
    std::swap(_pieces[w_piece], _pieces[*it]);

    // Find any checks
    int checks = GetChecks(_currentTurn);
    
    // return the board status
    std::swap(_pieces[w_piece], _pieces[*it]);
    std::swap(temp, _pieces[*it]);

    // Last, discard the move if it results in a check
    if(checks)
    {
      it = legal_moves.erase(it);
    }
    else
    {
      it++;
    }
    
  }

  for(auto move : legal_moves)
  {
    std::cout << move << std::endl;
  }

  return legal_moves;
}


int Board::GetChecks(Piece::Color w_color)
{
  int checks = 0;

  for(int i = 0; i < 64; i++)
  {
    if(_pieces[i]->GetType() != Piece::Type::Empty && _pieces[i]->GetColor() != w_color)
    {
      std::vector<int> legal_moves;
      // get the legal moves for the piece
      if(_moveHistory.empty())
      {
        legal_moves = _pieces[i]->GetLegalMoves(_pieces, i, {0, 0, Piece::Type::Empty});
      }
      else
      {
        legal_moves = _pieces[i]->GetLegalMoves(_pieces, i, _moveHistory.back());
      }

      // check for checks
      for(auto& move : legal_moves)
      {
        if(_pieces[move]->GetColor() == w_color && _pieces[move]->GetType() == Piece::Type::King)
        {
          checks++;
        }
      }
    }
  }

  return checks;
}


Board::MoveStatus Board::MakeMove(int w_srcTile, int w_destTile)
{
  Board::MoveStatus ret = Board::MoveStatus::Illegal;

  struct Piece::PieceMove last_move = {0, 0, Piece::Type::Empty};
  if(!_moveHistory.empty())
    last_move = _moveHistory.back();

  // Make sure it's the correct color moving
  if(_pieces[w_srcTile]->GetColor() == _currentTurn)
  {
    // Check that the move is legal for the selected piece
    auto legalMoves = _pieces[w_srcTile]->GetLegalMoves(_pieces, w_srcTile, last_move);
    if(std::find(legalMoves.begin(), legalMoves.end(), w_destTile) != legalMoves.end())
    {
      std::swap(_pieces[w_srcTile], _pieces[w_destTile]);

      // If the move ate a piece, remove it from the board
      if(_pieces[w_srcTile]->GetColor() == -(_pieces[w_destTile]->GetColor()))
      {
        std::unique_ptr<Piece> empty = std::make_unique<Piece>();
        std::swap(empty, _pieces[w_srcTile]);
      }

      // Hand the move to the other color
      _currentTurn = Piece::Color(_currentTurn * (Piece::Color)-1);

      ret = Board::MoveStatus::Legal;
    }
  }

  return ret;
}