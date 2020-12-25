#include "Game.hpp"
#include "Piece.hpp"



int main(void)
{

  Game g;
  g.LoadTextures();
  return g.Play();
}