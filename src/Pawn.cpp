#include "Pawn.hpp"
#include <iostream>

Pawn::Pawn(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Pawn;
  std::cout << "Created new pawn with color " << _color << std::endl;
}

Pawn::~Pawn()
{

}

std::vector<int> Pawn::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  int move1, move2, eatleft, eatright;
  std::vector<int> legal_moves;

  switch(_color)
  {
    case Piece::Color::White:
    {
      // check boundaries
      move1 = (w_pos+8)  < 64 ? w_pos + 8 : -1;

      // first pawn move can be 2 tiles
      move2 = (w_pos/8) == 1 ? w_pos + 16 : -1;

      // check if the pawn is on the rim
      eatleft  = w_pos % 8 != 0 ? w_pos + 7 : -1;
      eatright = w_pos % 8 != 7 ? w_pos + 9 : -1;
      break;
    }
    default:
    {
      // check boundaries
      move1 = (w_pos-8) >= 0 ? w_pos -  8 : -1;

      // first pawn move can be 2 tiles
      move2 = (w_pos/8) == 6 ? w_pos - 16 : -1;

      // check if the pawn is on the rim
      eatleft  = w_pos % 8 != 7 ? w_pos - 7 : -1;
      eatright = w_pos % 8 != 0 ? w_pos - 9 : -1;
      break;
    }
  }

  // the pawn should not land on preoccupied tiles
  if(move1 && w_board[move1]->GetType() == Piece::Type::Empty) 
    legal_moves.push_back(move1);

  if(move2 && w_board[move2]->GetType() == Piece::Type::Empty && move1 && w_board[move1]->GetType() == Piece::Type::Empty) 
    legal_moves.push_back(move2);

  // checks for eating left
  if(0 <= eatleft && eatleft < 64)
  {
    if(w_board[eatleft]->GetType() != Piece::Type::Empty && w_board[eatleft]->GetColor() != _color)
      legal_moves.push_back(eatleft);

    // en passant (ugly!)
    switch(_color)
    {
      case Piece::Color::White:
      {
        if(w_board[w_pos-1]->GetType() == Piece::Type::Pawn 
        && w_last_move.end == (w_pos-1) 
        && (w_last_move.start - w_last_move.end ) == 16 )
        {
          legal_moves.push_back(eatleft);
        }
        break;
      }
      default:
      {
        if(w_board[w_pos+1]->GetType() == Piece::Type::Pawn 
        && w_last_move.end == (w_pos+1) 
        && (w_last_move.start - w_last_move.end ) == -16 )
        {
          legal_moves.push_back(eatleft);
        }
        break;
      }
    }
  }

  // checks for eating left
  if(0 <= eatright && eatright < 64)
  {
    if(w_board[eatright]->GetType() != Piece::Type::Empty && w_board[eatright]->GetColor() != _color)
      legal_moves.push_back(eatright);

    // en passant (ugly!)
    switch(_color)
    {
      case Piece::Color::White:
      {
        if(w_board[w_pos+1]->GetType() == Piece::Type::Pawn 
        && w_last_move.end == (w_pos+1) 
        && (w_last_move.start - w_last_move.end ) == 16 )
        {
          legal_moves.push_back(eatright);
        }
        break;
      }
      default:
      {
        if(w_board[w_pos-1]->GetType() == Piece::Type::Pawn 
        && w_last_move.end == (w_pos-1) 
        && (w_last_move.start - w_last_move.end ) == -16 )
        {
          legal_moves.push_back(eatright);
        }
        break;
      }
    }
  }

  return legal_moves;
}