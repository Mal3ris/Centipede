#include "Glyph.h"
#include "SpriteSheet.h"
#include "TEAL\ResourceManager.h"
#include <assert.h>

//Default Constructor
Glyph::Glyph()
{
	sprsheet = nullptr;
	cellIndex = 0;
	position = sf::Vector2f(0, 0);
}

//Constructor
Glyph::Glyph(SpriteSheet* sheet, int cellInd, sf::Vector2f pos)
{
	sprsheet = sheet;
	position = pos;
	cellIndex = cellInd;
}

//Draw
void Glyph::Draw()
{
	assert(sprsheet != nullptr);

	sprsheet->Draw(cellIndex, position);
}
