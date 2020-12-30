#include "Knight.hpp"
#include <iostream>

Knight::Knight(Piece::Color w_color) :
Piece(w_color)
{
  _type = Piece::Type::Knight;
  std::cout << "Created new Knight with color " << _color << std::endl;
}

Knight::~Knight()
{

}

std::vector<int> Knight::GetLegalMoves(const std::array<std::unique_ptr<Piece>, 64>& w_board, PiecePosition w_pos, PieceMove w_last_move) const
{
  std::vector<int> legal_moves;

  // List of candidate moves
  std::vector<int> candidate_moves = { 6, 15, 17, 10, -6, -15, -17, -10 };

  
  for(auto it = candidate_moves.begin(); it != candidate_moves.end();)
  {
    // Boundary checks
    if( w_pos+*it > 63
    || w_pos+*it < 0
    || std::abs( (w_pos % 8) - ((w_pos+*it) % 8)) > 2 )
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