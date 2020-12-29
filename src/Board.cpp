#include "Board.hpp"


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

}

std::array<std::unique_ptr<Piece>, 64>& Board::GetPieces()
{
  return _pieces;
}


std::vector<int> Board::GetLegalMoves(int w_piece) const
{
  if(_moveHistory.empty())
  {
    return std::move(_pieces[w_piece]->GetLegalMoves(_pieces, w_piece, {0, 0, Piece::Type::Empty}));
  }
  return std::move(_pieces[w_piece]->GetLegalMoves(_pieces, w_piece, _moveHistory.back()));
}