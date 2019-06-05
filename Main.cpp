/* Author: Dragi Plakalovic */
/* Date: May 28st, 2019
** Description: This is a simple ski game written in C++
** utilizing SFML Graphics Library.
** Version: V1.0
** Filename: ICS4U_summative.cpp */

#include <SFML/Graphics.hpp>	// Due to time constraints, there will be only graphics
#include <cstdlib>				// For debugging purposes
#include <iostream>
using namespace sf;		// All SFML functions, classes, and templates are in sf namespace.
using namespace std;	// For cstdlib functions
// Define the class for drawing the tilemap for the levels of the game
class LevelMaker : public Transformable, public Drawable
{
	// Define how the the level will be drawn inside the public space
public:
	/* The following class method will load the array containing info on when to use the tile in the tileset.
	** Using information supplied, it will define a quad containing a tile from the set,
	** and will create a level. */
	bool load(const std::string &tileSet, Vector2u tileSize, const int *tiles, unsigned int width, unsigned int height)
	{
		// Use the string passed to load the tileSet texture from the file refered in the string passed
		if (!tile_set.loadFromFile(tileSet))
		{
			return false; // Indicate failure of loading texture from the file
		}

		// Since the tiles are quadriterals, set that each four vertices form a quad
		m_vertices.setPrimitiveType(Quads);
		// Make the vertex array to fit the entire surface of game window using height and window argument
		m_vertices.resize(width*height*4);

		// Populate the game window with tiles
		for (unsigned int i = 0; i < width; ++i)
			for (unsigned int j = 0; j < height; ++j)
			{
				// Calculate the current tile number
				int tileNumber = tiles[i + j * width];

				// Obtain the tile position in the texture of tiles
				int tileHorizontal = tileNumber % (tile_set.getSize().x / tileSize.x);
				int tileVertical = tileNumber / (tile_set.getSize().x / tileSize.x);

				// Get the reference to the current tile
				Vertex* tileQuad = &m_vertices[(i+j*width)*4];

				// Define tile's texture coordinates and corners
				tileQuad[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
				tileQuad[1].position = Vector2f((i+1) * tileSize.x, j * tileSize.y);
				tileQuad[2].position = Vector2f((i+1) * tileSize.x, (j+1) * tileSize.y);
				tileQuad[3].position = Vector2f(i * tileSize.x, (j+1) * tileSize.y);

				tileQuad[0].texCoords = Vector2f(tileHorizontal * tileSize.x, tileVertical * tileSize.y);
				tileQuad[1].texCoords = Vector2f((tileHorizontal+1) * tileSize.x, tileVertical * tileSize.y);
				tileQuad[2].texCoords = Vector2f((tileHorizontal+1) * tileSize.x, (tileVertical+1) * tileSize.y);
				tileQuad[3].texCoords = Vector2f(tileHorizontal * tileSize.x, (tileVertical+1) * tileSize.y);
			}
		
		// Indicate the success of level creation
		return true;
	}

private:
	/* In private section of the class, define an overidable method level drawing
	** Also, define variables for holding tiles and its vertices */

	// The draw() method will need the name of the render window to which it would render the tilemap
	// Also, it needs states in which the tilemap would be drawn
	virtual void draw(RenderTarget& target, RenderStates states) const
	{
		// Get the transform state for the tilemap of the level
		states.transform *= getTransform();

		// Apply the texture of the tileset used to make the level
		states.texture = &tile_set;

		// Method for drawing the level
		target.draw(m_vertices, states);
	}

	// Define the vertices array and Texture variable for the tileset
	// Tiles are in effect textures 
	VertexArray m_vertices;
	Texture tile_set;

};

// Main game loop and function
int main(void)
{
	std::string imageFile = "floortileset.png";

	// Create a window in which the SkiPro! would be rendered
	RenderWindow gameWindow(VideoMode(750, 750), "SkiPro!");

	// Define variables for holding number of tiles in row and number of such rows
	int numberOfTilesInRow = 24;
	int numberOfRowsOfTiles = 48;

	// Select each tile from the tileSet to construct a level
	const int level[] =
	{
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,

		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,

		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,

		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,

		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,

		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
		53,53,53,53,53, 52,52,52,52,52,52,52,52,52,52,52,52,52,52, 53,53,53,53,53,
	};

	// Create a level using the tileset.
	/* Since tiles are 32x32, create a vector (32,32) */
	LevelMaker level1;
	if (!level1.load(imageFile, sf::Vector2u(32, 32), level, numberOfTilesInRow, numberOfRowsOfTiles))
		// If it is not possible to load the image, terminate the game and indicate an error
		return EXIT_FAILURE;

	// View coordinates variables
	float xPos = 0.0f;
	float yPos = 0.0f;
	float sizeX = 750.0f;
	float sizeY = 750.0f;

	// Set a view to allow for level scrolling (it will hold the current section of level displayed
	View currentSectionDisplay(FloatRect(xPos, yPos, sizeX, sizeY));

	// Activate the view 
	gameWindow.setView(currentSectionDisplay);

	// Create an Event variable which store user-generated game events
	Event event;

	// Process events as long the window is open
	while (gameWindow.isOpen())
	{
		// Make a loop that will process events stored in event variable
		while (gameWindow.pollEvent(event))
		{
			// Scroll the view to the right if Right Arrow Key is pressed
			/*if (event.key.code == Keyboard::Right)
			{
				currentSectionDisplay.move(30.0f, 0.0f);
			}

			// Scroll the view to the left if Left Arrow Key is pressed
			if (event.key.code == Keyboard::Left)
			{
				currentSectionDisplay.move(-30.0f, 0.0f);
			}*/

			// Scroll the view upwards if Up Arrow Key is pressed
			if (event.key.code == Keyboard::Up)
			{
				// Set the move value in the variable
				float moveUpBy = -50.0f;

				// Check if the view has reached the top of the level
				if (yPos == 0.0f)
				{
					// Keep the yPos the same
					yPos = 0.0f;
				}
				else
				{
					// Move the view up by 50.0f.
					currentSectionDisplay.move(0.0f, moveUpBy);
					// Update the current y position
					yPos += moveUpBy;
				}
			}

			// Scroll the view downwards if Down Arrow Key is pressed
			if (event.key.code == Keyboard::Down)
			{
				// Set the move value in the variable
				float moveDownBy = 50.0f;

				// Check if the view has reached the bottom of the level
				if (yPos == 750.0f)
				{
					// Keep the yPos the same
					yPos = 750.0f;
				}
				else
				{
					// Move the view down by 50.0f.
					currentSectionDisplay.move(0.0f, moveDownBy);
					// Update the current y position
					yPos += moveDownBy;
				}
			}

			// Close the window when user decides to close the game
			if (event.type == Event::Closed)
			{
				gameWindow.close();
			}
		}

		gameWindow.clear();
		gameWindow.draw(level1);
		gameWindow.setView(currentSectionDisplay);
		gameWindow.display();
		View currentView = gameWindow.getView();
	}

	return EXIT_SUCCESS;
}