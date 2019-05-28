#include <SFML/Graphics.hpp>
using namespace sf;

class Game
{
public:
  Game();
  void run();
private:
  void processEvents();
  void update();
  void render();
private:
  sf::RenderWindow mWindow;
  sf::CircleShape mPlayer;
};

Game::Game() : mWindow(VideoMode(640, 480), "SkiPro"), mPlayer()
{
  mPlayer.setRadius(40.f);
  mPlayer.setPosition(100.f, 100.f);
  mPlayer.setFillColor(Color::Cyan);
}

void Game::run()
{
  while(mWindow.isOpen())
  {
    processEvents();
    update();
    render();
  }
}

void Game::handlePlayerInput(Keyborad::Key key, bool isPressed)
{
  if (key == Keyboard::W)
    mIsMovingUp = isPressed;
  else if (key == Keyboard::S)
    mIsMovingDown = isPressed;
  else if (key == Keyboard::A)
    mIsMovingLeft = isPressed;
  else if (key == Keyboard::D)
    mIsMovingRight = isPressed;
}

void Game::processEvents()
{
  Event event;
  while (mWindow.pollEvent(event))
  {
    switch(event.type)
    {
      case Event::KeyPressed:
        handlePlayerInput(event.key.code, true);
        break;
      case Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case Event::Closed:
        mWindow.close();
        break;
    }
  }
}

void Game::update()
{
  Vector2f movement(0.f, 0.f);
  if (mIsMovingUp)
    movement.x += 1.0f;
  else if (mIsMovingDown)
    movement.x -= 1.0f;
  else if (mIsMovingRight)
    movement.y += 1.0f;
  else if (mIsMovingLeft)
    movement.y -= 1.0f;
  
  mPlayer.move(movement);
}

void Game::render()
{
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.display();
}

int main()
{
  Game game;
  game.run();
  
  return 0;
}
