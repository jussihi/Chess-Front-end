#include "Game.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <thread>

Game::Game(unsigned int w_window_width, unsigned int w_window_height,
            Rotation w_rotation) :
_window(sf::VideoMode(w_window_width, w_window_height), "Chess"),
_leftMousePressed(false),
_rotation(w_rotation),
_selectedTile(-1),
_engine(_board),
_playerColor(Piece::Color::White)
{
  /* Initialize gfx, set framerate limit to 60 */
  _window.setFramerateLimit(60);

  /* Initialize the chess board TODO: do this later, when settings set */
  _board.InitBoard();
}


Game::~Game()
{

}

int Game::GetBoardTileFromCoordinates(int w_x, int w_y)
{
  switch (_rotation)
  {
  case Game::Rotation::White:
  {
    float TileSize = _boardSize / 8;
    int rotated_y = std::abs( ((int)( w_y /TileSize) + 1) - 8 );
    int rotated_x = (int)( w_x /TileSize);

    return (rotated_y * 8) + rotated_x;
  }
  /* black */
  default:
    return 0;
  }

  return 0;
}

void Game::LoadTextures()
{
  _texturesW[Piece::Type::Pawn].loadFromFile("../textures/w_pawn_png_shadow_256px.png");
  _texturesW[Piece::Type::Rook].loadFromFile("../textures/w_rook_png_shadow_256px.png");
  _texturesW[Piece::Type::Knight].loadFromFile("../textures/w_knight_png_shadow_256px.png");
  _texturesW[Piece::Type::Bishop].loadFromFile("../textures/w_bishop_png_shadow_256px.png");
  _texturesW[Piece::Type::King].loadFromFile("../textures/w_king_png_shadow_256px.png");
  _texturesW[Piece::Type::Queen].loadFromFile("../textures/w_queen_png_shadow_256px.png");

  _texturesB[Piece::Type::Pawn].loadFromFile("../textures/b_pawn_png_shadow_256px.png");
  _texturesB[Piece::Type::Rook].loadFromFile("../textures/b_rook_png_shadow_256px.png");
  _texturesB[Piece::Type::Knight].loadFromFile("../textures/b_knight_png_shadow_256px.png");
  _texturesB[Piece::Type::Bishop].loadFromFile("../textures/b_bishop_png_shadow_256px.png");
  _texturesB[Piece::Type::King].loadFromFile("../textures/b_king_png_shadow_256px.png");
  _texturesB[Piece::Type::Queen].loadFromFile("../textures/b_queen_png_shadow_256px.png");

  _textureSquareDark.loadFromFile("../textures/square brown dark_png_shadow_256px.png");
  _textureSquareLight.loadFromFile("../textures/square brown light_png_shadow_256px.png");

  _textureLegalMove.loadFromFile("../textures/transparent_circle2.png");

}

void Game::DrawBoard()
{
  _Tiles.clear();
  _Pieces.clear();
  _LegalMoves.clear();
  /* draw board */
  _boardSize = 1000 * 0.9;
  float TileSize = _boardSize / 8;
  for(int i = 0; i < 64; i++)
  {
    sf::RectangleShape tile;
    tile.setSize(sf::Vector2f(TileSize, TileSize));
    if( ((i / 8) + i) % 2 == 0)
    {
      tile.setTexture(&_textureSquareLight);
    }
    else
    {
      tile.setTexture(&_textureSquareDark);
    }
    tile.setPosition(sf::Vector2f(TileSize * (i % 8), TileSize * (i / 8)));
    _Tiles.push_back(tile);
  }

  /* draw pieces */
  for(int i = 0; i < 64; i++)
  {
    Piece p = *_board.GetPieces()[i];
    if(p.GetType() != Piece::Type::Empty)
    {
      sf::RectangleShape tile;
      tile.setSize(sf::Vector2f(TileSize, TileSize));
      tile.setPosition(sf::Vector2f(TileSize * (i % 8), TileSize * (std::abs( ((i/8) + 1) - 8 ))));
      
      /* If the current piece is currently floating (selected) */
      if(p.IsFloating())
      {
        tile.setPosition(sf::Vector2f(_mousePosX - _selectedTileOffsetX, _mousePosY - _selectedTileOffsetY));
      }
      


      switch (p.GetColor())
      {
      case Piece::Color::White:
        tile.setTexture(&_texturesW[p.GetType()]);
        break;
      case Piece::Color::Black:
        tile.setTexture(&_texturesB[p.GetType()]);
        break;
      }
      _Pieces.push_back(tile);
    }
  }

  for(auto move : _selectedTileLegalMoves)
  {
    sf::RectangleShape currLegalMove;
    currLegalMove.setSize(sf::Vector2f(TileSize, TileSize));
    currLegalMove.setPosition(sf::Vector2f(TileSize * (move % 8), TileSize * (std::abs( ((move/8) + 1) - 8 ))));
    currLegalMove.setTexture(&_textureLegalMove);
    _LegalMoves.push_back(currLegalMove);
  }

  _window.clear();
  /* draw tiles */
  for(auto it = _Tiles.begin(); it != _Tiles.end(); it++)
  {
      _window.draw(*it);
  }

  /* draw pieces */
  for(auto it = _Pieces.begin(); it != _Pieces.end(); it++)
  {
      _window.draw(*it);
  }

  /* draw legal moves */
  for(auto it = _LegalMoves.begin(); it != _LegalMoves.end(); it++)
  {
      _window.draw(*it);
  }

  _window.display();

}


int Game::Play()
{
  /* Main busy loop of the game */
  while(_window.isOpen())
  {
    sf::Event event;
    while(_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
        {
          // close the program gracefully
          std::cout << "exit" << std::endl;

          break;
        }

        case sf::Event::MouseButtonPressed:
        {
          if (event.mouseButton.button == sf::Mouse::Left)
          {
            _leftMousePressed = true;
            _mousePosX = event.mouseButton.x;
            _mousePosY = event.mouseButton.y;
            // todo!
            _selectedTile = GetBoardTileFromCoordinates(event.mouseButton.x, event.mouseButton.y);
            float TileSize = _boardSize / 8;
            _selectedTileOffsetX = event.mouseButton.x % (int)TileSize;
            _selectedTileOffsetY = event.mouseButton.y % (int)TileSize;
            _board.GetPieces()[_selectedTile]->SetFloating(true);
            _selectedTileLegalMoves = _board.GetLegalMoves(_selectedTile);
          }
          else if(event.mouseButton.button == sf::Mouse::Right)
          {
            std::cout << "undoing" << std::endl;
            _board.UndoMove();
          }
          break;
        }

        case sf::Event::MouseButtonReleased:
        {
          if(_selectedTile >= 0)
          {
            _board.GetPieces()[_selectedTile]->SetFloating(false);

            // try to move the piece
            if(_board.GetPieces()[_selectedTile]->GetColor() == _playerColor)
            {
              // Let engine play if the player moved piece OK
              if(_board.MakeMove(_selectedTile, GetBoardTileFromCoordinates(_mousePosX, _mousePosY)) == Board::MoveStatus::Legal)
              {
                auto engineMove = _engine.EvaluateBestMove(5);
                
                std::cout << "engine evaluates this position as " << engineMove.evaluation << std::endl;
                std::cout << "engine evaluates the bst move to be " << engineMove.bestMove.start << " --> " << engineMove.bestMove.end << std::endl;
                _board.MakeMove(engineMove.bestMove.start, engineMove.bestMove.end);

                //auto worker = std::thread(&Engine::EvaluateBestMove, _engine, 4);
                //worker.detach();
              }
            }
            
          }

          _leftMousePressed = false;
          _selectedTile = -1;
          
          break;
        }

        case sf::Event::MouseMoved:
        {
          if(_leftMousePressed)
          {
            _mousePosX = event.mouseMove.x;
            _mousePosY = event.mouseMove.y;
          }
          break;
        }

      }
    }
    DrawBoard();
  }
}