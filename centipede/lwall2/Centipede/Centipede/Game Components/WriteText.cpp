#include "WriteText.h"
#include "PlayerManager.h"
#include "ScoreManager.h"
#include "TileFactory.h"
#include "GridConstants.h"
#include "Glyph.h"

//Constructor that sets highest draw order
WriteText::WriteText(std::string s)
{
	scene = s;
	myTF = nullptr;
	SetDrawOrder(1);
}

//Overloaded with TileFactory for any play screen
WriteText::WriteText(TileFactory* pTF, std::string s)
{
	scene = s;
	myTF = pTF;
	SetDrawOrder(1);

	if (scene != "highscore") {
		nextpos = sf::Vector2f(0, 0);
		for (int i = 0; i < GridConstants::GRIDWIDTH; i++) {
			TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
			nextpos.x += myfont.CellWidth();
		}
	}
	
}

//Responsible for Writing Scoring Text
void WriteText::WriteLine() {
	std::string text;
	if (PlayerManager::getPlayer().score / 10000.0 <= .9) {
		text.push_back(' ');
	}
	if (PlayerManager::getPlayer().score / 1000.0 <= .9) {
		text.push_back(' ');
	}
	if (PlayerManager::getPlayer().score / 100.0 <= .9) {
		text.push_back(' ');
	}
	if (PlayerManager::getPlayer().score / 10.0 <= .9) {
		text.push_back('0');
	}
	text += std::to_string(PlayerManager::getPlayer().score);
	if (PlayerManager::getPlayer().currPat != "ai") {
		for (int i = 0; i < PlayerManager::getPlayer().lives - 1; i++) {
			text.push_back('|');
		}
		for (int i = 0; i <= 8 - PlayerManager::getPlayer().lives - 1; i++) {
			text.push_back(' ');
		}
	}
	else {
		for (int i = 0; i <= 8 - 1; i++) {
			text.push_back(' ');
		}
	}

	//Updates the top score to equal players score during gameplay
	if (PlayerManager::getPlayer().score > ScoreManager::GetHighScore(0).score && scene == "gameplay") {
		text += std::to_string(PlayerManager::getPlayer().score);
	}
	else {
		text += std::to_string(ScoreManager::GetHighScore(0).score);
	}
	
	//Magic number, big enough to go to end of screen, not exact
	for (int i = 0; i <= 16; i++) {
		text.push_back(' ');
	}

	nextpos = sf::Vector2f(0, 0);

	//Stops List from Getting Super Big and causing Lag
	while (!symbolsTop.empty()) {
		symbolsTop.pop_front();
	}

	for (size_t i = 0; i < text.length(); i++)
	{
		
		symbolsTop.push_back(myfont.GetGlyph(text.at(i), nextpos));

		nextpos.x += myfont.CellWidth();
	}

}

//In charge of Copyright
void WriteText::WriteCopyright() {
	std::string text;
	text.push_back('[');
	text += "ATARI";
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH/2 - 3) * GridConstants::CELLSIZE, (GridConstants::GRIDHEIGHT+1) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
}

//In charge of HighScores
void WriteText::WriteHighScores() {
	std::string text;
	text = "High";
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 5) * GridConstants::CELLSIZE, (3) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2) * GridConstants::CELLSIZE, (3) * GridConstants::CELLSIZE);
	text = "Scores";
	for (size_t i = 0; i < text.length(); i++)
	{
		TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
	for (int j = 0; j < 8; j++) {
		Highscore tmp = ScoreManager::GetHighScore(j);
		nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 4) * GridConstants::CELLSIZE, (4.0f + j) * GridConstants::CELLSIZE);
		text = "";

		if (tmp.score / 10000.0 <= .9) {
			text.push_back('0');
		}
		if (tmp.score / 1000.0 <= .9) {
			text.push_back('0');
		}
		if (tmp.score / 100.0 <= .9) {
			text.push_back('0');
		}
		if (tmp.score / 10.0 <= .9) {
			text.push_back('0');
		}
		text += std::to_string(tmp.score);

		for (size_t i = 0; i < text.length(); i++)
		{
			TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
			symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth();
		}

		nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 + 2) * GridConstants::CELLSIZE, (4.0f + j) * GridConstants::CELLSIZE);
		text = tmp.name;

		for (size_t i = 0; i < text.length(); i++)
		{
			TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
			symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

			// we must update the next position ourselves
			nextpos.x += myfont.CellWidth();
		}

	}
	text = "1 coin 1 play";
	//Magic num cause cant calc half len in statement
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 7) * GridConstants::CELLSIZE, 13 * GridConstants::CELLSIZE);

	for (size_t i = 0; i < text.length(); i++)
	{
		TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}

	text = "bonus every 12000";
	//Magic num cause cant calc half len in statement
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 8) * GridConstants::CELLSIZE, 15 * GridConstants::CELLSIZE);

	for (size_t i = 0; i < text.length(); i++)
	{
		TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
}

//In charge of HighScore Screen
void WriteText::WriteHighScoreScreen() {
	std::string text;
	
	text = "game over";
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 5) * GridConstants::CELLSIZE, (12) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		//TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
	
	text = "great score";
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 6) * GridConstants::CELLSIZE, (16) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		//TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
	
	text = "enter your initials";
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 10) * GridConstants::CELLSIZE, (18) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		//TileFactory::CreateTile(sf::Vector2f(nextpos.x + GridConstants::HALFCELLSIZE, nextpos.y + GridConstants::HALFCELLSIZE));
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
}

//Used to Print player names
void WriteText::WriteInitials(std::string text) {
	if (text.length() < 3) {
		for (int i = text.length(); i < 3; i++) {
			text.push_back(' ');
		}
	}
	nextpos = sf::Vector2f((GridConstants::GRIDWIDTH / 2 - 2) * GridConstants::CELLSIZE, (22) * GridConstants::CELLSIZE);
	for (size_t i = 0; i < text.length(); i++)
	{
		symbols.push_back(myfont.GetGlyph(text.at(i), nextpos));

		// we must update the next position ourselves
		nextpos.x += myfont.CellWidth();
	}
}

//Double Loop To Match the wiping symbols from score
void WriteText::Draw()
{
	std::list<Glyph>::iterator it;
	for (it = symbols.begin(); it != symbols.end(); it++)
		it->Draw();
	for (it = symbolsTop.begin(); it != symbolsTop.end(); it++)
		it->Draw();
}
