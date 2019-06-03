#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <string>
using namespace sf;
using namespace std;

// Design a class that will act as level constructor
class LevelConstructor : public Drawable, public Transformable
{
public:
  // This class method will load the tileset and using number selections, it will construct a tilemap
  /* Arguments for load(): tileset location, Vector2u containing the size of the tilemap, array containing the tile selections
  ** number of horizontal and vertical tiles (height and width) */
  bool load(string fileLocation, Vector2u sizeOfTiles, int* tileSelections, heigth, width)
  {
    // Load the file containing the tileset
    if (!setOfTiles.loadFromTile(fileLocation))
      return false;   // The SFML will return the reason for failure
    
    // Define what will vertex array store
    vertices.setPrimitiveType(Quads);
    // Resize the array to fit entire screen
    vertices.resize(width*height*4)
    
    // Create a nested loop that will assemble the tilemap using the tileset and selections provided
    for (int i = 0; i < width; ++i)
    {
      for (int j = 0; j < height; ++j)
      {
        // Obtain the current tile selection number
        int currentTileNumber = tileSelections[i+j*width]
        
        // Obtain the current tile position
        tileHorizontal = currentTileNumber % (vertices.getSize().x / sizeOfTiles.x);
        tileVertical = currentTileNumber / (vertices.getSize().x / sizeOfTiles.x);
        
        // Set the pointer to the current tile quad
        Vertex* quad = &vertices[(i+j*width)*4];
        
        // Define the quads four positions and textures
        quad[0].position = Vector2f(i*sizeOfTiles.x, j*sizeOfTiles.y);
        quad[1].position = Vector2f((i+1)*sizeOfTiles.x, j*sizeOfTiles.y);
        quad[2].position = Vector2f((i+1)*sizeOfTiles.x, (j+1)*sizeOfTiles.y);
        quad[3].position = Vector2f(i*sizeOfTiles.x, (j+1)*sizeOfTiles.y);
        
        quad[0].textCoords = Vector2f(tileHorizontal*sizeOfTiles.x, tileVertical*sizeOfTiles.y);
        quad[1].textCoords = Vector2f((tileHorizontal+1)*sizeOfTiles.x, tileVertical*sizeOfTiles.y);
        quad[2].textCoords = Vector2f((tileHorizontal+1)*sizeOfTiles.x, (tileVertical+1)*sizeOfTiles.y);
        quad[3].textCoords = Vector2f(tileHorizontal*sizeOfTiles.x, (tileVertical+1)*sizeOfTiles.y);
      }
    }
    
    // Level was created. Indicate success
    return true;
  }

private:
  // Define the overriden draw method for drawing levels using tiles
  virtual void draw(RenderTarget &target, RenderStates state) const
  {
    // Allow the map to be transformed
    state.transform *= getTransform();
    
    // Apply the objects textures to the state
    state.texture = &setOfTiles;
    
    // Draw the map
    target.draw(verties, state)
  }
  
  // Define a texture and vertex array
  Texture setOfTiles;
  VertexArray vertices;
};

int main(void)
{
  // Create the main window
  RenderWindow gameWindow (VideoMode(640, 480), "SkiPro!");
  
  // Control the handling of events
  Event eventHandler;
  
  // The main game loop will run until the game is closed
  while(gameWindow.isOpen())
  {
    // Fetch all events
    while (gameWindow.pollEvent(eventHandler))
    {
      // Use a switch statement to control the window, depending on type of event
      switch(eventHandler)
      {
        // By default, close the game window
        default:
          gameWindow.close();
          break;
      }
    }
    
    // Clear the screen
    gameWindow.clear();
  }
  
  return EXIT_SUCCESS;
}
