#include "Rook.hpp"
#include <iostream>

Rook::Rook(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Rook;
}

Rook::~Rook()
{

}

std::vector<int> Rook::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  std::vector<int> legal_moves;

  // Get vertical moves downwards
  for(int i = -8; i > -64; i-=8)
  {
    // Boundary check
    if(w_pos + i < 0)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos+i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos+i);
    }
    else
    {
      if(w_board[w_pos+i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos+i);
      }
      break;
    }
  }

  // Get vertical moves upwards
  for(int i = 8; i < 64; i+=8)
  {
    // Boundary check
    if(w_pos + i >= 64)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos+i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos+i);
    }
    else
    {
      if(w_board[w_pos+i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos+i);
      }
      break;
    }
  }

  // Get horizontal moves to the left
  for(int i = -1; i > -8; i--)
  {
    // Row check
    if(((w_pos + i) / 8) != (w_pos / 8) || w_pos + i < 0)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos+i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos+i);
    }
    else
    {
      if(w_board[w_pos+i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos+i);
      }
      break;
    }
  }

  // Get horizontal moves to the right
  for(int i = 1; i < 8; i++)
  {
    // Row check
    if(((w_pos + i) / 8) != (w_pos / 8) || w_pos + i >= 64)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos+i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos+i);
    }
    else
    {
      if(w_board[w_pos+i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos+i);
      }
      break;
    }
  }

  return legal_moves;
}