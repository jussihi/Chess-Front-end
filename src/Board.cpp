#include "Board.hpp"


Board::Board()
{
  for(int i = 0; i < 64; i++)
  {
    _pieces[i] = Piece();
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
    _pieces[i] = Piece();
  }

  /* Set white pawns */
  for(int i = 8; i < 16; i++)
  {
    _pieces[i] = Pawn(Piece::Color::White);
  }

  /* Set black pawns */
  for(int i = 48; i < 56; i++)
  {
    _pieces[i] = Pawn(Piece::Color::Black);
  }

  /* Set white rooks */
  _pieces[0] = Rook(Piece::Color::White);
  _pieces[7] = Rook(Piece::Color::White);

  /* Set black rooks */
  _pieces[56] = Rook(Piece::Color::Black);
  _pieces[63] = Rook(Piece::Color::Black);
  

  /* Set white knights */
  _pieces[1] = Knight(Piece::Color::White);
  _pieces[6] = Knight(Piece::Color::White);

  /* Set black knights */
  _pieces[57] = Knight(Piece::Color::Black);
  _pieces[62] = Knight(Piece::Color::Black);
  

  /* Set white bishops */
  _pieces[2] = Bishop(Piece::Color::White);
  _pieces[5] = Bishop(Piece::Color::White);

  /* Set black bishops */
  _pieces[58] = Bishop(Piece::Color::Black);
  _pieces[61] = Bishop(Piece::Color::Black);
  

  /* Set white queen */
  _pieces[3] = Queen(Piece::Color::White);

  /* Set black queen */
  _pieces[59] = Queen(Piece::Color::Black);


  /* Set white king */
  _pieces[4] = King(Piece::Color::White);

  /* Set black king */
  _pieces[60] = King(Piece::Color::Black);


}

Piece* Board::GetPieces()
{
  return _pieces;
}