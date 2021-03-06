#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Board.hpp"
#include "Engine.hpp"


class Game
{
public:
  enum Rotation {
    White,
    Black
  };

  Game(unsigned int w_window_width = 400, unsigned int w_window_height = 400, Rotation w_rotation = White);
  ~Game();

  int GetBoardTileFromCoordinates(int w_x, int w_y);

  void LoadTextures();
  void DrawBoard();

  
  
  int Play();


private:
  sf::RenderWindow _window;

  Rotation _rotation;

  float _boardSize;

  int _selectedTile;
  int _selectedTileOffsetX;
  int _selectedTileOffsetY;
  std::vector<int> _selectedTileLegalMoves;

  bool _leftMousePressed;
  int _mousePosX;
  int _mousePosY;

  std::map<Piece::Type, sf::Texture> _texturesW;
  std::map<Piece::Type, sf::Texture> _texturesB;

  sf::Texture _textureSquareDark;
  sf::Texture _textureSquareLight;

  sf::Texture _textureLegalMove;


  std::vector<sf::RectangleShape> _Tiles;
  std::vector<sf::RectangleShape> _Pieces;
  std::vector<sf::RectangleShape> _LegalMoves;

  Board _board;
  Engine _engine;

  Piece::Color _playerColor;
};