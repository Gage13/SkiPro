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

int main()
{
  Game game;
  game.run();
  
  return 0;
}
