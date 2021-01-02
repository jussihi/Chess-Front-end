#include "Bishop.hpp"
#include <iostream>

Bishop::Bishop(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Bishop;
}

Bishop::~Bishop()
{

}

std::vector<int> Bishop::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  std::vector<int> legal_moves;

  // Get the diagonal to the up-left
  for(int i = -1; i >= -( (w_pos % 8) ) ; i--)
  {
    // Boundary check
    if(w_pos + std::abs(i * 8) + i >= 64)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos + std::abs(i * 8) + i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos + std::abs(i * 8) + i);
    }
    else
    {
      if(w_board[w_pos + std::abs(i * 8) + i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos + std::abs(i * 8) + i);
      }
      break;
    }
  }

  // Get the diagonal to the down-left
  for(int i = -1; i >= -( (w_pos % 8) ) ; i--)
  {
    // Boundary check
    if(w_pos + (i * 8) + i < 0)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos + (i * 8) + i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos + (i * 8) + i);
    }
    else
    {
      if(w_board[w_pos + (i * 8) + i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos + (i * 8) + i);
      }
      break;
    }
  }

  // Get the diagonal to the up-right
  for(int i = 1; i < (8 - (w_pos % 8) ) ; i++)
  {
    // Boundary check
    if(w_pos + i * 8 + i >= 64)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos + i * 8 + i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos + i * 8 + i);
    }
    else
    {
      if(w_board[w_pos + i * 8 + i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos + i * 8 + i);
      }
      break;
    }
  }

  // Get the diagonal to the down-right
  for(int i = 1; i < (8 - (w_pos % 8) ) ; i++)
  {
    // Boundary check
    if(w_pos - i * 8 + i < 0)
    {
      break;
    }

    // Check if the tile is occupied
    if(w_board[w_pos - i * 8 + i]->GetType() == Piece::Type::Empty)
    {
      legal_moves.push_back(w_pos - i * 8 + i);
    }
    else
    {
      if(w_board[w_pos - i * 8 + i]->GetColor() != _color)
      {
        legal_moves.push_back(w_pos - i * 8 + i);
      }
      break;
    }
  }

  return legal_moves;
}