#include "Game.hpp"
#include "Piece.hpp"



int main(void)
{

  Game g(1000, 1000);
  g.LoadTextures();
  return g.Play();
}