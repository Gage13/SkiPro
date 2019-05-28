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
  sf::CircleShape mCircel;
};

int main()
{
  Game game;
  game.run();
  
  return 0;
}
