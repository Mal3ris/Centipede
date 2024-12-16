#pragma once

//In Charge of Writing all the text on screen

#include "TEAL/CommonElements.h"
#include <list>
#include "Font.h"
#include "GridConstants.h"
#include "TileFactory.h"

class WriteText : public GameObject
{
public:
	WriteText() = delete;
	WriteText(std::string scene);
	WriteText(TileFactory* pTF, std::string scene);
	WriteText(const WriteText&) = delete;
	WriteText& operator=(const WriteText&) = delete;
	~WriteText() = default;

	virtual void Draw();

	void WriteLine();
	void WriteCopyright();
	void WriteHighScores();
	void WriteHighScoreScreen();
	void WriteInitials(std::string text);


private:
	Font myfont;

	std::list<Glyph> symbols;
	std::list<Glyph> symbolsTop;
	sf::Vector2f nextpos;

	TileFactory* myTF;

	std::string scene;
};