#include "King.hpp"
#include <iostream>

King::King(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::King;
  std::cout << "Created new King with color " << _color << std::endl;
}

King::~King()
{

}

std::vector<int> King::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  std::vector<int> legal_moves;

  // List of candidate moves
  std::vector<int> candidate_moves = { 8, -8 };

  // Add rest of candidates if the king is not on A or H files
  if(w_pos % 8 != 0)
  {
    std::vector<int> A{ -1, 7, -9 };
    std::move(A.begin(), A.end(), std::back_inserter(candidate_moves));
  }
  if(w_pos % 8 != 7)
  {
    std::vector<int> H{ 1, 9, -7 };
    std::move(H.begin(), H.end(), std::back_inserter(candidate_moves));
  }

  // Boundary checks
  for(auto it = candidate_moves.begin(); it != candidate_moves.end();)
  {
    // Boundary checks
    if( w_pos+*it > 63 || w_pos+*it < 0)
    {
      it = candidate_moves.erase(it);
    }
    else
    {
      // Check if the tile is preoccupied by same color
      if(w_board[w_pos+*it]->GetColor() == _color)
      {
        it = candidate_moves.erase(it);
      }
      else
      {
        legal_moves.push_back(w_pos+*it);
        it++;
      }
    }
  }
  return legal_moves;
}